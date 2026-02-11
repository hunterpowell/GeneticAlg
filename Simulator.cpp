#include <algorithm>
#include "Simulator.h"

Simulator::Simulator() : rng(std::random_device{}()), dist(0.0, 1.0) {

    // populate array of robots
    for (int i = 0; i < Config::ROBOTS_PER_GEN; i++) {
        Robot robert;
        roboArray[i] = robert;
    }
}

void Simulator::runSim() {
    int fitnessArr[Config::GENERATIONS];

    // main loop
    for (int i = 0; i < Config::GENERATIONS; i++) {
        avgFitness = 0;

        // generational loop, generates new map for every bot
        for (int j = 0; j < Config::ROBOTS_PER_GEN; j++) {
            generator.populateMap(map);
            map.setCell(roboArray[j].getRow(), roboArray[j].getCol(), Config::THE_GUY);
            
            while (roboArray[j].getEnergy() > 0) {
                roboArray[j].movement(map);
            }
            
            avgFitness += roboArray[i].getFitness();
        }

        // idx corresponds to generation
        avgFitness /= Config::ROBOTS_PER_GEN;
        fitnessArr[i] = avgFitness;

        // sort descending by fitness
        std::sort(roboArray, roboArray + Config::ROBOTS_PER_GEN, 
            [](Robot& a, Robot& b) {
                return a.getFitness() > b.getFitness();
            });
        
        // repopulate();

    }
}

void Simulator::repopulate() {
    
    // new generation
    Robot nextGen[Config::ROBOTS_PER_GEN];

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
    // std::uniform_int_distribution<int> dist(0, Config::ROBOTS_PER_GEN-1);
    
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

    if (dist(rng) < 0.5) {
        child1.setGenes(p1);
        child2.setGenes(p2);
    }
    else {
        child1.setGenes(p2);
        child2.setGenes(p1);
    }

}
