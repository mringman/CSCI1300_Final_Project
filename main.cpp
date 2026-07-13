#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

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

void playEgypt(Player &player, Era &egypt, bool &componentRecovered){
    int egyptChoice = 0;

    bool stealingRoute = false;
    bool caughtStealing = false;

    bool priestQuestStarted = false;
    bool marketHelped= false;
    bool hasRoyalSeel = false;

    int theftAttempts = 0;

    cout << endl;
    cout << "You step through the portal..." << endl;

    // cool portal ASQII ART

    cout << "Heat surrounds you as the laboratory disappears." << endl;
    cout << "You have arrived in Ancient Egypt." << endl;

    player.useChronoEnergy(10);

    if (!componentRecovered) {
        int routeChoice;
        cout << endl;

        cout << "A hooded man steps from behind a sandstone wall." << endl;
        cout << endl;
        cout << "Seti: \"You look lost, stranger. I know why you are here.\"" << endl;
        cout << "Seti: \"The priests guard an object known as the "
             << "Scarab of the Endless Dawn.\"" << endl;
        cout << "Seti: \"Help me steal it from the crypt tonight, "
             << "and we can both leave richer.\"" << endl;
        
        cout << endl;
        cout << "1. Agree to help Seti steal the scarab" << endl;
        cout << "2. Refuse and find an honest way" << endl;
        cout << "Enter Choice: ";
        cin >> routeChoice;

        while (cin.fail() || routeChoice < 1 || routeChoice > 2) {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "Invalid input. Enter 1 or 2: ";
            cin >> routeChoice;
        }

        if (routeChoice == 1) {
            stealingRoute = true;
            cout << endl;
            cout << "Seti smiles." << endl;
            cout << "Seti: \"Meet me at the crypt when you are ready.\"" << endl;
        }
        else {
            stealingRoute = false;

            cout << endl;
            cout << "Seti shakes his head." << endl;
            cout << "Seti: \"Fine. Waste your time winning over priests and merchants.\"" << endl;
        }
    }

    while (egyptChoice != 4 &&
            player.getChronoEnergy() > 0 &&
            !componentRecovered) {

        cout << endl;
        cout << "======== ANCIENT EGYPT ========" << endl;
        egypt.displayEra();

        cout << endl;
        cout << "Chrono Energy: " << player.getChronoEnergy() << endl;

        if (caughtStealing){
            cout << "Status: The guards are suspicious of you." << endl;
        }
        if (marketHelped){
            cout << "Status: You helped people in the market." << endl;
        }
        if (hasRoyalSeel){
            cout << "Status: You have permission to enter the crypt." << endl;
        }
        cout << endl;

        cout << "1. Explore the Crypt" << endl;
        cout << "2. Visit the Worship Center" << endl;
        cout << "3. Search the Market" << endl;
        cout << "4. Return to the Time Portal" << endl;
        cout << "Enter Choice: ";
        cin >> egyptChoice;

        while (cin.fail() || egyptChoice < 1 || egyptChoice > 4) {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "Invalid input. Enter a number 1-4: ";
            cin >> egyptChoice;
        }

        cout << endl;

        switch (egyptChoice) {
            case 1: {
                cout << "You approach the ancient crypt." << endl;
                if (hasRoyalSeel){
                    cout << "There is a guard waiting infront of the entrance." << endl;
                    cout << "Guard: \"I see you have a Royal Seel from the High Priest."
                         << "I need to examine it.\"" << endl;
                    cout << "Guard: \"You may enter\"" << endl;
                    cout << "You enter a chamber fulled with golden light." << endl;
                    cout << "At its center rests the Scarab of Endless Dawn." << endl;
                    cout << "You carefully recover the missing component." << endl;
                    componentRecovered = true;
                }
                else if (stealingRoute){
                    int theftChoice;

                    cout << endl;
                    cout << "Seti waits for you in the shadows." << endl;
                    cout << "Seti: \"The guards are chaning positions. "
                         << "This is our chance\"" << endl;
                    cout << endl;

                    cout << "1. Attempt to sneak past the guards" << endl;
                    cout << "2. Back out and return to the city" << endl;
                    cout << "Enter Choice: ";
                    cin >> theftChoice;

                    while (cin.fail() || theftChoice < 1 || theftChoice > 2) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        
                        cout << "Invalid Choice. Enter 1 or 2: ";
                        cin >> theftChoice;
                    }
                    if (theftChoice == 1) {
                        theftAttempts ++;
                        stealingRoute = true;

                        int roll = rand() % 10 + 1;

                        if (roll <= player.getLuck()){
                            cout << "You quietly sneak past the guards." << endl;
                            cout << "Seti grins as you recover the Scarab of the Endless Dawn." << endl;

                            componentRecovered = true;
                        }
                        else{
                            caughtStealing = true;

                            int energyPenalty = 5 + theftAttempts * 5;

                            cout << "A guard spots you!" << endl;
                            cout << "You barely excape." << endl;
                            cout << "You lose " << energyPenalty << " Chrono Energy." << endl;

                            player.useChronoEnergy(energyPenalty);

                            if (player.getChronoEnergy() > 0) {
                                int failureChoice;

                                cout << endl;
                                cout << "Seti: \"That was too close. We can try again, "
                                     << "or you can crawl back to the priests.\"" << endl;
                                
                                cout << endl;
                                cout << "1. Try stealing it again later" << endl;
                                cout << "2. Abandon the theft and earn trust" << endl;
                                cout << "3. Leave Egypt" << endl;
                                cout << "Enter Choice: ";
                                cin >> failureChoice;

                                while (cin.fail() || failureChoice < 1 || failureChoice > 3){
                                    cin.clear();
                                    cin.ignore(1000, '\n');

                                    cout << "Invalid input. Enter a number 1-3";
                                    cin >> failureChoice;
                                }
                                if (failureChoice == 1){
                                    cout << endl;
                                    cout << "Seti: \"Return when you are ready to try again. \"" << endl;
                                }
                                else if (failureChoice == 2){
                                    stealingRoute = false;
                                    cout << endl;
                                    cout << "Seti scoffs and disappears into the shadows." << endl;
                                    cout << "You decide to seek help from the priests and townspeople." << endl;
                                }
                                else{
                                    egyptChoice = 4;
                                    cout << endl;
                                    cout << "You decide to leave Egypt for now." << endl;
                                }
                            }
                        }
                    }
                    else {
                        cout << "You decide that the attempt is too dangerous." << endl;
                        stealingRoute = false;
                    }
                }
                else {
                    cout << "A temple guard blocks the crypt entrance." << endl;
                    cout << endl;
                    cout << "Guard: \"This crypt is sacred. Travelers are not permitted inside\"" << endl;
                    cout << "Guard: \"Speak with the High Priest at the Worship Center "
                         << " if you seek permission\"" << endl;
                }
                break;
            }

            case 2: {
                cout << "You enter the Worship Center." << endl;
                cout << "Incense fills the air as you approach High Priest Anhur." << endl;

                player.useChronoEnergy(2);

                if (hasRoyalSeel){
                    cout << endl;
                    cout << "High Priest Anhur: \"You already have me seal. "
                         << "The crypt guard will allow you to enter \"" << endl;
                }
                else if (!priestQuestStarted) {
                    priestQuestStarted = true;

                    cout << endl;

                    if (caughtStealing) {
                        cout << "High Priest Anhur: \"The guards saw you near "
                             << "the crypt after dark.\"" << endl;
                        cout << "High Priest Anhur: \"I have little reason to "
                             << "trust you, but trust can still be earned throug action.\"" << endl;
                    }
                    else {
                        cout << "High Priest Anhur: \"You seek the Scarab of the Endless Dawn, "
                             << "but why should we trust you?\"" << endl;
                    }
                    cout << "High Priest Anhur: \"The market's water jars were "
                         << "destroyed during the sandstorm. Help our people, "
                         << "then return to me.\"" << endl;
                }
                else if (!marketHelped) {
                    cout << endl;
                    cout << "High Priest Anhur: \"The people in the market still need you help.\"" << endl;
                }
                else {
                    hasRoyalSeel = true;

                    cout << "High Priest Anhur: \"The merchants have told me "
                         << "what you did for them.\"" << endl;
                    
                    if (caughtStealing) {
                        cout << "High Priest Anhur: \"Your earlier actions were "
                             << "dishonorable, but your service proves that you can change.\"" << endl;
                    }
                    else{
                        cout << "High Priest Anhur: \"You sought our greatest "
                             << "treasure, yet chose to help our people first.\"" << endl;
                    }

                    cout << "High Priest Anhur: \"The scarab's power has become unstable. "
                         << "Perhaps it no longer belongs in this time.\"" << endl;
                    cout << "High Priest Anhur gives you a royal seal." << endl;
                    cout << "You may now enter the crypt and recover the scarab." << endl;
                }
                break;
            }

            case 3:{
                cout << "You enter the crowded market." << endl;
                cout << "A merchant named Nefru stands beside several broken water jars." << endl;
                player.useChronoEnergy(2);

                if (marketHelped){
                    cout << endl;
                    cout << "Nefru: \"The people still speak of the stranger who helped us. Thank you.\"" << endl;
                }
                else{
                    int helpChoice;

                    cout << endl;
                    cout << "Nefru: \"The sandstorm destroyed our water jars. "
                         << "Several families now have nothing to drink.\"" << endl;
                    
                    cout << endl;
                    cout << "1. Help carry replacement water jars" << endl;
                    cout << "2. Refuse to help" << endl;
                    cout << "Enter Choice: ";
                    cin >> helpChoice;

                    while (cin.fail() || helpChoice < 1 || helpChoice > 2){
                        cin.clear();
                        cin.ignore(1000, '\n');

                        cout << "Invalid input. Enter 1 or 2: ";
                        cin >> helpChoice;
                    }

                    if (helpChoice == 1) {
                        player.useChronoEnergy(5);
                        marketHelped = true;

                        cout << endl;
                        cout << "You spend the afternoon carrying heavy clay jars through the market." << endl;
                        cout << "The merchants begin speaking of the stranger who helped without asking for payment." << endl;

                        if (!priestQuestStarted) {
                            cout << "Nefru: \"I suggest you speak with the High Priest Anhur at the Worship Center." << endl;
                        }
                    }
                    else {
                        cout << endl;
                        cout << "Nefu turns away disappointed." << endl;
                    }
                }
                break;
            }
            case 4:
                if (!componentRecovered){
                    string decision;
                    cout << "Are you sure? You haven't found this eras device." << endl;
                    cout << "Return through the portal (Y) / Stay in Egypt (N): ";
                    cin >> decision;

                    while (decision != "y" && decision != "Y" && decision != "n" && decision != "N") {
                        cout << "Invalid input. Enter a number Y/N: ";
                        cin >> decision;
                    }
                    if (decision == "Y" || decision == "y"){
                        cout << "You return to the time portal." << endl;
                        break;
                    }
                    else if (decision == "N" || decision == "n") {
                        egyptChoice = 0;
                        break;
                    }
                    
                    }
                else{
                    cout << "You return to the time portal." << endl;
                }
                break;    
        }
    }
}


void displayPortalMenu(
    Player &player, 
    Era &egypt,
    bool &egyptComponentRecovered){

        int portalChoice = 0;

        while (portalChoice != 5){
            cout << endl;
            cout << "======== TIME PORTALS ========" << endl;
            cout << "1. Ancient Egypt" << endl;
            cout << "2. Wild West - UNDER CONSTRUCTION" << endl;
            cout << "3. Future 2352 - UNDER CONSTRUCTION" << endl;
            cout << "4. Area 51, 1982 - UNDER CONSTRUCTION" << endl;
            cout << "5. Return to Main Menu" << endl;
            cout << "Enter Choice: ";
            cin >> portalChoice;

            while (cin.fail() || portalChoice < 1 || portalChoice > 5){
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invlaid input. Enter a number 1-5: ";
                    cin >> portalChoice;
            }
            cout << endl;
            cout << endl;

            switch (portalChoice) {
                case 1:
                    cout << "You step through the portal to Ancient Egypt." << endl;
                    playEgypt(player, egypt, egyptComponentRecovered);
                    break;
                case 2:
                    cout << "This portal is not stable" << endl;
                    break;
                case 3:
                    cout << "This portal is not stable" << endl;
                    break;
                case 4:
                    cout << "This portal is not stable" << endl;
                    break;
                case 5:
                cout << "You step away from the portals." << endl;
            }
        }

}


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
    bool egyptComponentRecovered = false;

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
    int maxMenuChoice = 5;

    while (menuChoice != maxMenuChoice){
        cout << endl;
        cout << "========== MAIN MENU ==========" << endl;
        cout << "1. View Player Stats" << endl;
        cout << "2. Talk to Dr. Baige" << endl;
        cout << "3. View Laboratory Map" << endl;
        cout << "4. Enter a Time Portal" << endl;
        cout << "5. Quit Game" << endl;
        cout << "Enter Choice: ";
        cin >> menuChoice;

        while (cin.fail() || menuChoice < 1 || menuChoice > maxMenuChoice){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Enter a number 1-" << maxMenuChoice << endl;
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
                displayPortalMenu(player, egypt, egyptComponentRecovered);
                break;
            case 5:
                cout << "Thanks for playing Temporal Collapse!" << endl;
                break;
        }

        if (player.getChronoEnergy() <= 0) {
            cout << "You ran out of Chrono Energy." << endl;
            cout << "The time machine shuts down and you are stranded in time." << endl;
            menuChoice = maxMenuChoice;
        }
    }


    return 0;
}
