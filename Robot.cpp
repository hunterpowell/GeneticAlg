#include <iostream>
#include <random>
#include "Robot.h"


Robot::Robot() {

    std::random_device rd;
    std::mt19937 gen(rd());
    
    // for random start
    std::uniform_int_distribution<int> startDist(1, Config::MAP_SIZE-2);

    // for random genes, 0-2 for wall, empty, battery
    std::uniform_int_distribution<int> geneDist(0, 2);
    // 0-4 for n, e, s, w, random
    std::uniform_int_distribution<int> moveDist(0, 4);

    // random start
    coords[0] = startDist(gen);
    coords[1] = startDist(gen);

    for (int i = 0; i < geneCount; i++) {
        for (int j = 0; j < valsPerGene; j++) {
            int r = geneDist(gen);
            genes[i][j] = r;
        }
        /* mod 5 for all movement directions; n, e, s, w, random
        consider adding 8 directional movement?
        maybe 6 directional and make the map 3d? */
        int r = moveDist(gen);
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

