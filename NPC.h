#ifndef NPC_H
#define NPC_H

#include "character.h"
#include <string>
using namespace std;

class NPC : public Character {
    private:
        string dialogue;
        string quest;
        string reward;
    
        public:
            NPC();
            NPC(string n, int h, string d, string q, string r);

            string getDialogue();
            string getQuest();
            string getReward();

            void setDialogue(string d);
            void setQuest(string q);
            void setReward(string r);

            void speak();

            void displayInfo() const;

};

#endif
