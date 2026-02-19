#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include "Config.h"

class Map {
private: 
    std::array<std::array<int, Config::MAP_SIZE>, Config::MAP_SIZE> grid;

public: 
    Map() = default;

    std::array<std::array<int, Config::MAP_SIZE>, Config::MAP_SIZE>& getGrid() {return grid;}
    void setCell(int row, int col, int n) {
        grid[row][col] = n;
    }
    int checkCell(int row, int col) {
        return grid[row][col];
    }
    void display(std::ostream& file) {
        for (int i = 0; i < Config::MAP_SIZE; i++) {
            for (int j = 0; j < Config::MAP_SIZE; j++) {
                // std::string out;
                // switch (grid[i][j]) {
                //     case 0:
                //         out = "O";
                //         break;
                //     case 1:
                //         out = "#";
                //         break;
                //     case 2:
                //         out = "W";
                //         break;
                //     case 3:
                //         out = ".";
                //         break;
                //     default:
                //         out = "R";
                // }
                // std::cout << out << " ";
                file << grid[i][j] << " ";
            }
            // std::cout << "\n";
            file << "\n";
        }
    }
};

#endif
