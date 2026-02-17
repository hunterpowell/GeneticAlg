#include <iostream>
#include <random>
#include <chrono>
#include "Simulator.h"

int main() {

    auto start = std::chrono::high_resolution_clock::now();
    
    auto sim = std::make_unique<Simulator>();
    sim->runSim();
    sim->showBots();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by function: " << duration.count() / 1000000 << " seconds\n";
    
    system("python graph.py");

    return 0;
}
