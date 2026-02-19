# Genetic Algorithm — Coverage Bot Evolution

A C++ simulation that evolves robots to maximize grid coverage using a genetic algorithm. Robots navigate a walled, battery-scattered map and are rewarded for collecting batteries (i.e., covering cells). Over generations, the population evolves increasingly effective exploration strategies — sometimes independently converging on a lawnmower sweep pattern.

<img width="1780" height="1479" alt="image" src="https://github.com/user-attachments/assets/5b046644-168c-4252-8595-f81a191eae68" />



## How It Works

### The Environment

Each robot is placed on a 20x20 grid surrounded by walls. The interior cells are randomly populated with batteries. Robots start at a random position and consume one energy per turn; collecting a battery restores 5 energy and adds to their fitness score. The simulation ends when a robot runs out of energy.

Cells are tracked as one of five states: `EMPTY`, `BATTERY`, `WALL`, `VISITED`, or `WILDCARD`. The `VISITED` state is key — robots that can sense where they've already been are able to break through a ~50% coverage plateau that otherwise caps their performance.

### The Genome

Each robot has 32 genes. Every gene is a rule:
- **Condition** — 4 values describing the expected state of the robot's N/E/S/W neighbors
- **Action** — a movement direction (N, E, S, W, or random)

On each turn, the robot scans its surroundings and fires the first gene whose condition matches. The final gene acts as a default fallback. Wildcards in condition values match any cell state, and can only enter the gene pool through mutation — not random initialization. This keeps them from becoming a crutch early on, while still letting them augment good strategies later.

### Evolution

Each generation runs 500 robots and selects for the next via:

- **Elitism** — the top 5% of performers are carried over unchanged
- **Tournament selection** — parents are chosen by randomly sampling 10 robots and picking the best
- **Uniform crossover** — each gene is independently inherited from one of the two parents (50/50)
- **Mutation** — each gene value has a small independent chance (~0.07%) of randomizing; the only path for wildcards into the genome

Robots always start at a random position on a freshly randomized map, which forces evolution toward generalizable strategies rather than memorized routes.

### Parallelism
All parallel benchmarking done on a 500 bot, 500 generation run.

Both the evaluation loop and the repopulation loop are parallelized with OpenMP, leading to a 6x speedup. Together they reduced runtime from ~138 seconds down to ~22 seconds on the same hardware. Further optimization (removing allocations, tightening the sim loop) brought it down to ~5 seconds. 

### Visualization

After the simulation, `graph.py` (matplotlib) displays a 2×2 dashboard:
- Average fitness per generation
- Best fitness per generation
- Final map state for a random gen-1 bot
- Final map state for the best bot found across all generations

## Key Findings

- **Visited state is essential.** Without tracking visited cells, average fitness plateaus around 50% map coverage. With it, bots can sometimes reach 90%+.
- **4-directional movement outperforms 8-directional.** Despite the added expressiveness, 8-direction movement is computationally significantly heavier and actually peaks lower in practice.
- **32 genes is the sweet spot.** Fewer genes limit expressiveness, more add noise without improving results.
- **Wildcards through mutation, not initialization.** Allowing wildcards in initial random genomes makes bots lazy. Restricting them to mutation means they augment good strategies rather than replace them.
- **Mutation rate should be very low.** Around 0.05–0.1% per gene value seems optimal. Higher rates disrupt good solutions faster than selection can preserve them.
- **Emergent sweep behavior.** The algorithm often independently evolves a boustrophedon (back-and-forth row sweep) pattern given enough time.
- **Performance plateaus.** Average fitness has local maxima around 50%, 65%, and 80% of maximum possible coverage. The global average maximum observed is just over 90% maximum coverage, requiring large populations and many generations.
- **Individuals outperform generational averages.** At least one high performer emerges early, but takes dozens or hundreds of generations to propagate genes and meaningfully raise generational average. 
- **500 bots × 2000 generations** consistently achieves >700 average fitness and at least one near-perfect coverage bot, completing in ~5 seconds on release build.

## Configuration

All tunable parameters live in [Config.h](Config.h):

| Parameter | Default | Notes |
|---|---|---|
| `MAP_SIZE` | 22 | Grid dimensions (includes border walls) |
| `GENE_COUNT` | 32 | Number of rules per robot |
| `GENERATIONS` | 2000 | Number of evolutionary cycles |
| `ROBOTS_PER_GEN` | 500 | Population size |
| `TOP_PERCENT` | 0.05 | Fraction of elites preserved each gen |
| `TOURNAMENT_SIZE` | 10 | Candidates sampled per tournament selection |
| `MUTATION_RATE` | 0.07 | Per-value mutation chance (expressed as %, divided by 100 internally) |

## Building

Requires a C++17 compiler, CMake, and OpenMP.

```bash
cmake -B build
cmake --build build --config Release
```

The build copies `graph.py` into the output directory automatically. Run the executable from the build output folder so the visualization script can find its input files.

## Dependencies

- C++17
- OpenMP
- Python 3 with `numpy` and `matplotlib` (for visualization)
