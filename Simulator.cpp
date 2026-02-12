#include <algorithm>
#include "Simulator.h"

Simulator::Simulator() : rng(std::random_device{}()), dist(0.0, 1.0) {

    // populate array of robots w/ rng engine
    for (auto &r : roboArray) {
        r.init(rng);
    }
}

void Simulator::runSim() {

    std::array<int, Config::GENERATIONS> fitnessArray;

    for (int i = 0; i < Config::GENERATIONS; i++) {
        avgFitness = 0;

        // for every bot, generate new map and move through while energy
        for (auto& r : roboArray) {
            generator.populateMap(map);
            map.setCell(r.getRow(), r.getCol(), Config::THE_GUY);

            while (r.getEnergy() > 0) {
                r.movement(map, rng);
            }

            avgFitness += r.getFitness();
        }

        avgFitness /= Config::ROBOTS_PER_GEN;
        fitnessArray[i] = avgFitness;

        // sort descending 
        sort(roboArray.begin(), roboArray.end(), [](const Robot& a, Robot& b) {
            return a.getFitness() > b.getFitness();
        });
        
        repopulate();

        roboArray = nextGen;
    }

    bestBot = roboArray[0];

    // for (auto& r : roboArray) {
    //     std::cout << r;
    // }

}

void Simulator::repopulate() {
    
    // preserve top n%
    for (int i = 0; i < Config::ROBOTS_PER_GEN * Config::TOP_PERCENT; i++) {
        nextGen[i] = roboArray[i];
    }

    for (int i = (int)(Config::ROBOTS_PER_GEN * Config::TOP_PERCENT); i < Config::ROBOTS_PER_GEN; i++) {

        // parents, picks two (hopefully good) robots
        Robot parent1 = tournament();
        Robot parent2 = tournament();

    }

}

Robot Simulator::tournament() {
    
    Robot best;
    best.init(rng);
    
    // random n robots, picks the best one
    for (int i = 0; i < Config::TOURNAMENT_SIZE; i++) {
        int x = (int)(dist(rng) * Config::ROBOTS_PER_GEN);
        if (roboArray[x].getFitness() > best.getFitness()) {
            best = roboArray[x];
        }
    }

    return best;

}

void Simulator::crossover(Robot p1, Robot p2) {
    Robot child1;
    Robot child2;

    for (int i = 0; i < Config::GENE_COUNT; i++) {
        if (dist(rng) < 0.5) {
            child1.setGene(p1, i);
            child2.setGene(p2, i);
        }
        else {
            child1.setGene(p2, i);
            child2.setGene(p1, i);
        }
    }
}
