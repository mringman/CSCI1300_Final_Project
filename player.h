#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"
#include <string>
#include <vector>
using namespace std;

class Player : public Character {
    private:
        string characterType;
        int chronoEnergy;
        int timeStability;
        int luck;
        int sociability;
        vector<string> inventory;

    public:
        Player();
        Player(string n, string cT, int cE, int tS, int l, int s);

        string getCharacterType();
        int getChronoEnergy();
        int getTimeStability();
        int getLuck();
        int getSociability();

        void setCharacterType(string cT);
        void setChronoEnergy(int cE);
        void setTimeStability(int tS);
        void setLuck(int l);
        void setSociability(int s);

        void useChronoEnergy(int amount);
        void lowerTimeStability(int amount);

        void addItem(string item);
        void showInventory();

        void displayInfo() const;
    
};

#endif
