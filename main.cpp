#include <iostream>
#include <random>
#include <chrono>
#include "Simulator.h"

int main() {

    std::cout << "Running...\n";
    auto start = std::chrono::high_resolution_clock::now();
    
    auto sim = std::make_unique<Simulator>();
    sim->runSim();
    
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time taken by sim: " << duration.count() << " milliseconds\n";
    
    sim->showBestGen();
    
    system("python graph.py");
    
    return 0;
}
