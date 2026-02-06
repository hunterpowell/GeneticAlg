#include <iostream>
#include <random>
#include "Robot.h"

Robot::Robot() : gen(std::random_device{}()) {
    
    // for random start
    std::uniform_int_distribution<int> startDist(1, Config::MAP_SIZE-2);

    // for random genes, 0-3 for wall, empty, battery, WILDCARD
    std::uniform_int_distribution<int> geneDist(0, 3);
    // 0-8 for n, ne, e, se, s, sw, w, nw, random
    std::uniform_int_distribution<int> moveDist(0, 8);

    // random start
    position[0] = startDist(gen);
    position[1] = startDist(gen);

    for (int i = 0; i < geneCount; i++) {
        for (int j = 0; j < valsPerGene; j++) {
            int r = geneDist(gen);
            genes[i][j] = r;
        }
        // randomizes 0-8 for n, ne, e, se, s, sw, w, nw, random
        int r = moveDist(gen);
        movementGene[i] = r;
    }
}

void Robot::look(Map m) {
    // populate surroundings array
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
        // check match OR wildcard, if neither we return false
        if (genes[geneIdx][j] != surroundings[j] && genes[geneIdx][j] != 3) {
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
    // std::cout << "CALLING MOVE, movement gene = " << mgene << "\n";
    
    // eat energy and increment turns alive
    energy--;
    turnsAlive++;

    int dir;
    std::uniform_int_distribution<int> randomDir(0, 7);

    // random dir if movement gene is 8
    dir = (mgene != 8) ? mgene : randomDir(gen);

    // move in a cardinal direction, n e s w respectively
    if (surroundings[dir] != Config::WALL) {
        
        // empty current cell as we move
        m.setCell(position[0], position[1], Config::EMPTY);
        
        // change y and x based on movement gene
        int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};
        int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
        position[0] += dy[dir];
        position[1] += dx[dir];
        
        // if battery, add 5 to energy and fitness
        if (m.checkCell(position[0], position[1]) == Config::BATTERY) {
            energy += 5;
            fitness += 5;
        }

        // set current cell to our robot constant
        m.setCell(position[0], position[1], Config::THE_GUY);
    }
    
    // update surroundings
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
