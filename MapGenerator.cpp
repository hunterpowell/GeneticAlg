#include <iostream>
#include <random>
#include <algorithm>
#include <array>
#include "MapGenerator.h"
#include "Config.h"

void MapGenerator::populateMap(Map& map, std::mt19937& rng) {
    int size = Config::MAP_SIZE;

    // fill whole grid with 0s to start
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            map.setCell(i, j, Config::EMPTY);
        }
    }
    
    // set perimeter
    for (int i = 0; i < size; i++) {
        map.setCell(0, i, Config::WALL);        // n
        map.setCell(i, size-1, Config::WALL);   // e
        map.setCell(size-1, i, Config::WALL);   // s
        map.setCell(i, 0, Config::WALL);        // w
    }

    // static_cast does so at compile time, speedge
    int interiorCells = Config::TOTAL_CELLS;
    int maxBatteries = static_cast<int>(interiorCells*0.4);
    
    std::array<std::pair<int, int>, Config::TOTAL_CELLS> interiorPos;
    int count = 0;
    for (int i = 1; i < size-1; i++) {
        for (int j = 1; j < size-1; j++){
            interiorPos[count++] = {i, j};
        }
    }
    // shuffle all interior cells
    std::shuffle(interiorPos.begin(), interiorPos.begin() + count, rng);

    // fills first 40% of (shuffled) cells with batteries
    for (int i = 0; i < maxBatteries; i++) {
        auto [row, col] = interiorPos[i];
        map.setCell(row, col, Config::BATTERY);
    }
}

