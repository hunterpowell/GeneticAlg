#include <iostream>
#include <random>
#include "Simulator.h"

int main() {

    Simulator sim;
    sim.runSim();

    std::cout << sim.getBestBot();

    return 0;
}
