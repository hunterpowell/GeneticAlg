#include <iostream>
#include <random>
#include "Simulator.h"

int main() {

    auto sim = std::make_unique<Simulator>();
    sim->runSim();

    // std::cout << "Random bot from gen 1, best performer\nBoth running on new maps\n";
    sim->showBots();
    // std::cout << sim->getBestBot();

    return 0;
}
