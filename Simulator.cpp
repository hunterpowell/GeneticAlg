#include "Simulator.h"

Simulator::Simulator() {

    // populate array of robots
    for (int i = 0; i < Config::ROBOTS_PER_GEN; i++) {
        Robot robert;
        roboArray[i] = robert;
    }
}

void Simulator::runSim() {

    // generational loop, generates new map for every bot
    for (int i = 0; i < Config::ROBOTS_PER_GEN; i++) {
        generator.populateMap(map);
        map.setCell(roboArray[i].getRow(), roboArray[i].getCol(), Config::THE_GUY);
        
        while (roboArray[i].getEnergy() > 0) {
            roboArray[i].movement(map);
        }

        // track best performer
        if (roboArray[i].getFitness() > bestBot.getFitness()) {
            bestBot = roboArray[i];
        }

    }
}

