#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
using namespace std;

class Character{
    protected:
        string name;
        int health;
    
    public:
        Character();
        Character(string n, int h);

        string getName();
        int getHealth();

        void setName(string n);
        void setHealth(int h);

        virtual void displayInfo() const;

};

#endif
