#include "character.h"
#include <iostream>
using namespace std;

Character::Character(){
    name = "Unknown";
    health = 100;
}
Character::Character(string n, int h){
    name = n;
    health = h;
}

string Character::getName(){
    return name;
}
int Character::getHealth(){
    return health;
}

void Character::setName(string n){
    name = n;
}
void Character::setHealth(int h){
    health = h;
}

void Character::displayInfo() const{
    cout << "Name: " << name << endl;
    cout << "Health: " << health << endl;
}
