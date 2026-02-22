#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <omp.h>
#include "Config.h"
#include "Robot.h"
#include "MapGenerator.h"
#include "Map.h"



class Simulator {
    private: 
        std::mt19937 rng;
        std::uniform_real_distribution<double> dist;
        MapGenerator generator;
        Map map;
        std::array<Robot, Config::ROBOTS_PER_GEN> roboArray;
        int topBots;
        Robot genOneRando;
        Robot bestBot;
        std::array<int, 2> bestGenFitness;
        
        std::vector<std::mt19937> rngs;
        std::array<Robot, Config::ROBOTS_PER_GEN> nextGen;
        
        void repopulate();
        Robot tournament(std::mt19937&);
        std::array<Robot, 2> crossover(const std::array<Robot, 2>&, std::mt19937&);
        void evalBest();
        
    public:

        Simulator();
        
        void runSim();
        void showBestGen();

        Robot getBestBot() {return bestBot;}
};

#endif
