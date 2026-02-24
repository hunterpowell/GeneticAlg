#include <algorithm>
#include <iostream>
#include <fstream>
#include <omp.h>
#include "Simulator.h"

// #include <chrono>
// using MyClock = std::chrono::high_resolution_clock;


Simulator::Simulator() : rng(std::random_device{}()), dist(0.0, 1.0) {

    // populate array of robots w/ rng engine
    for (auto &r : roboArray) {
        r.init(rng);
    }

    topBots = (int)(Config::ROBOTS_PER_GEN * Config::TOP_PERCENT);
    
    // pick random from gen 1 for display later
    genOneRando = roboArray[69];
    // initialize bestBot for comparison later
    bestBot = roboArray[69];

    // gen and value resp.
    bestGenFitness[0] = 0;
    bestGenFitness[1] = 0;

    int numThreads = omp_get_max_threads();
    rngs.resize(numThreads);
    for (int i = 0; i < numThreads; i++) {
        rngs[i] = std::mt19937(rng());
    }
}

void Simulator::runSim() {
    std::ofstream AvgFile("averages.txt");
    std::ofstream BestFile("best.txt");

    AvgFile << -1 << " " << Config::TOTAL_CELLS << "\n";

    double progress = 0;

    // loop through gens
    for (int i = 0; i < Config::GENERATIONS; i++) {
        int localAvg = 0;
        // auto t1 = MyClock::now();

        // parallelism through OpenMP
        #pragma omp parallel for reduction(+:localAvg)
        for (int j = 0; j < Config::ROBOTS_PER_GEN; j++) {
            int tid = omp_get_thread_num();
            
            Map localMap; 
            roboArray[j].reset(rngs[tid]);
            generator.populateMap(localMap, rngs[tid]);
            localMap.setCell(
                roboArray[j].getRow(), 
                roboArray[j].getCol(), 
                Config::THE_GUY
            );
            
            while (roboArray[j].getEnergy() > 0) {
                roboArray[j].movement(localMap, rngs[tid]);
            }
            localAvg += roboArray[j].getFitness();
        }
        
        localAvg /= Config::ROBOTS_PER_GEN;
        
        // sort only top n descending 
        std::partial_sort(
            roboArray.begin(), roboArray.begin() + topBots, roboArray.end(),
            [](const Robot& a, const Robot& b) {
            return a.getFitness() > b.getFitness();
        });

        // auto t2 = MyClock::now();
        // save best performers and evolve next generation
        repopulate();

        // auto t3 = MyClock::now();
        // std::cout << "eval: " << std::chrono::duration<double, std::milli>(t2-t1).count() << "ms\n";
        // std::cout << "repop: " << std::chrono::duration<double, std::milli>(t3-t2).count() << "ms\n";

        if (localAvg > bestGenFitness[1]) {
            bestGenFitness[0] = i;
            bestGenFitness[1] = localAvg;
        }

        AvgFile << i << " " << localAvg << "\n";
        BestFile << i << " " << roboArray[0].getFitness() << "\n";
        // std::cout << "Avg fitness of gen " << i+1 << ": " << localAvg << "\n";

        // check best performer of each generation to find best overall performer
        if (roboArray[0].getFitness() >= bestBot.getFitness()) {
            bestBot = roboArray[0];
        }

        // this is an absolute mess but it prints a progress bar to console
        if (i % 25 == 0) {
            int width = 70;
            
            std::string bar = "[";
            int pos = int(progress * width);
            for (int j = 0; j < width - 2; j++) {
                bar += (j < pos) ? '#' : '-';
            }
            bar += "] " + std::to_string(int(progress * 100) + 2) + " %";
            
            std::cout << "\r" << bar;
            std::cout.flush();
            
            progress += .0125;
        }
    }
    std::cout << std::endl;

    evalBest();

    // bestBot.displayGenes();
    AvgFile.close();
    BestFile.close();
}

void Simulator::repopulate() {
    
    int eliteCount = (int)(Config::ROBOTS_PER_GEN * Config::TOP_PERCENT);
    
    // preserve top n percent
    for (int i = 0; i < eliteCount; i++) {
        nextGen[i] = roboArray[i];
    }
    
    // fill the rest, further parallelism 
    #pragma omp parallel for
    for (int i = eliteCount; i < Config::ROBOTS_PER_GEN; i++) {
        
        int tid = omp_get_thread_num();
        std::array<Robot, 2> parents = {tournament(rngs[tid]), 
            tournament(rngs[tid])};
            std::array<Robot, 2> children = crossover(parents, rngs[tid]);
            
            children[0].mutate(rngs[tid]);
            children[1].mutate(rngs[tid]);
            nextGen[i] = children[i%2];
        }
        
        roboArray = nextGen;
    }
    
Robot Simulator::tournament(std::mt19937& localRng) {
    
    Robot best;
    best.init(localRng);
    
    // random n robots, picks the best one
    for (int i = 0; i < Config::TOURNAMENT_SIZE; i++) {
        int x = (int)(dist(localRng) * Config::ROBOTS_PER_GEN);
        if (roboArray[x].getFitness() > best.getFitness()) {
            best = roboArray[x];
        }
    }
    
    return best;
}

std::array<Robot, 2> Simulator::crossover(const std::array<Robot, 2>& parents, std::mt19937& localRng) {
    std::array<Robot, 2> children;
    children[0].init(localRng);
    children[1].init(localRng);
    
    for (int i = 0; i < Config::GENE_COUNT; i++) {
        if (dist(localRng) < 0.5) {
            children[0].setGene(parents[0], i);
            children[1].setGene(parents[1], i);
        }
        else {
            children[0].setGene(parents[1], i);
            children[1].setGene(parents[0], i);
        }
    }
    return children;
}

void Simulator::evalBest() {

    std::ofstream randomBotMap("rand_map.txt");
    std::ofstream bestBotMap("best_map.txt");
    
    genOneRando.reset(rng);
    generator.populateMap(map, rng);
    map.setCell(genOneRando.getRow(), genOneRando.getCol(), Config::THE_GUY);

    while (genOneRando.getEnergy() > 0) {
        genOneRando.movement(map, rng);
    }

    // std::cout << "Random selection from gen 1\n";
    map.writeToFile(randomBotMap);
    // std::cout << genOneRando;

    bestBot.reset(rng);
    generator.populateMap(map, rng);
    map.setCell(bestBot.getRow(), bestBot.getCol(), Config::THE_GUY);

    while (bestBot.getEnergy() > 0) {
        bestBot.movement(map, rng);
    }
    // std::cout << "Best overall performer\n";
    map.writeToFile(bestBotMap);
    // std::cout << bestBot;
    // bestBot.displayGenes();

}

void Simulator::showBestGen() {
    std::cout << "Best gen: " << bestGenFitness[0] << "\n";
    std::cout << "Fitness: " << bestGenFitness[1] << "/" 
                << Config::TOTAL_CELLS * 2 << " ("
                << (float)bestGenFitness[1]/(Config::TOTAL_CELLS*2) * 100 << "%)";
}
