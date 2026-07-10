#include "player.h"
#include <iostream>
using namespace std;

Player::Player() : Character("Unknown", 100){
    characterType = "Unknown";
    chronoEnergy = 100;
    timeStability = 100;
    luck = 5;
    sociability = 5;
}
Player::Player(string n, string cT, int cE, int tS, int l, int s) : Character(n, 100) {
    characterType = cT;
    chronoEnergy = cE;
    timeStability = tS;
    luck = l;
    sociability = s;
}

string Player::getCharacterType(){
    return characterType;
}
int Player::getChronoEnergy(){
    return chronoEnergy;
}
int Player::getTimeStability(){
    return timeStability;
}
int Player::getLuck(){
    return luck;
}
int Player::getSociability(){
    return sociability;
}

void Player::setCharacterType(string cT){
    characterType = cT;
}
void Player::setChronoEnergy(int cE){
    chronoEnergy = cE;
}
void Player::setTimeStability(int tS){
    timeStability = tS;
}
void Player::setLuck(int l){
    luck = l;
}
void Player::setSociability(int s){
    sociability = s;
}

void Player::useChronoEnergy(int amount){
    chronoEnergy -= amount;
    if (chronoEnergy < 0){
        chronoEnergy = 0;
    }
}
void Player::lowerTimeStability(int amount){
    timeStability -= amount;
    if (timeStability < 0){
        timeStability = 0;
    }
}

void Player::addItem(string item){
    inventory.push_back(item);
}
void Player::showInventory(){
    cout << "Inventory:" << endl;
    if (inventory.size() == 0) {
        cout << "Empty" << endl;
    }
    else{
        for (size_t i = 0; i < inventory.size(); i++){
            cout << inventory[i] << endl;
        }
    }
}

void Player::displayInfo() const {
    Character::displayInfo();
    cout << "Character Type: " << characterType << endl;
    cout << "Chrono Energy: " << chronoEnergy << endl;
    cout << "Time Stability: " << timeStability << endl;
    cout << "Luck: " << luck << endl;
    cout << "Sociability: " << sociability << endl;
}
