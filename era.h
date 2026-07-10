#ifndef ERA_H
#define ERA_H

#include <string>
#include <vector>
using namespace std;

class Era {
    private:
        string eraName;
        vector<string> subLocations;
        bool componentFound;
    
    public:
        Era();
        Era(string name);

        string getEraName();
        bool getComponentFound();

        void setEraName(string name);
        void setComponentFound(bool found);

        void addSubLocation(string location);
        void displayEra();
    
};


#endif
