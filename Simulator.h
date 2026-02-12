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
        Robot bestBot;
        int avgFitness;

        std::array<Robot, Config::ROBOTS_PER_GEN> nextGen;

        void repopulate();
        Robot tournament();
        void crossover(Robot, Robot);

    public:
        Simulator();
        
        void runSim();

        Robot getBestBot() {return bestBot;}
        int getAvgFitnesss() {return avgFitness;}


};

#endif
