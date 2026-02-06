#include "Config.h"
#include "Map.h"

class Robot {
    private:
    std::mt19937 gen;
        // 0-7 -> n, ne, e, se, s, sw, w, nw
        int surroundings[8];
        // 0-1 -> row, col
        int position[2];
        int energy;
        int fitness;
        int turnsAlive;
        int geneCount = Config::GENE_COUNT;
        int valsPerGene = Config::VALS_PER_GENE;
        int genes[Config::GENE_COUNT][Config::VALS_PER_GENE];
        int movementGene[Config::GENE_COUNT];

        bool geneMatch(int);
        void move(Map&, int);
        
    public:
        Robot();
        void look(Map);
        
        void displayGenes();

        int* getSurroundings() {return &surroundings[0];}
        int getEnergy() {return energy;}
        int getFitness() {return fitness;}
        int getTurnsAlive() {return turnsAlive;}
        int getRow() {return position[0];}
        int getCol() {return position[1];}
        int* getGenes() {return &genes[0][0];}
        int* getMovementGene() {return &movementGene[0];}
        void movement(Map&);

};
