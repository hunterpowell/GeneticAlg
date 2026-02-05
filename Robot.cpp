#include <iostream>
#include <random>
#include "Robot.h"


Robot::Robot() {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, Config::MAP_SIZE-2);

    srand(time(0));


    // random start
    this->coords[0] = dis(gen);
    this->coords[1] = dis(gen);

    for (int i = 0; i < geneCount; i++) {
        for (int j = 0; j < valsPerGene; j++) {
            // mod 4 for every possible "thing" in adjacent squres; empty, battery, wall, predator
            // mod 3 for now bc fuck predators for now
            int r = rand() % 3;
            genes[i][j] = r;
        }
        /* mod 5 for all movement directions; n, e, s, w, random
        consider adding 8 directional movement?
        maybe 6 directional and make the map 3d? */
        int r = rand() % 5;
        movementGene[i] = r;
    }
}

void Robot::look(Map m) {
    // populate surroundings
    int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
    for (int i = 0; i < 8; i++) {
        this->surroundings[i] = m.checkCell(
            this->coords[0] + dy[i], 
            this->coords[1] + dx[i]
        );
    }
}

void Robot::displayGenes() {
    std::cout << "Genes: \n";
    for (int i = 0; i < geneCount; i++) {
        for (int j = 0; j < valsPerGene; j++) {
            std::cout << genes[i][j] << " ";
        }
        std::cout << movementGene[i] << std::endl;
    }
}

