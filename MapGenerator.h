#ifndef MAP_GENERATOR_H
#define MAP_GENERATOR_H

#include <random>
#include "Map.h"

class MapGenerator {
    private:
        std::mt19937 gen;

    public:
        MapGenerator();
        void populateMap(Map& m);

};

#endif
