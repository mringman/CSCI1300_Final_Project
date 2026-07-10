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
void Era::displayEra(){
    cout << "Era: " << eraName << endl;
    cout << "Locations: " << endl;

    for (size_t i = 0; i < subLocations.size(); i++){
        cout << i + 1 << ". " << subLocations[i] << endl;
    }

    if (componentFound) {
        cout << "Component Status: Found" << endl;
    }
    else{
        cout << "Component Status: Missing" << endl;
    }
}
