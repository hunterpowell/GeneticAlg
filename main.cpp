#include <iostream>
#include <random>
#include "Simulator.h"

int main() {

    auto sim = std::make_unique<Simulator>();
    sim->runSim();
    sim->showBots();

    /*
    what's next?
    output to csv and make matplotlib/python chart
    maybe go back to 4d movement?
    more maps per bot 3-5?
    bot memory?
    figure out how to break past avg plateau of ~400 
    */

    return 0;
}
