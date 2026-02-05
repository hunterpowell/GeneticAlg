#include "Config.h"
#include "Map.h"

class Robot {
    private:
        int surroundings[8];
        int coords[2];
        int energy;
        int fitness;
        int turnsAlive;
        int geneCount = Config::GENE_COUNT;
        int valsPerGene = Config::VALS_PER_GENE;
        int genes[Config::GENE_COUNT][Config::VALS_PER_GENE];
        int movementGene[Config::GENE_COUNT];

    public:
        Robot();
        void look(Map m);
        
        void displayGenes();

        int* getSurroundings() {return &surroundings[0];}
        int getEnergy() {return energy;}
        int getFitness() {return fitness;}
        int getTurnsAlive() {return turnsAlive;}
        int getRow() {return coords[0];}
        int getCol() {return coords[1];}
        int* getGenes() {return &genes[0][0];}
        int* getMovementGene() {return &movementGene[0];}
};
