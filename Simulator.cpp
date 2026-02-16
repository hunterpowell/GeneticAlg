#include <algorithm>
#include <iostream>
#include <fstream>
#include "Simulator.h"

Simulator::Simulator() : rng(std::random_device{}()), dist(0.0, 1.0) {

    // populate array of robots w/ rng engine
    for (auto &r : roboArray) {
        r.init(rng);
    }
    
    // pick random from gen 1 for display later
    genOneRando = roboArray[69];
    // initialize bestBot for comparison later
    bestBot = roboArray[69];
}

void Simulator::runSim() {
    std::ofstream AvgFile("averages.txt");
    std::ofstream BestFile("best.txt");
    // stores avg fitness of every gen (idx is gen #)
    std::array<int, Config::GENERATIONS> fitnessArray;

    for (int i = 0; i < Config::GENERATIONS; i++) {
        avgFitness = 0;

        // for every bot, generate new map and move through while energy
        for (auto& r : roboArray) {
            r.reset(rng);
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
        // save best performers and evolve next generation
        repopulate();

        AvgFile << i << " " << avgFitness << "\n";
        BestFile << i << " " << roboArray[0].getFitness() << "\n";
        std::cout << "Avg fitness of gen " << i+1 << ": " << avgFitness << "\n";
    }

    // check best performer of each generation to find best overall performer
    if (roboArray[0].getFitness() >= bestBot.getFitness()) {
        bestBot = roboArray[0];
    }

    // bestBot.displayGenes();
    AvgFile.close();
    BestFile.close();
}

void Simulator::showBots() {

    std::ofstream randomBotMap("rand_map.txt");
    std::ofstream bestBotMap("best_map.txt");
    
    genOneRando.reset(rng);
    generator.populateMap(map);
    map.setCell(genOneRando.getRow(), genOneRando.getCol(), Config::THE_GUY);

    while (genOneRando.getEnergy() > 0) {
        genOneRando.movement(map, rng);
    }

    std::cout << "Random selection from gen 1\n";
    map.display(randomBotMap);
    std::cout << genOneRando;

    bestBot.reset(rng);
    generator.populateMap(map);
    map.setCell(bestBot.getRow(), bestBot.getCol(), Config::THE_GUY);

    while (bestBot.getEnergy() > 0) {
        bestBot.movement(map, rng);
    }
    std::cout << "Best overall performer\n";
    map.display(bestBotMap);
    std::cout << bestBot;
    // bestBot.displayGenes();
}

void Simulator::repopulate() {

    int eliteCount = (int)(Config::ROBOTS_PER_GEN * Config::TOP_PERCENT);

    // preserve top n percent
    for (int i = 0; i < eliteCount; i++) {
        nextGen[i] = roboArray[i];
    }

    // fill the rest
    for (int i = eliteCount; i < Config::ROBOTS_PER_GEN; i++) {
        std::array<Robot, 2> parents = {tournament(), tournament()};
        std::array<Robot, 2> children = crossover(parents);
        children[0].mutate(rng);
        children[1].mutate(rng);
        // alternate children
        nextGen[i] = children[i%2];
    }

    roboArray = nextGen;
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

std::array<Robot, 2> Simulator::crossover(const std::array<Robot, 2>& parents) {
    std::array<Robot, 2> children;
    children[0].init(rng);
    children[1].init(rng);

    for (int i = 0; i < Config::GENE_COUNT; i++) {
        if (dist(rng) < 0.5) {
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
