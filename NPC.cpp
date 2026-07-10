#include "NPC.h"
#include <iostream>
using namespace std;



NPC::NPC() : Character("Unknown NPC", 100){
    dialogue = "Hello traveler.";
    quest = "No quest available.";
    reward = "No reward.";
}

NPC::NPC(string n, int h, string d, string q, string r) : Character(n, h){
    dialogue = d;
    quest = q;
    reward = r;
}

string NPC::getDialogue(){
    return dialogue;
}
string NPC::getQuest(){
    return quest;
}
string NPC::getReward(){
    return reward;
}

void NPC::setDialogue(string d){
    dialogue = d;
}
void NPC::setQuest(string q){
    quest = q;
}
void NPC::setReward(string r){
    reward = r;
}

void NPC::speak(){
    cout << name << ": " << dialogue << endl;
}

void NPC::displayInfo() const{
    Character::displayInfo();
    cout << "Quest: " << quest << endl;
    cout << "Reward: " << reward << endl;
}
