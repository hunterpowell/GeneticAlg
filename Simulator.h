#ifndef SIMULATOR_H
#define SIMULATOR_H


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
        Robot genOneRando;
        Robot bestBot;
        int avgFitness;

        std::array<Robot, Config::ROBOTS_PER_GEN> nextGen;

        void repopulate();
        Robot tournament();
        std::array<Robot, 2> crossover(const std::array<Robot, 2>&);

    public:
        Simulator();
        
        void runSim();
        void showBots();

        Robot getBestBot() {return bestBot;}
        int getAvgFitnesss() {return avgFitness;}

};

#endif
