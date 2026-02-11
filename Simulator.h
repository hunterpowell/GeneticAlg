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
        Robot roboArray[Config::ROBOTS_PER_GEN];
        Robot bestBot;
        int avgFitness;

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
