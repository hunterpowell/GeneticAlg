#include <random>
#include <array>
#include "Config.h"
#include "Map.h"

class Robot {
    private:
        std::array<int, 8> surroundings;    // 0-7 -> n, ne, e, se, s, sw, w, nw
        std::array<int, 2> position;        // 0-1 -> row, col
        int energy;                         // current energy
        int fitness;                        // total energy
        int turnsAlive;
        int geneCount = Config::GENE_COUNT;
        int valsPerGene = Config::VALS_PER_GENE;
        std::array<std::array<int, Config::VALS_PER_GENE>, Config::GENE_COUNT> genes;
        std::array<int, Config::GENE_COUNT> movementGene;

        bool geneMatch(int);
        void move(Map&, int, std::mt19937&);

    public:
        Robot() = default;
        void init(std::mt19937&);

        void look(Map&);
        void movement(Map&, std::mt19937&);
        void reset();
        
        const std::array<int, 8>& getSurroundings() const {return surroundings;}
        int getEnergy() const {return energy;}
        int getFitness() const {return fitness;}
        int getTurnsAlive() const {return turnsAlive;}
        int getRow() {return position[0];}
        int getCol() {return position[1];}
        const std::array<std::array<int, Config::VALS_PER_GENE>, Config::GENE_COUNT>& getGenes() const {return genes;}
        const std::array<int, Config::GENE_COUNT>& getMovementGene() const {return movementGene;}
        

        void setGene(Robot, int);

        void displayGenes();
        
        friend std::ostream &operator << (std::ostream &output, const Robot &x);

};
