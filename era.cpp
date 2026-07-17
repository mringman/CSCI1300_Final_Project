#include "era.h"
#include <iostream>
using namespace std;

Era::Era(){
    eraName = "Unknown Era";
    componentFound = false;
}
Era::Era(string name){
    eraName = name;
    componentFound = false;
}

string Era::getEraName(){
    return eraName;
}
bool Era::getComponentFound(){
    return componentFound;
}

void Era::setEraName(string name){
    eraName = name;
}
void Era::setComponentFound(bool found){
    componentFound = found;
}

void Era::addSubLocation(string location){
    subLocations.push_back(location);
}
void Era::addNPC(NPC npc) {
    npcs.push_back(npc);
}
void Era::markNPCTalkedTo(string npcName){
    for (size_t i = 0; i < npcs.size(); i++){
        if (npcs[i].getName() == npcName) {
            npcs[i].setTalkedTo(true);
        }
    }
}

void Era::displayNPCs(){
    cout << "Characters: " << endl;
    
    if (npcs.size() == 0){
        cout << "None" << endl;
    }
    else{
        for (size_t i = 0; i < npcs.size(); i++) {
            cout << "- " << npcs[i].getName() << endl;

            if (npcs[i].getTalkedTo()){
                cout << "  ~ Talked to" << endl;
                cout << "  ~ Quest: " << npcs[i].getQuest() << endl;
                cout << "  ~ Reward: " << npcs[i].getReward() << endl;
            }
            else{
                cout << "  ~ Not Yet Met";
            }
            cout << endl;
        }
    }
}
void Era::displayEra(){
    cout << "Era: " << eraName << endl;
    cout << "Locations: " << endl;

    for (size_t i = 0; i < subLocations.size(); i++){
        cout << i + 1 << ". " << subLocations[i] << endl;
    }

    cout << endl;
    displayNPCs();

    if (componentFound) {
        cout << "Component Status: Found" << endl;
    }
    else{
        cout << "Component Status: Missing" << endl;
    }
}
