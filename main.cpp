#include <iostream>
#include <random>
#include "Robot.h"
#include "Map.h"
#include "MapGenerator.h"

int main() {

    // std::random_device rd;
    // std::mt19937 gen(rd());

    Robot robert; 
    robert.displayGenes();
    
    MapGenerator generator;
    Map map;
    generator.populateMap(map);
    map.setCell(robert.getRow(), robert.getCol(), Config::THE_GUY);
    map.display();

    robert.look(map);

    int* tmp = robert.getSurroundings();
    std::cout << robert.getRow() << std::endl;
    std::cout << robert.getCol() << std::endl;

    for (int i = 0; i < 8; i++) {
        std::cout << tmp[i] << " ";
    }

    return 0;
}
