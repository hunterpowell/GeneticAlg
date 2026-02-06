#ifndef MAP_H
#define MAP_H

#include <iostream>
#include "Config.h"

class Map {
private: 
    int grid[Config::MAP_SIZE][Config::MAP_SIZE];

public: 
    Map() = default;

    int (*getGrid())[Config::MAP_SIZE] {return grid;}
    void setCell(int row, int col, int n) {
        grid[row][col] = n;
    }
    int checkCell(int row, int col) {
        return grid[row][col];
    }
    void eatBattery(int row, int col) {
        grid[row][col] = Config::EMPTY;
    }
    bool checkOOB(int row, int col) {
        return grid[row][col] == Config::WALL;
    }
    void display() {
        for (int i = 0; i < Config::MAP_SIZE; i++) {
            for (int j = 0; j < Config::MAP_SIZE; j++) {
                std::cout << grid[i][j] << " ";
            }
            std::cout << "\n";
        }
    }
};

#endif
