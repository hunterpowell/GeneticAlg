#include <iostream>
#include <random>
#include <algorithm>
#include <fstream>
#include "Robot.h"

// constructor, not using normal one bc i need to pass in mersenne twister
void Robot::init(std::mt19937& gen) {
    // for random start
    std::uniform_int_distribution<int> startDist(1, Config::MAP_SIZE-2);

    // for random genes, 0-4 for wall, empty, battery, visited, wildcard
    std::uniform_int_distribution<int> geneDist(0, 3);
    // 0-8 for n, ne, e, se, s, sw, w, nw, random
    // testing 4d movement, n e s w rand
    std::uniform_int_distribution<int> moveDist(0, 4);

    // random start
    position[0] = startDist(gen);
    position[1] = startDist(gen);

    energy = 5;
    fitness = 0;
    turnsAlive = 0;

    for (int i = 0; i < geneCount; i++) {
        for (int j = 0; j < valsPerGene; j++) {
            genes[i][j] = geneDist(gen);
        }
        // randomizes 0-8 for n, ne, e, se, s, sw, w, nw, random
        // testing 0-4
        movementGene[i] = moveDist(gen);
    }
}

// let's me cout << robot; and it'll print out the relevant info
std::ostream &operator << (std::ostream &output, const Robot &x) {
    // std::cout << "\nrow: " << x.position[0] << " col: " << x.position[1] << "\n";
    std::cout << "energy: " << x.energy << "\n";
    std::cout << "fitness: " << x.fitness << "\n";
    std::cout << "turns alive: " << x.turnsAlive << "\n";
    return output;
}

void Robot::look(Map& m) {
    // populate surroundings array
    // std::array<int, 8> dy = {-1, -1, 0, 1, 1, 1, 0, -1};
    // std::array<int, 8> dx = {0, 1, 1, 1, 0, -1, -1, -1};
    std::array<int, 4> dy = {-1, 0, 1, 0};
    std::array<int, 4> dx = {0, 1, 0, -1};
    for (int i = 0; i < Config::VALS_PER_GENE; i++) {
        surroundings[i] = m.checkCell(
            position[0] + dy[i], 
            position[1] + dx[i]
        );
    }
}

// check one gene at a time, iterate through each value and return false for first miss
bool Robot::geneMatch(int geneIdx) {
    for (int j = 0; j < Config::VALS_PER_GENE; j++) {
        // check match OR wildcard, if neither we return false
        if (genes[geneIdx][j] != surroundings[j] && genes[geneIdx][j] != Config::WILDCARD) {
            return false;
        }
    }
    return true;
}

void Robot::movement(Map& m, std::mt19937& gen) {
    // update surroundings
    look(m);

    // loop through rows of genes, -1 bc we default to final gene
    for (int i = 0; i < Config::GENE_COUNT-1; i++) {
        if (geneMatch(i)) {
            // move direction of first match
            move(m, movementGene[i], gen);
            return;
        }
    }
    // default to final gene if no match
    move(m, movementGene[Config::GENE_COUNT-1], gen);
}

void Robot::move(Map& m, int mgene, std::mt19937& gen) {
    
    // eat energy and increment turns alive
    energy--;
    turnsAlive++;

    int dir;
    std::uniform_int_distribution<int> randomDir(0, 3);

    // random dir if movement gene is 8
    // reworked for 4d movement
    dir = (mgene != 4) ? mgene : randomDir(gen);

    // move if direction of movement isn't the wall
    if (surroundings[dir] != Config::WALL) {
        
        // set cell to visited as we move
        m.setCell(position[0], position[1], Config::VISITED);
        
        // change y and x based on movement gene
        // std::array<int, 8> dy = {-1, -1, 0, 1, 1, 1, 0, -1};
        // std::array<int, 8> dx = {0, 1, 1, 1, 0, -1, -1, -1};
        std::array<int, 4> dy = {-1, 0, 1, 0};
        std::array<int, 4> dx = {0, 1, 0, -1};
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
}

void Robot::reset(std::mt19937& gen) {
    energy = 5;
    fitness = 0;
    turnsAlive = 0;
    std::uniform_int_distribution<int> startDist(1, Config::MAP_SIZE-2);
    position[0] = startDist(gen);
    position[1] = startDist(gen);
}

// a few % chance to mutate every time a baby is made
void Robot::mutate(std::mt19937& rng) {
    std::uniform_real_distribution<double> chance(0.0, 1.0);
    // this is the only place wildcards can eneter the gene pool
    std::uniform_int_distribution<int> geneVal(0, 4);
    std::uniform_int_distribution<int> moveVal(0, 4);

    for (int i = 0; i < Config::GENE_COUNT; i++) {
        for (int j = 0; j < Config::VALS_PER_GENE; j++) {
            if (chance(rng) < Config::MUTATION_RATE) {
                genes[i][j] = geneVal(rng);
            }
        }
        if (chance(rng) < Config::MUTATION_RATE) {
            movementGene[i] = moveVal(rng);
        }
    }
}

void Robot::setGene(Robot r, int pos) {
    genes[pos] = r.getGenes()[pos];
    movementGene[pos] = r.getMovementGene()[pos];
}

void Robot::displayGenes() {
    std::cout << "Genes: \n";
    for (int i = 0; i < geneCount; i++) {
        for (int j = 0; j < valsPerGene; j++) {
            std::cout << genes[i][j] << " ";
        }
        std::cout << " m: " << movementGene[i] << std::endl;
    }
}

