#ifndef ERA_H
#define ERA_H

#include <string>
#include <vector>
#include "NPC.h"

using namespace std;

class Era {
    private:
        string eraName;
        vector<string> subLocations;
        vector<NPC> npcs;
        bool componentFound;
    
    public:
        Era();
        Era(string name);

        string getEraName();
        bool getComponentFound();

        void setEraName(string name);
        void setComponentFound(bool found);

        void addSubLocation(string location);
        void addNPC(NPC npc);
        void markNPCTalkedTo(string npcName);

        void displayEra();
        void displayNPCs();
    
};


#endif
