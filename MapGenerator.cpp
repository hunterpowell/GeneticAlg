#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include "MapGenerator.h"
#include "Config.h"

MapGenerator::MapGenerator() : gen(std::random_device{}()) {
}

void MapGenerator::populateMap(Map& map) {
    int size = Config::MAP_SIZE;
    int (*grid)[Config::MAP_SIZE] = map.getGrid();
    int totalCells = size * size;

    // fill whole grid with 0s to start
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            grid[i][j] = Config::EMPTY;
        }
    }
    
    // set perimeter
    for (int i = 0; i < size; i++) {
        grid[0][i] = Config::WALL;          // n wall 
        grid[i][size-1] = Config::WALL;     // e wall
        grid[size-1][i] = Config::WALL;     // s wall
        grid[i][0] = Config::WALL;          // w wall
    }

    // static_cast does so at compile time, speedge
    int interiorCells = Config::TOTAL_CELLS;
    int maxBatteries = static_cast<int>(interiorCells*0.4);
    
    // tmp vector for interior filling
    std::vector<std::pair<int, int>> interiorPos; 
    for (int i = 1; i < size-1; i++) {
        for (int j = 1; j < size-1; j++) {
            interiorPos.push_back({i, j});
        }
    }
    
    // shuffle all interior cells
    std::shuffle(interiorPos.begin(), interiorPos.end(), gen);

    // fills first 40% of (shuffled) cells with batteries
    for (int i = 0; i < maxBatteries; i++) {
        auto [row, col] = interiorPos[i];
        grid[row][col] = Config::BATTERY;
    }

}

