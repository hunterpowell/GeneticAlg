#include <iostream>
#include <random>
#include "Robot.h"
#include "Map.h"
#include "MapGenerator.h"

int main() {

    Robot robert; 
    MapGenerator generator;
    Map m;
    generator.populateMap(m);
    m.setCell(robert.getRow(), robert.getCol(), Config::THE_GUY);

    m.display();
    while (robert.getEnergy() > 0) {
        robert.look(m);
        robert.movement(m);
    }
    m.display();


    return 0;
}
