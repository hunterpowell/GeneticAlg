#ifndef SIMULATOR_H
#define SIMULATOR_H


#include "Config.h"
#include "Robot.h"
#include "MapGenerator.h"
#include "Map.h"


class Simulator {
    private: 
        MapGenerator generator;
        Map map;
        Robot roboArray[Config::ROBOTS_PER_GEN];
        Robot bestBot;
        int avgFitness;

    public:
        Simulator();
        
        void runSim();

        Robot getBestBot() {return bestBot;}
        int getAvgFitnesss() {return avgFitness;}


};

#endif
