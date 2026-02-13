#ifndef CONFIG_H
#define CONFIG_H

class Config {
    public:
        static constexpr int EMPTY = 0;
        static constexpr int BATTERY = 1;
        static constexpr int WALL = 2;
        // static constexpr int PREDATOR = 3;
        static constexpr int THE_GUY = 7;

        // map size
        static constexpr int MAP_SIZE = 22;
        static constexpr int TOTAL_CELLS = (MAP_SIZE-2) * (MAP_SIZE-2);     // -2 bc i don't want to turn the walls into batteries
        
        // robot numbers
        static constexpr int GENE_COUNT = 64;
        static constexpr int VALS_PER_GENE = 8;

        // sim numbers
        static constexpr int GENERATIONS = 500;
        static constexpr int ROBOTS_PER_GEN = 500;
        static constexpr double TOP_PERCENT = 0.1;
        static constexpr int TOURNAMENT_SIZE = 10;
        static constexpr double MUTATION_RATE = 0.03;

};

#endif
