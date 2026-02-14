#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <string>
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
    void display() {
        for (int i = 0; i < Config::MAP_SIZE; i++) {
            for (int j = 0; j < Config::MAP_SIZE; j++) {
                std::string out;
                switch (grid[i][j]) {
                    case 0:
                        out = "O";
                        break;
                    case 1:
                        out = "#";
                        break;
                    case 2:
                        out = "W";
                        break;
                    case 3:
                        out = ".";
                        break;
                    default:
                        out = "R";
                }
                std::cout << out << " ";
            }
            std::cout << "\n";
        }
    }
};

#endif
