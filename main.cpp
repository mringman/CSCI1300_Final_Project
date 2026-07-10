#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "player.h"
#include "NPC.h"
#include "era.h"

using namespace std;

struct CharacterChoice {
    string type;
    int chronoEnergy;
    int timeStability;
    int luck;
    int sociability;
};

int loadCharacterChoices(string filename, CharacterChoice choices[], int maxChoices){
    ifstream file(filename);

    if (!file.is_open()){
        return -1;
    }

    string line;
    int count = 0;

    getline(file, line);

    while (getline(file, line) && count < maxChoices){
        stringstream ss(line);

        string type;
        string chronoEnergyStr;
        string timeStabilityStr;
        string luckStr;
        string sociabilityStr;

        getline(ss, type, ',');
        getline(ss, chronoEnergyStr, ',');
        getline(ss, timeStabilityStr, ',');
        getline(ss, luckStr, ',');
        getline(ss, sociabilityStr, ',');

        choices[count].type = type;
        choices[count].chronoEnergy = stoi(chronoEnergyStr);
        choices[count].timeStability = stoi(timeStabilityStr);
        choices[count].luck = stoi(luckStr);
        choices[count].sociability = stoi(sociabilityStr);
        
        count++;
    }
    
    file.close();

    return count;
}

Player choosePlayer(CharacterChoice choices[], int numChoices){
    string playerName;
    int choice;

    cout << "Enter your player name: ";
    getline(cin, playerName);

    cout << endl;
    cout << "Choose your character type: " << endl;

    for (int i = 0; i < numChoices; i++){
        cout << i + 1 << ". " << choices[i].type << endl;
        cout << "    Chrono Energy: " << choices[i].chronoEnergy << endl;
        cout << "    Time Stability: " << choices[i].timeStability << endl;
        cout << "    Luck: " << choices[i].luck << endl;
        cout << "    Sociability: " << choices[i].sociability << endl;
        cout << endl;
    }

    cout << "Enter Choice: ";
    cin >> choice;

    while (cin.fail() || choice < 1 || choice > numChoices){
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Invalid Choice. Enter a number between 1 and " << numChoices << endl;
        cin >> choice;
    }
    cin.ignore(1000, '\n');

    int index = choice - 1;

    Player player(
        playerName,
        choices[index].type,
        choices[index].chronoEnergy,
        choices[index].timeStability,
        choices[index].luck,
        choices[index].sociability
    );

    return player;
}

int main(){
    CharacterChoice choices[10];

    int loaded = loadCharacterChoices("playerClasses.txt", choices, 10);

    if (loaded <= 0) {
        cout << "Error: could not load playerClasses.txt" << endl;
        return 1;
    }

    cout << "==============================" << endl;
    cout << "      TEMPORAL COLLAPSE       " << endl;
    cout << "==============================" << endl;
    cout << endl;

    Player player = choosePlayer(choices, loaded);

    NPC scientist(
        "Dr. Baige",
        100,
        "The time machine has collapsed. You need to recover the lost stability components.",
        "Recover the missing components across time.",
        "Chrono key"
    );

    Era laboratory("Laboratory");
    laboratory.addSubLocation("Portals");
    laboratory.addSubLocation("Workbench");
    laboratory.addSubLocation("Changingroom");

    Era egypt("Ancient Egypt");
    egypt.addSubLocation("Crypt");
    egypt.addSubLocation("Worship Center");
    egypt.addSubLocation("Market");

    Era wildWest("Wilde West");
    wildWest.addSubLocation("Gold Mine");
    wildWest.addSubLocation("Town Saloon");
    wildWest.addSubLocation("Oldman Jankins Cabin");

    Era future("2352");
    future.addSubLocation("Research Facility");
    future.addSubLocation("AI workshop");
    future.addSubLocation("Park");

    Era area51("Area 51 - 1982");
    area51.addSubLocation("Labratory");
    area51.addSubLocation("Warehouse");
    area51.addSubLocation("Cafeteria");

    int menuChoice = 0;

    while (menuChoice != 8){
        cout << endl;
        cout << "========== MAIN MENU ==========" << endl;
        cout << "1. View Player Stats" << endl;
        cout << "2. Talk to Dr. Baige" << endl;
        cout << "3. View Laboratory Map" << endl;
        cout << "4. Travel to Ancient Egypt" << endl;
        cout << "5. Travel to Wild West" << endl;
        cout << "6. Travel to The Future - 2352" << endl;
        cout << "7. Travel to Area 51 - 1982" << endl;
        cout << "8. Quit Game" << endl;
        cout << "Enter Choice: ";
        cin >> menuChoice;

        while (cin.fail() || menuChoice < 1 || menuChoice > 8){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Enter a number 1-8. ";
            cin >> menuChoice;
        }

        cout << endl;

        switch (menuChoice){
            case 1:
                player.displayInfo();
                break;
            case 2:
                scientist.speak();
                break;
            case 3:
                laboratory.displayEra();
                break;
            case 4:
                cout << "You travel to Ancient Egypt." << endl;
                player.useChronoEnergy(10);
                egypt.displayEra();
                break;
            case 5:
                cout << "You travel to the Wild West." << endl;
                player.useChronoEnergy(15);
                wildWest.displayEra();
                break;
            case 6:
                cout << "You travel to the Future - 2352" << endl;
                player.useChronoEnergy(10);
                future.displayEra();
                break;
            case 7:
                cout << "You travel to Area 51 - 1982" << endl;
                player.useChronoEnergy(7);
                area51.displayEra();
                break;
            case 8:
                cout << "Thanks for playing Temoral Collapse!" << endl;
                break;
        }

        if (player.getChronoEnergy() <= 0) {
            cout << "You ran out of Chrono Energy." << endl;
            cout << "The time machine shuts down and you are stranded in time." << endl;
            menuChoice = 8;
        }
    }


    return 0;
}
