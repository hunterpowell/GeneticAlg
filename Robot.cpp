#include <iostream>
#include <random>
#include "Robot.h"

Robot::Robot() : gen(std::random_device{}()) {

    // std::random_device rd;
    // std::mt19937 gen(rd());
    
    // for random start
    std::uniform_int_distribution<int> startDist(1, Config::MAP_SIZE-2);

    // for random genes, 0-2 for wall, empty, battery
    std::uniform_int_distribution<int> geneDist(0, 2);
    // 0-4 for n, e, s, w, random
    std::uniform_int_distribution<int> moveDist(0, 4);

    // random start
    position[0] = startDist(gen);
    position[1] = startDist(gen);

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
        surroundings[i] = m.checkCell(
            position[0] + dy[i], 
            position[1] + dx[i]
        );
    }
}

bool Robot::geneMatch(int geneIdx) {
    for (int j = 0; j < Config::VALS_PER_GENE; j++) {
        if (genes[geneIdx][j] != surroundings[j]) {
            return false;
        }
    }
    return true;
}

void Robot::movement(Map& m) {
    // loop through rows of genes
    for (int i = 0; i < Config::GENE_COUNT; i++) {
        if (geneMatch(i)) {
            // move direction of first match
            std::cout << "MATCH MATCH MATCH\n";
            move(m, movementGene[i]);
            return;
        }
    }
    // default to final gene if no match
    std::cout << "NO MATCH NO MATCH NO MATCH\n";
    move(m, movementGene[Config::GENE_COUNT-1]);
}

void Robot::move(Map& m, int mgene) {
    std::cout << "CALLING MOVE, movement gene = " << mgene << "\n";
    // 0-4 -> n, e, s, w, random
    energy -= 1;
    turnsAlive += 1;

    int dir;
    int tmp;
    std::uniform_int_distribution<int> randomDir(0, 3);
    
    // double bc surroudings is 8 directions but movement is 4
    // even nums are cardinal
    if (mgene != 4) {
        dir = 2*mgene;
        tmp = mgene;
    }
    // random direction if movementGene is 4
    else {
        dir = 2*randomDir(gen);
        tmp = dir/2;
    }

    // move in a cardinal direction, n e s w respectively
    if (surroundings[dir] != Config::WALL) {
        m.setCell(position[0], position[1], Config::EMPTY);
        switch (tmp) {
            case(0):
                std::cout << "moving n\n";
                position[0]--;
                break;
            case(1):
                std::cout << "moving e\n";
                position[1]++;
                break;
            case(2):
                std::cout << "moving s\n";
                position[0]++;
                break;
            case(3):
                std::cout << "moving w\n";
                position[1]--;
                break;
        }
        m.setCell(position[0], position[1], Config::THE_GUY);
    }
    
    look(m);
    
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
