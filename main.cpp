#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

#include "player.h"
#include "NPC.h"
#include "era.h"

using namespace std;

void printPortal(){
    ifstream portalFile("portal.txt");

    if (!portalFile.is_open()) {
        cout << "Error: could not open portal.txt" << endl;
        return;

    }
    string line;

    while (getline(portalFile, line)) {
        cout << line << endl;
    }

    portalFile.close();
}

void waitSecond(int seconds){
    this_thread::sleep_for(chrono::seconds(seconds));
}

struct CharacterChoice {
    string type;
    int chronoEnergy;
    int timeStability;
    int luck;
    int sociability;
};

struct EgyptState{
    bool visitedEgypt;
    bool stealingRoute;
    bool caughtStealing;
    bool priestQuestStarted;
    bool marketHelped;
    bool hasRoyalSeal;
    int theftAttempts;
};

struct EgyptResult {
    Player player;
    Era egypt;
    bool componentRecovered;
    EgyptState state;
};

struct WildWestState{
    bool visitedWildWest;
    bool metWade;
    bool stealingRoute;
    bool toldSheriff;
    bool stagecoachStolen;
    bool wadeArrested;
    bool helpedJankins;
};

struct WildWestResult {
    Player player;
    Era wildWest;
    bool componentRecovered;
    WildWestState state;
};

struct FutureState {
    bool visitedFuture;

    bool metNyx;
    bool smugglingRoute;
    bool hasTunnelCode;
    bool breakInAttempted;

    bool repairQuestStarted;
    bool aiRepaired;
    bool hasClearanceChip;

    bool securityAlerted;
    int hackingAttempts;
};

struct FutureResult {
    Player player;
    Era future;
    bool componentRecovered;
    FutureState state;
};

void enterToContinue(){
    cout << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << endl;
    cout << "              Press Enter to Continue..." << endl;
    cout << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << endl;
    cin.get();

}

int getValidatedChoice(int min, int max){
    int choice;

    cin >> choice;

    while (cin.fail() || choice < min || choice > max){
        cin.clear();
        cin.ignore(1000, '\n');
        
        cout << "Invalid input. Enter a number " << min << "-" << max << endl;

        cin >> choice;
    }
    cin.ignore(1000, '\n');
    return choice;
}

EgyptResult playEgypt(
    Player player,
    Era egypt, 
    bool componentRecovered, 
    EgyptState state
){
    if(componentRecovered) {
        cout << endl;
        cout << "You have already recovered the Scarab of the Endless Dawn." << endl;
        cout << "There is no reason to return to Ancient Egypt." << endl;
        EgyptResult result = {player, egypt, componentRecovered, state};
        return result;
    }

    int egyptChoice = 0;

    cout << endl;
    cout << "You step through the portal..." << endl;

    waitSecond(3);

    printPortal();

    waitSecond(3);

    // cool portal ASQII ART
    cout << endl;
    cout << "Heat surrounds you as the laboratory disappears." << endl;
    cout << "You have arrived in Ancient Egypt." << endl;

    player.useChronoEnergy(10);
    player.lowerTimeStability(5);

    enterToContinue();

    if (state.visitedEgypt){
        cout << endl;
        cout << "Seti walks over as you step away from the portal." << endl;
        if (state.hasRoyalSeal) {
            cout << "Seti: \"You're back. And I see you have a Royal Seal. Impressive.\"" << endl;
            cout << "Seti: \"You can go into the Crypt with that.\"" << endl;
            cout << "Seti: \"But, stealing it would be much more exciting.\"" << endl;
        }
        else if (state.stealingRoute) {
            cout << "Seti: \"You're back! Are you still ready to steal the scarab?\"" << endl;
        }
        else{
            cout << "Seti: \"You're back! Done helping people yet?\"" << endl;
            cout << "Seti: \"You should reconsider my plan.\"" << endl;
            cout << "Seti: \"Stealing the scarab will be much faster.\"" << endl;
        }
        
    }
    
    else{
        state.visitedEgypt = true;
        if (!componentRecovered) {
            int routeChoice;
            egypt.markNPCTalkedTo("Seti");
            cout << endl;

            cout << "A hooded man steps from behind a sandstone wall." << endl;
            cout << "Seti: \"You look lost, stranger. I know why you are here.\"" << endl;
            
            enterToContinue();

            cout << "Seti: \"The priests guard an object known as the "
                << "Scarab of the Endless Dawn.\"" << endl;
            cout << "Seti: \"Help me steal it from the crypt tonight, "
                << "and we can both leave richer.\"" << endl;

            cout << endl;
            cout << "1. Agree to help Seti steal the scarab" << endl;
            cout << "2. Refuse and find an honest way" << endl;
            cout << "Enter Choice: ";

            routeChoice = getValidatedChoice(1,2);

            if (routeChoice == 1) {
                state.stealingRoute = true;

                player.useChronoEnergy(5);
                player.lowerTimeStability(5);

                cout << endl;
                cout << "Seti smiles." << endl;
                cout << "Seti: \"Meet me at the crypt when you are ready.\"" << endl;
                cout << endl;
                cout << "Preparing the risky plan cost you 5 Chrono Energy and 5 Time Stability." << endl;
            }
            else {
                state.stealingRoute = false;

                cout << endl;
                cout << "Seti shakes his head." << endl;
                cout << "Seti: \"Fine. Waste your time winning over priests and merchants.\"" << endl;
            }
        }
    }
   
    enterToContinue();

    while (egyptChoice != 4 &&
            player.getChronoEnergy() > 0 &&
            player.getTimeStability() > 0 &&
            !componentRecovered) {

        cout << endl;
        cout << "======== ANCIENT EGYPT ========" << endl;
        egypt.displayEra();

        cout << endl;
        cout << "Chrono Energy: " << player.getChronoEnergy() << endl;
        cout << "Time Stability: " << player.getTimeStability() << endl;

        if (state.caughtStealing){
            cout << "Status: The guards are suspicious of you." << endl;
        }
        if (state.marketHelped){
            cout << "Status: You helped people in the market." << endl;
        }
        if (state.hasRoyalSeal){
            cout << "Status: You have permission to enter the crypt." << endl;
        }
        enterToContinue();

        cout << "1. Explore the Crypt" << endl;
        cout << "2. Visit the Worship Center" << endl;
        cout << "3. Search the Market" << endl;
        cout << "4. Return to the Time Portal" << endl;
        cout << "Enter Choice: ";

        egyptChoice = getValidatedChoice(1,4);
        cout << endl;

        switch (egyptChoice) {
            case 1: {
                cout << "You approach the ancient crypt." << endl;
                if (state.hasRoyalSeal){
                    cout << "There is a guard waiting in front of the entrance." << endl;
                    cout << "Guard: \"I see you have a Royal Seal from the High Priest. "
                         << "I need to examine it.\"" << endl;
                    
                    enterToContinue();

                    cout << "Guard: \"You may enter.\"" << endl;
                    cout << "You enter a chamber filled with golden light." << endl;
                    cout << "At its center rests the Scarab of the Endless Dawn." << endl;
                    cout << "You carefully recover the missing component." << endl;
                    player.addItem("Scarab of the Endless Dawn");
                    egypt.setComponentFound(true);
                    componentRecovered = true;

                    enterToContinue();
                }

                else if (state.stealingRoute){
                    int theftChoice;

                    cout << endl;
                    cout << "Seti waits for you in the shadows." << endl;
                    cout << "Seti: \"The guards are changing positions."
                         << "This is our chance.\"" << endl;
                    cout << endl;

                    enterToContinue();

                    cout << "1. Attempt to sneak past the guards" << endl;
                    cout << "2. Back out and return to the city" << endl;
                    cout << "Enter Choice: ";

                    theftChoice = getValidatedChoice(1,2);

                    if (theftChoice == 1) {
                        state.theftAttempts ++;
                        state.stealingRoute = true;

                        int roll = rand() % 10 + 1;

                        if (roll <= player.getLuck()){
                            cout << endl;
                            cout << "You quietly sneak past the guards." << endl;
                            cout << "Seti grins as you recover the Scarab of the Endless Dawn." << endl;

                            player.addItem("Scarab of the Endless Dawn");
                            egypt.setComponentFound(true);
                            componentRecovered = true;

                            enterToContinue();
                        }
                        else{
                            state.caughtStealing = true;

                            int energyPenalty = 5 + state.theftAttempts * 5;
                            cout << endl;
                            cout << "A guard spots you!" << endl;
                            cout << "You barely escape." << endl;
                            cout << "You lose " << energyPenalty << " Chrono Energy." << endl;

                            player.useChronoEnergy(energyPenalty);

                            enterToContinue();

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

                                failureChoice = getValidatedChoice(1,3);

                                if (failureChoice == 1){
                                    cout << endl;
                                    cout << "Seti: \"Return when you are ready to try again. \"" << endl;
                                    enterToContinue();
                                }
                                else if (failureChoice == 2){
                                    state.stealingRoute = false;
                                    cout << endl;
                                    cout << "Seti scoffs and disappears into the shadows." << endl;
                                    cout << "You decide to seek help from the priests and townspeople." << endl;
                                    enterToContinue();
                                }
                                else{
                                    egyptChoice = 4;
                                    cout << endl;
                                    cout << "You decide to leave Egypt for now." << endl;
                                    enterToContinue();
                                }
                            }
                        }
                    }
                    else {
                        cout << endl;
                        cout << "You decide that the attempt is too dangerous." << endl;
                        state.stealingRoute = false;
                        enterToContinue();
                    }
                }
                else {
                    cout << endl;
                    cout << "A temple guard blocks the crypt entrance." << endl;
                    cout << endl;
                    cout << "Guard: \"This crypt is sacred. Travelers are not permitted inside.\"" << endl;
                    cout << "Guard: \"Speak with the High Priest at the Worship Center "
                         << "if you seek permission.\"" << endl;
                    
                     enterToContinue();
                }
                break;
            }

            case 2: {
                cout << endl;
                cout << "You enter the Worship Center." << endl;
                cout << "Incense fills the air as you approach High Priest Anhur." << endl;
                enterToContinue();

                player.useChronoEnergy(2);

                if (state.hasRoyalSeal){
                    cout << endl;
                    cout << "High Priest Anhur: \"You already have my seal. "
                         << "The crypt guard will allow you to enter.\"" << endl;
                    enterToContinue();
                }
                else if (!state.priestQuestStarted) {
                    egypt.markNPCTalkedTo("High Priest Anhur");
                    state.priestQuestStarted = true;

                    if (state.caughtStealing) {
                        cout << "High Priest Anhur: \"The guards saw you near "
                             << "the crypt after dark.\"" << endl;
                        cout << "High Priest Anhur: \"I have little reason to "
                             << "trust you, but trust can still be earned through action.\"" << endl;
                        enterToContinue();
                    }
                    else {
                        cout << "High Priest Anhur: \"You seek the Scarab of the Endless Dawn, "
                             << "but why should we trust you?\"" << endl;
                        enterToContinue();

                        if(player.getSociability() >= 8 && !state.marketHelped){
                            state.hasRoyalSeal = true;

                            cout << "You calmly explain the danger caused by the unstable scarab." << endl;
                            cout << "Your words convince High Priest Anhur that you can be trusted." << endl;
                            cout << "You may now enter the crypt." << endl;

                            enterToContinue();
                        }
                    }
                    if (!state.hasRoyalSeal && state.marketHelped){
                        state.hasRoyalSeal = true;
                        cout << "High Priest Anhur: \"The Merchants have already told me of your help.\"" << endl;
                        cout << "High Priest Anhur: \"Your actions have earned our trust.\"" << endl;
                        cout << endl;
                        cout << "High Priest Anhur gives you a royal seal." << endl;
                        cout << "You may now enter the crypt and recover the scarab." << endl;

                        enterToContinue();
                    }
                    else if (!state.hasRoyalSeal){
                        cout << "High Priest Anhur: \"The market's water jars were "
                            << "destroyed during the sandstorm. Help our people, "
                            << "then return to me.\"" << endl;
                        enterToContinue();
                    }
                }
                else if (!state.marketHelped) {
                    cout << endl;
                    cout << "High Priest Anhur: \"The people in the market still need your help.\"" << endl;
                    enterToContinue();
                }
                else {
                    state.hasRoyalSeal = true;

                    cout << "High Priest Anhur: \"The merchants have told me "
                         << "what you did for them.\"" << endl;
                    enterToContinue();
                    
                    if (state.caughtStealing) {
                        cout << "High Priest Anhur: \"Your earlier actions were "
                             << "dishonorable, but your service proves that you can change.\"" << endl;
                        enterToContinue();
                    }
                    else{
                        cout << "High Priest Anhur: \"You sought our greatest "
                             << "treasure, yet chose to help our people first.\"" << endl;
                        enterToContinue();
                    }

                    cout << "High Priest Anhur: \"The scarab's power has become unstable. "
                         << "Perhaps it no longer belongs in this time.\"" << endl;
                    cout << "High Priest Anhur gives you a royal seal." << endl;
                    cout << "You may now enter the crypt and recover the scarab." << endl;
                    enterToContinue();
                }
                break;
            }

            case 3:{
                cout << "You enter the crowded market." << endl;
                cout << "A merchant named Nefru stands beside several broken water jars." << endl;
                player.useChronoEnergy(2);
                enterToContinue();

                if (state.marketHelped){
                    cout << endl;
                    cout << "Nefru: \"The people still speak of the stranger who helped us. Thank you.\"" << endl;
                    enterToContinue();
                }
                else{
                    egypt.markNPCTalkedTo("Nefru");
                    int helpChoice;

                    cout << endl;
                    cout << "Nefru: \"The sandstorm destroyed our water jars. "
                         << "Several families now have nothing to drink.\"" << endl;
                    enterToContinue();
                    
                    cout << endl;
                    cout << "1. Help carry replacement water jars" << endl;
                    cout << "2. Refuse to help" << endl;
                    cout << "Enter Choice: ";

                    helpChoice = getValidatedChoice(1,2);

                    if (helpChoice == 1) {
                        player.useChronoEnergy(5);
                        state.marketHelped = true;

                        cout << endl;
                        cout << "You spend the afternoon carrying heavy clay jars through the market." << endl;
                        cout << "The merchants begin speaking of the stranger who helped without asking for payment." << endl;

                        enterToContinue();

                        if (!state.priestQuestStarted) {
                            cout << "Nefru: \"I suggest you speak with the High Priest Anhur at the Worship Center.\"" << endl;
                            enterToContinue();
                        }
                    }
                    else {
                        cout << endl;
                        cout << "Nefru turns away disappointed." << endl;
                        enterToContinue();
                    }
                }
                break;
            }
            case 4:
                if (!componentRecovered){
                    string decision;
                    cout << "Are you sure? You haven't found this era's device." << endl;
                    cout << "Return through the portal (Y) / Stay in Egypt (N): ";
                    cin >> decision;

                    while (decision != "y" && decision != "Y" && decision != "n" && decision != "N") {
                        cout << "Invalid input. Enter Y or N: ";
                        cin >> decision;
                    }
                    cin.ignore(1000, '\n');
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

    EgyptResult result = {
        player,
        egypt,
        componentRecovered,
        state
    };
    return result;
}

WildWestResult playWildWest(
    Player player,
    Era wildWest,
    bool componentRecovered,
    WildWestState state
){
    if (componentRecovered && state.helpedJankins) {
        cout << endl;
        cout << "You have already recovered the Temporal Cog." << endl;
        cout << "There is no reason to return to the Wild West." << endl;

        if (player.getChronoEnergy() <= 0) {
            cout << endl;
            cout << "Your Chrono Energy has been depleted." << endl;
            cout << "The time machine can no longer bring you home." << endl;
            cout << "GAME OVER" << endl;

            enterToContinue();
        }
        else if (player.getTimeStability() <= 0) {
            cout << endl;
            cout << "Time Stability has reached zero." << endl;
            cout << "The portal collapses around you." << endl;
            cout << "GAME OVER" << endl;

            enterToContinue();
        }

        WildWestResult result = {
            player,
            wildWest,
            componentRecovered,
            state
        };
        return result;
    }

    int wildWestChoice = 0;
    cout << endl;
    cout << "The laboratory disappears behind a cloud of dust." << endl;

    waitSecond(3);

    printPortal();

    waitSecond(3);

    cout << "You arrive in a small Wild West town." << endl;

    player.useChronoEnergy(10);
    player.lowerTimeStability(5);

    if (!state.visitedWildWest){
        state.visitedWildWest = true;

        cout << endl;
        cout << "A wounded miner stumbles toward you." << endl;
        cout << "Miner: \"The gold mine collapsed. We found some kind of brass "
             << "gear buried in the rock.\"" << endl;
        cout << "Miner: \"Hank struck it with his pickaxe, and the whole mine "
             << "lit up blue before the tunnels came down!\"" << endl;
        cout << "Miner: \"That strange gear is still trapped inside.\"" << endl;
    }
    else {
        cout << endl;
        cout << "You return to the dusty frontier town." << endl;
        cout << "The collapsed mine still waits in the distance." << endl;
    }
    enterToContinue();

    while (wildWestChoice !=4 &&
           player.getChronoEnergy() > 0 &&
           player.getTimeStability() > 0 &&
           !(componentRecovered &&
           state.helpedJankins)) {
    
        int robberyDecision;
        cout << endl;
        cout << "========= WILD WEST =========" << endl;
        wildWest.displayEra();

        cout << endl;
        cout << "Chrono Energy: " << player.getChronoEnergy() << endl;
        cout << "Time Stability: " << player.getTimeStability() << endl;

        enterToContinue();

        cout << "1. Visit the Gold Mine" << endl;
        cout << "2. Enter the Town Saloon" << endl;
        cout << "3. Visit Old Man Jankins' Cabin" << endl;
        cout << "4. Return to the Time Portal" << endl;
        cout << "Enter Choice: ";

        wildWestChoice = getValidatedChoice(1,4);

        switch (wildWestChoice) {
            case 1: {
                cout << endl;
                if (componentRecovered) {
                    cout << "The Temporal Cog has already been recovered from the mine." << endl;

                    if (!state.helpedJankins) {
                        cout << "Before leaving town, you should visit Old Man Jankins." << endl;
                    }
                    enterToContinue(); 
                }
                else if (state.stealingRoute && state.stagecoachStolen) {
                    cout << "You arrive at the collapsed mine." << endl;
                    cout << "Wade Blackwell stands beside the stolen stagecoach." << endl;
                    cout << "Several crates of dynamite are stacked near the entrance." << endl;

                    enterToContinue();

                    cout << "Wade Blackwell: \"There you are, partner.\"" << endl;
                    cout << "Wade Blackwell: \"We'll use the dynamite to clear those rocks.\"" << endl;
                    cout << "Wade Blackwell: \"Stand back. This is gonna be loud.\"" << endl;

                    enterToContinue();

                    int explosionRoll = rand() % 10 + 1;

                    if (explosionRoll <= player.getLuck()) {
                        cout << "Wade lights the fuse, and you both run for cover." << endl;
                        cout << "The explosion tears through the fallen rock." << endl;
                        cout << "When the dust clears, the mine entrance is open." << endl;

                        enterToContinue();

                        cout << "You enter the damaged mine and follow a faint blue glow." << endl;
                        cout << "Buried beneath the rubble is the Temporal Cog." << endl;
                        cout << "You carefully recover the missing component." << endl;

                        player.addItem("Temporal Cog");
                        wildWest.setComponentFound(true);
                        componentRecovered = true;

                        enterToContinue();

                        cout << "Wade Blackwell: \"That strange gear is all yours.\"" << endl;
                        cout << "Wade Blackwell: \"I'm taking the rest of the valuables.\"" << endl;
                        cout << "Wade climbs onto the stagecoach and rides away." << endl;

                        enterToContinue();

                        cout << "You remember hearing about Old Man Jankins' cabin." << endl;
                        cout << "Perhaps you should visit him before leaving town." << endl;

                        enterToContinue();

                    }

                    else {

                        cout << "Wade lights the fuse, and you both run for cover." << endl;
                        cout << "The dynamite explodes, sending pieces of rock through the air." << endl;
                        cout << "A chunk of stone strikes you in the head." << endl;
                        cout << "Everything goes dark." << endl;

                        enterToContinue();

                        cout << "You slowly wake up near the mine entrance." << endl;
                        cout << "The sheriff is kneeling beside you." << endl;
                        cout << "Wade and the stolen stagecoach are gone." << endl;

                        enterToContinue();

                        cout << "Sheriff: \"Easy now. I found you unconscious beside the mine.\"" << endl;
                        cout << "Sheriff: \"Want to explain what you were doing out here?\"" << endl;

                        int confessionChoice = 0;

                        while (confessionChoice != 1 &&

                            player.getChronoEnergy() > 0 &&
                            player.getTimeStability() > 0) {

                            cout << endl;
                            cout << "1. Confess that you helped Wade steal the stagecoach" << endl;
                            cout << "2. Lie and claim you were exploring alone" << endl;
                            cout << "Enter Choice: ";
                            confessionChoice = getValidatedChoice(1, 2);

                            if (confessionChoice == 1) {

                                cout << endl;
                                cout << "You confess that you helped Wade steal the stagecoach." << endl;
                                cout << "You explain that you only needed the equipment to "
                                    << "recover the Temporal Cog." << endl;

                                enterToContinue();

                                cout << "Sheriff: \"You made a foolish choice, but telling the "
                                    << "truth counts for something.\"" << endl;
                                cout << "Sheriff: \"Wade left some dynamite behind. I'll help "
                                    << "you open the mine.\"" << endl;

                                enterToContinue();

                                cout << "The sheriff carefully sets the remaining dynamite." << endl;
                                cout << "The explosion clears the mine entrance." << endl;
                                cout << "Inside, you find the Temporal Cog glowing beneath the rubble." << endl;

                                player.addItem("Temporal Cog");
                                wildWest.setComponentFound(true);
                                componentRecovered = true;
                                state.stealingRoute = false;
                                state.toldSheriff = true;

                                enterToContinue();

                                cout << "Sheriff: \"Before you leave town, check on Old Man Jankins.\"" << endl;
                                cout << "Sheriff: \"He lives in the cabin outside town and could use some help.\"" << endl;

                                enterToContinue();
                            }

                            else {
                                cout << endl;
                                cout << "Sheriff: \"Exploring alone, huh?\"" << endl;
                                cout << "Sheriff: \"Then explain the stolen stagecoach tracks "
                                    << "and Wade Blackwell's dynamite.\"" << endl;
                                cout << "The sheriff does not believe your story." << endl;
                                cout << "You lose 5 Chrono Energy and 5 Time Stability." << endl;

                                player.useChronoEnergy(5);
                                player.lowerTimeStability(5);
                                if (player.getChronoEnergy() > 0 &&
                                    player.getTimeStability() > 0) {
                                    cout << endl;
                                    cout << "Sheriff: \"Let's try this again. Tell me the truth.\"" << endl;

                                }

                            }

                        }

                    }

                }
                else if (state.toldSheriff && !state.wadeArrested) {
                    cout << "You arrive at the collapsed mine." << endl;
                    cout << "The sheriff is waiting behind a large boulder." << endl;

                    enterToContinue();

                    cout << "Sheriff: \"Keep your head down. Wade should be here soon.\"" << endl;
                    cout << "A stolen stagecoach approaches through the dust." << endl;
                    cout << "Wade stops near the mine and begins unloading dynamite." << endl;

                    enterToContinue();

                    cout << "Sheriff: \"Now!\"" << endl;
                    cout << "You and the sheriff step out from behind the rocks." << endl;
                    cout << "Sheriff: \"Wade Blackwell! Step away from that dynamite!\"" << endl;

                    enterToContinue();

                    cout << "Wade Blackwell: \"You! I remember you.\"" << endl;

                    if (state.metWade) {
                        cout << "Wade Blackwell: \"You should've taken my offer when you had the chance.\"" << endl;
                    }

                    cout << "Wade reaches toward his revolver, but the sheriff draws first." << endl;
                    cout << "Wade slowly raises his hands." << endl;
                    cout << "The sheriff places him under arrest." << endl;

                    state.wadeArrested = true;
                    enterToContinue();

                    cout << "Sheriff: \"The stagecoach has everything we need to clear the entrance.\"" << endl;
                    cout << "Together, you place the dynamite against the fallen rock." << endl;
                    cout << "The explosion opens a path into the mine." << endl;

                    enterToContinue();

                    cout << "You follow a faint blue glow through the damaged tunnel." << endl;
                    cout << "Beneath the rubble, you find the Temporal Cog." << endl;
                    cout << "You carefully recover the missing component." << endl;

                    player.addItem("Temporal Cog");
                    wildWest.setComponentFound(true);
                    componentRecovered = true;
                    enterToContinue();

                    if (!state.helpedJankins){
                        cout << "Sheriff: \"Before you leave town, visit Old Man Jankins.\"" << endl;
                        cout << "Sheriff: \"He lives alone outside town and could use a helping hand.\"" << endl;
                        
                        enterToContinue();
                    }
                    else{
                        cout << "Sheriff: \"Safe travels. Good luck!\"" << endl;
                    }
                }

                else {

                    cout << "The mine entrance is blocked by fallen rock." << endl;
                    cout << "You will need equipment before you can enter." << endl;
                    cout << "Someone at the town saloon may know how to get it." << endl;

                    enterToContinue();

                }

            break;
            }
                
            case 2: {
                player.useChronoEnergy(2);

                if (!state.metWade){
                    int saloonJob;
                    cout << endl;
                    cout << "You enter the crowded town saloon." << endl;
                    cout << "Piano music and drunken talk surround you." << endl;
                    cout << "You walk over to the bar and sit down." << endl;

                    enterToContinue();

                    cout << "A man wearing a black cowboy hat and dark clothing approaches you." << endl;
                    cout << "Wade Blackwell: \"You're new round these parts. What's your name?\"" << endl;
                    cout << "You: \"Name's " << player.getName() << ".\"" << endl;

                    enterToContinue();

                    cout << "Wade Blackwell: \"Good to meet you.\"" << endl;
                    cout << "Wade Blackwell: \"I'm lookin' to hire guns for a job tonight.\"" << endl;
                    cout << "Wade Blackwell: \"You interested?\"" << endl;
                    cout << "1. \"I'm interested!\"" << endl;
                    cout << "2. \"I'm just traveling west. Let me enjoy my whiskey and leave me alone.\"" << endl;
                    cout << "Enter Choice: ";
                    saloonJob = getValidatedChoice(1,2);
                    wildWest.markNPCTalkedTo("Wade Blackwell");

                    if (saloonJob == 1){
                        cout << endl;
                        cout << "Wade Blackwell: \"Good to hear. Meet me back here tonight.\"" << endl;
                        state.stealingRoute = true;

                        player.useChronoEnergy(5);
                        player.lowerTimeStability(5);

                        cout << endl;
                        cout << "Planning the robbery costs you 5 Chrono Energy "
                             << "and 5 Time Stability." << endl;
                        enterToContinue();
                    }
                    else{
                        cout << endl;
                        cout << "Wade waves his hand dismissively." << endl;
                        cout << "Wade Blackwell: \"Your loss.\"" << endl;
                        cout << "Wade walks out of the saloon." << endl;

                        state.stealingRoute = false;

                        enterToContinue();
                        
                        cout << "A man wearing a silver badge takes the empty seat beside you." << endl;
                        cout << "Sheriff: \"I saw Wade Blackwell speaking with you.\"" << endl;
                        cout << "Sheriff: \"Mind telling me what that outlaw wanted?\"" << endl;

                        enterToContinue();

                        cout << "You: \"He wanted me to help him steal a stagecoach tonight.\"" << endl;
                        cout << "Sheriff: \"That sounds like Wade. He's been causing trouble "
                            << "around here for years.\"" << endl;
                        cout << "Sheriff: \"That coach carries dynamite, rope, and mining tools.\"" << endl;

                        enterToContinue();

                        cout << "Sheriff: \"With the mine collapsed, I have a feeling I know "
                            << "where he's headed.\"" << endl;
                        cout << "Sheriff: \"He'll probably steal the coach without you and take "
                            << "the supplies to the mine.\"" << endl;
                        cout << "Sheriff: \"Meet me at the mine. We'll catch him there.\"" << endl;

                        state.toldSheriff = true;
                        wildWest.markNPCTalkedTo("Sheriff");

                        enterToContinue();
                    }
                    state.metWade = true;
                    
                }
                else if (state.metWade && state.stealingRoute && !state.stagecoachStolen){
                    cout << endl;
                    cout << "Wade Blackwell: \"Glad to see you didn't back out.\"" << endl;
                    cout << "Wade Blackwell: \"We'll be stealin' a stagecoach tonight. "
                         << "It's got dynamite, pickaxes, and some good pickins' for ya!\"" << endl;
                    cout << "Wade Blackwell: \"It should be here soon!\"" << endl;

                    enterToContinue();

                    cout << "The stagecoach pulls in." << endl;
                    cout << "The owners step inside the saloon." << endl;
                    cout << endl;
                    cout << "Wade Blackwell: \"Alright it's time to go. You ready?\"" << endl;
                    cout << "1. \"I'm ready!\"" << endl;
                    cout << "2. \"I uhhh forgot my gun. Let's do this another night.\"" << endl;
                    cout << "Enter Choice: ";

                    robberyDecision = getValidatedChoice (1,2);

                    if (robberyDecision == 1){
                        state.stagecoachStolen = true;

                        player.useChronoEnergy(5);
                        player.lowerTimeStability(5);

                        cout << endl;
                        cout << "You and Wade Blackwell jump into the stagecoach and ride off." << endl;
                        cout << "Stealing the stagecoach costs you 5 Chrono Energy "
                             << "and 5 Time Stability." << endl;

                        enterToContinue();

                        cout << "Wade Blackwell: \"You did great, son! Meet me over at the mine "
                             << "so we can see what's in this stagecoach.\"" << endl;
                        cout << "Wade Blackwell: \"Maybe we can take a peek inside the mine with this dynamite.\"" << endl;

                        enterToContinue();
                    }
                    else {
                        cout << endl;
                        cout << "You step away from the stagecoach." << endl;
                        cout << "You: \"I can't do this.\"" << endl;

                        cout << endl;
                        cout << "Sheriff: \"Nobody move!\"" << endl;
                        cout << "The sheriff steps out from behind the saloon with his revolver drawn." << endl;

                        enterToContinue();

                        cout << "Sheriff: \"Wade Blackwell, I should've known you'd be behind this.\"" << endl;
                        cout << "Wade Blackwell: \"Afraid I don't have time to chat, Sheriff.\"" << endl;
                        cout << "Wade shoves past you and disappears into the darkness." << endl;

                        enterToContinue();

                        cout << "Sheriff: \"You must be new in town.\"" << endl;
                        cout << "Sheriff: \"Wade Blackwell is an outlaw, and you nearly helped him "
                            << "steal a stagecoach.\"" << endl;
                        cout << "You explain that you only need the equipment to reach the collapsed mine." << endl;

                        enterToContinue();

                        cout << "Sheriff: \"The mine, huh? That explains why Wade wanted this coach.\"" << endl;
                        cout << "Sheriff: \"It carries dynamite, ropes, and mining tools.\"" << endl;
                        cout << "Sheriff: \"He'll probably try again without you.\"" << endl;
                        cout << "Sheriff: \"Meet me at the mine. We'll catch him there and recover "
                            << "the equipment.\"" << endl;

                        state.stealingRoute = false;
                        state.toldSheriff = true;
                        wildWest.markNPCTalkedTo("Sheriff");
                        enterToContinue();
                    }
                }
                else if(componentRecovered && !state.helpedJankins) {
                    cout << endl;
                    cout << "You return to the saloon with the Temporal Cog secured." << endl;
                    cout << "The bartender looks at the strange brass device in your hands." << endl;

                    enterToContinue();

                    cout << "Bartender: \"Looks like you found what you came for.\"" << endl;
                    cout << "Bartender: \"Before you leave town, you ought to visit Old Man Jankins.\"" << endl;
                    cout << "Bartender: \"He lives in the cabin outside town and could use some help.\"" << endl;
                    cout << "Bartender: \"Poor man hasn't been the same since his wife passed.\"" << endl;

                    enterToContinue();
                }
                else if (state.toldSheriff && !state.wadeArrested) {
                    cout << endl;
                    cout << "Sheriff: \"Remember to meet me at the mine tonight so we can finally stop Blackwell.\"" << endl;
                    enterToContinue();
                }
                else{
                    cout << endl;
                    cout << "Bartender: \"I saw you talkin to that Blackwell fellow. Let me tell you he's bad news.\"" << endl;

                    enterToContinue();
                    cout << "Bartender: \"You should head up to Old Man Jankins' cabin.\"" << endl;
                    cout << "Bartender: \"Maybe he'll knock your head straight!\"" << endl;

                    enterToContinue();
                }
            }
                break;
            case 3:{
                cout << endl;
                cout << "You approach Old Man Jankins' cabin." << endl;
                cout << "The small wooden cabin sits alone beneath the setting sun." << endl;

                if (state.helpedJankins) {
                    cout << "Old Man Jankins sits peacefully on the porch." << endl;
                    cout << "Jankins: \"Thank you again, partner.\"" << endl;
                    cout << "Jankins: \"I reckon Martha would have liked you.\"" << endl;

                    enterToContinue();
                }
                else {
                    wildWest.markNPCTalkedTo("Old Man Jankins");
                    cout << "You knock on the weathered front door." << endl;
                    cout << "After a moment, an elderly man slowly opens it." << endl;

                    enterToContinue();

                    cout << "Jankins: \"Don't get many visitors out this way.\"" << endl;
                    cout << "Jankins: \"Name's Jankins. What can I do for you?\"" << endl;
                    cout << "You: \"The bartender said you might need some help.\"" << endl;

                    enterToContinue();

                    cout << "Jankins looks toward a small hill behind his cabin." << endl;
                    cout << "Jankins: \"My wife Martha is buried up there.\"" << endl;
                    cout << "Jankins: \"I used to bring flowers to her every week.\"" << endl;
                    cout << "Jankins: \"These old legs just can't make the climb anymore.\"" << endl;

                    cout << endl;
                    cout << "1. Offer to bring flowers to Martha's grave" << endl;
                    cout << "2. Tell Jankins you cannot help right now" << endl;
                    cout << "Enter Choice: ";

                    int jankinsChoice = getValidatedChoice(1, 2);

                    if (jankinsChoice == 1) {
                        cout << endl;
                        cout << "You take a small bundle of wildflowers from Jankins." << endl;
                        cout << "You climb the hill behind the cabin." << endl;

                        player.useChronoEnergy(5);

                        enterToContinue();

                        cout << "At the top of the hill, you find a simple wooden grave marker." << endl;
                        cout << "It reads: \"Martha Jankins — A loving wife and a gentle soul.\"" << endl;
                        cout << "You place the flowers beside the grave." << endl;

                        enterToContinue();

                        cout << "You return to the cabin and tell Jankins that the flowers "
                            << "have been delivered." << endl;
                        cout << "Jankins removes his hat and looks toward the hill." << endl;

                        enterToContinue();

                        cout << "Jankins: \"Thank you, partner. That means more than you know.\"" << endl;
                        cout << "Jankins: \"It's good to know Martha hasn't been forgotten.\"" << endl;

                        state.helpedJankins = true;

                        enterToContinue();

                        if (componentRecovered) {
                            cout << "With the Temporal Cog recovered and Jankins helped, "
                                << "your work in the Wild West is complete." << endl;
                            cout << "You return to the time portal." << endl;

                            wildWestChoice = 4;

                            enterToContinue();
                        }
                        else {
                            cout << "Jankins: \"Now you'd better get back to that mine.\"" << endl;
                            cout << "Jankins: \"Whatever you're searching for is still buried inside.\"" << endl;

                            enterToContinue();
                        }
                    }
                    else {
                        cout << endl;
                        cout << "You: \"I'm sorry, but I can't help right now.\"" << endl;
                        cout << "Jankins: \"I understand. Maybe another time.\"" << endl;

                        enterToContinue();
                    }
                }
                break;
            }
            case 4:
                cout << endl;
                cout << "You return to the time portal." << endl;
                break;
        }
    }
    WildWestResult result = {
        player,
        wildWest,
        componentRecovered,
        state
    };

    return result;
}

FutureResult playFuture(
    Player player,
    Era future,
    bool componentRecovered,
    FutureState state
) {
    if (componentRecovered) {
        cout << endl;
        cout << "You have already recovered the Quantum Stabilizer Core." << endl;
        cout << "There is no reason to return to the year 2352." << endl;

        FutureResult result = {
            player,
            future,
            componentRecovered,
            state
        };

        return result;
    }

    int futureChoice = 0;

    cout << endl;

    waitSecond(3);

    printPortal();

    waitSecond(3);

    cout << endl;
    cout << "The laboratory disappears behind a wall of blue light." << endl;
    cout << "You arrive in a massive futuristic city." << endl;
    cout << "Hovering vehicles move silently between glowing towers." << endl;

    player.useChronoEnergy(10);
    player.lowerTimeStability(5);

    if (!state.visitedFuture) {
        state.visitedFuture = true;

        enterToContinue();

        cout << "A city announcement echoes from speakers above you." << endl;
        cout << "City AI: \"Warning. Unidentified quantum energy detected.\"" << endl;
        cout << "City AI: \"The Quantum Research Center remains under lockdown.\"" << endl;

        enterToContinue();

        cout << "You recognize the energy signature immediately." << endl;
        cout << "Your missing Quantum Stabilizer Core is somewhere inside the city." << endl;

        enterToContinue();

        cout << "A nearby public terminal suddenly flickers." << endl;
        cout << "An encrypted message appears on the screen." << endl;
        cout << endl;
        cout << "Unknown Sender: \"The Research Center will never give that core up willingly.\"" << endl;
        cout << "Unknown Sender: \"If you want another way inside, come to Neon Gardens.\"" << endl;
        cout << "Unknown Sender: \"Ask for Nyx. Come alone.\"" << endl;

        enterToContinue();

        cout << "You now have two possible leads:" << endl;
        cout << "1. Visit the Quantum Research Center and ask for help." << endl;
        cout << "2. Search Neon Gardens for Nyx and attempt a risky break-in." << endl;

        enterToContinue();
    }
    else {
        cout << endl;
        cout << "You return to the city of 2352." << endl;
        cout << "The Quantum Research Center remains visible in the distance." << endl;
    }

 

    while (futureChoice != 4 &&
           player.getChronoEnergy() > 0 &&
           player.getTimeStability() > 0 &&
           !componentRecovered) {

        cout << endl;
        cout << "========== FUTURE 2352 ==========" << endl;
        future.displayEra();

        cout << endl;
        cout << "Chrono Energy: " << player.getChronoEnergy() << endl;
        cout << "Time Stability: " << player.getTimeStability() << endl;

        if (state.securityAlerted) {
            cout << endl;
            cout << "Status: City security is searching for an intruder." << endl;
        }

        if (state.hasClearanceChip) {
            cout << endl;
            cout << "Status: You have a Research Clearance Chip." << endl;
        }

        if (state.hasTunnelCode) {
            cout << endl;
            cout << "Status: You have Nyx's maintenance tunnel code." << endl;
        }

        enterToContinue();

        cout << "1. Visit the Quantum Research Center" << endl;
        cout << "2. Enter the AI Workshop" << endl;
        cout << "3. Explore Neon Gardens" << endl;
        cout << "4. Return to the Time Portal" << endl;
        cout << "Enter Choice: ";

        futureChoice = getValidatedChoice(1, 4);

        switch (futureChoice) {
            case 1: {
                cout << endl;
                cout << "You approach the Quantum Research Center." << endl;
                cout << "A massive silver building rises above the city." << endl;
                cout << "Blue energy pulses through transparent walls." << endl;

                player.useChronoEnergy(2);
                enterToContinue();

                if (state.hasClearanceChip) {
                    cout << endl;
                    cout << "You place the Research Clearance Chip against the security scanner." << endl;
                    cout << "Security AI: \"Clearance verified. Access granted.\"" << endl;

                    enterToContinue();

                    cout << "The laboratory doors slide open." << endl;
                    cout << "You enter a sealed chamber filled with unstable blue light." << endl;
                    cout << "At the center of the room floats the Quantum Stabilizer Core." << endl;

                    enterToContinue();

                    cout << "Dr. Elara Voss enters the chamber behind you." << endl;
                    cout << "Dr. Voss: \"The repaired AI confirmed your story.\"" << endl;
                    cout << "Dr. Voss: \"This device does not belong in our timeline.\"" << endl;
                    cout << "Dr. Voss: \"Take it before its energy destabilizes the city.\"" << endl;

                    enterToContinue();

                    cout << "You carefully remove the Quantum Stabilizer Core." << endl;
                    cout << "The violent energy surrounding the chamber begins to fade." << endl;

                    player.addItem("Quantum Stabilizer Core");
                    future.setComponentFound(true);
                    componentRecovered = true;

                    enterToContinue();
                }
                else if (state.smugglingRoute && state.hasTunnelCode) {
                    cout << "Security drones patrol the main entrance." << endl;
                    cout << "You avoid them and follow Nyx's directions toward the east wall." << endl;
                    cout << "Behind a holographic advertisement, you discover a maintenance hatch." << endl;

                    enterToContinue();

                    cout << "You enter the tunnel code: 7-3-9-2." << endl;
                    cout << "The maintenance hatch unlocks with a quiet click." << endl;
                    cout << "A narrow tunnel leads beneath the Quantum Research Center." << endl;

                    enterToContinue();

                    cout << "At the end of the tunnel, an automated security panel blocks your path." << endl;
                    cout << "You must bypass the panel before the security drones detect you." << endl;

                    cout << endl;
                    cout << "1. Attempt to hack the security panel" << endl;
                    cout << "2. Back out and return to the city" << endl;
                    cout << "Enter Choice: ";

                    int breakInChoice = getValidatedChoice(1, 2);

                    if (breakInChoice == 1) {
                        state.breakInAttempted = true;
                        state.hackingAttempts++;

                        int hackingRoll = rand() % 10 + 1;

                        cout << endl;
                        cout << "You connect your device to the security panel." << endl;
                        cout << "Streams of encrypted data flash across the screen." << endl;

                        enterToContinue();

                        if (hackingRoll <= player.getLuck()) {
                            cout << "The security panel flashes green." << endl;
                            cout << "Security AI: \"Maintenance access accepted.\"" << endl;
                            cout << "The reinforced door slides open." << endl;

                            enterToContinue();

                            cout << "You enter a restricted laboratory filled with blue energy." << endl;
                            cout << "At the center of the chamber floats the Quantum Stabilizer Core." << endl;
                            cout << "Warning lights flash as you approach the device." << endl;

                            enterToContinue();

                            cout << "You disconnect the Quantum Stabilizer Core from the city's power system." << endl;
                            cout << "The chamber goes dark as you secure the missing component." << endl;

                            player.addItem("Quantum Stabilizer Core");
                            future.setComponentFound(true);
                            componentRecovered = true;

                            enterToContinue();

                            cout << "Nyx's voice comes through your communicator." << endl;
                            cout << "Nyx: \"Looks like you made it. Get out before security catches up.\"" << endl;
                            cout << "You escape through the maintenance tunnel and return to the portal." << endl;

                            enterToContinue();
                        }
                        else {
                            state.securityAlerted = true;

                            int energyPenalty = state.hackingAttempts * 5;

                            cout << "The security panel flashes red." << endl;
                            cout << "Security AI: \"Unauthorized access detected.\"" << endl;
                            cout << "Security drones enter the maintenance tunnel." << endl;
                            cout << "You disconnect your device and narrowly escape." << endl;

                            player.useChronoEnergy(energyPenalty);
                            player.lowerTimeStability(5);

                            cout << endl;
                            cout << "The failed break-in costs you " << energyPenalty
                                << " Chrono Energy and 5 Time Stability." << endl;

                            enterToContinue();

                            if (player.getChronoEnergy() > 0 &&
                                player.getTimeStability() > 0) {

                                cout << "Nyx contacts you after your escape." << endl;
                                cout << "Nyx: \"Security knows someone tried to enter.\"" << endl;
                                cout << "Nyx: \"You can try again, but every attempt will become more dangerous.\"" << endl;

                                cout << endl;
                                cout << "1. Try the break-in again later" << endl;
                                cout << "2. Abandon the smuggling route and ask Dr. Voss for help" << endl;
                                cout << "3. Leave the Future for now" << endl;
                                cout << "Enter Choice: ";

                                int failureChoice = getValidatedChoice(1, 3);

                                if (failureChoice == 1) {
                                    cout << endl;
                                    cout << "Nyx: \"Return when you're ready. The tunnel code should still work.\"" << endl;

                                    enterToContinue();
                                }
                                else if (failureChoice == 2) {
                                    state.smugglingRoute = false;
                                    state.hasTunnelCode = false;

                                    cout << endl;
                                    cout << "You delete Nyx's tunnel code from your device." << endl;
                                    cout << "You decide to seek legitimate access through Dr. Voss." << endl;

                                    enterToContinue();
                                }
                                else {
                                    cout << endl;
                                    cout << "You decide to return to the time portal for now." << endl;

                                    futureChoice = 4;

                                    enterToContinue();
                                }
                            }
                        }
                    }
                    else {
                        cout << endl;
                        cout << "You decide not to risk the break-in yet." << endl;
                        cout << "The maintenance tunnel remains available when you return." << endl;

                        enterToContinue();
                    }
                }
                else if (state.smugglingRoute && !state.hasTunnelCode) {
                    cout << "Security drones patrol the entrance." << endl;
                    cout << "You agreed to work with Nyx, but you do not yet have the "
                        << "maintenance tunnel code." << endl;
                    cout << "Return to Neon Gardens and finish planning the break-in." << endl;

                    enterToContinue();
                }
                else if (!state.repairQuestStarted) {

                    cout << "A security scanner blocks the entrance." << endl;
                    cout << "A woman wearing a white research uniform approaches you." << endl;

                    enterToContinue();

                    cout << "Dr. Elara Voss: \"You are not registered in the city database.\"" << endl;
                    cout << "Dr. Voss: \"State your purpose.\"" << endl;
                    cout << "You explain that the Quantum Stabilizer Core belongs to your time machine." << endl;

                    enterToContinue();

                    cout << "Dr. Voss: \"That device appeared several weeks ago.\"" << endl;
                    cout << "Dr. Voss: \"Its energy is currently supporting part of the city's power grid.\"" << endl;
                    cout << "Dr. Voss: \"I cannot release it without verifying your story.\"" << endl;
                    enterToContinue();

                    if (player.getSociability() >= 8) {
                        cout << "You carefully explain the danger caused by the displaced component." << endl;
                        cout << "Dr. Voss studies the unstable energy readings." << endl;
                        cout << "Dr. Voss: \"Your explanation matches our data.\"" << endl;
                        cout << "Dr. Voss: \"However, our facility AI is malfunctioning.\"" << endl;
                        cout << "Dr. Voss: \"Repair it at the AI Workshop and bring me a clearance chip.\"" << endl;
                    }

                    else {
                        cout << "You try to explain the danger caused by the displaced component." << endl;
                        cout << "Dr. Voss: \"Your story is difficult to believe.\"" << endl;
                        cout << "Dr. Voss: \"The facility AI can analyze the component's temporal signature.\"" << endl;
                        cout << "Dr. Voss: \"Unfortunately, the AI was damaged during the energy surge.\"" << endl;
                        cout << "Dr. Voss: \"Visit the AI Workshop and have it repaired.\"" << endl;
                    }
                    state.repairQuestStarted = true;
                    future.markNPCTalkedTo("Dr. Elara Voss");
                    enterToContinue();

                }

                else if (state.aiRepaired) {
                    cout << "Dr. Voss meets you near the security entrance." << endl;
                    cout << "Dr. Voss: \"The facility AI is operational again.\"" << endl;
                    cout << "Dr. Voss: \"Return to the AI Workshop and retrieve the clearance chip.\"" << endl;
                    enterToContinue();

                }

                else {
                    cout << "Dr. Voss waits beside the locked entrance." << endl;
                    cout << "Dr. Voss: \"The facility AI must be repaired before I can help you.\"" << endl;
                    cout << "Dr. Voss: \"You will find the AI Workshop near the center of the city.\"" << endl;

                    enterToContinue();

                }

                break;
            }
            case 2: {
                cout << endl;
                cout << "You enter the AI Workshop." << endl;
                cout << "Damaged robots hang from mechanical repair arms." << endl;
                cout << "Sparks flash across workbenches covered in wires and processors." << endl;

                player.useChronoEnergy(2);
                enterToContinue();

                if (state.hasClearanceChip) {
                    cout << "The workshop technician recognizes you." << endl;
                    cout << "Technician Juno: \"You already have the Research Clearance Chip.\"" << endl;
                    cout << "Technician Juno: \"Take it to Dr. Voss at the Quantum Research Center.\"" << endl;

                    enterToContinue();
                }

                else if (state.aiRepaired) {
                    cout << "The repaired facility AI glows beside the workbench." << endl;
                    cout << "Technician Juno: \"The AI is already fully operational.\"" << endl;
                    cout << "Technician Juno hands you the Research Clearance Chip." << endl;

                    state.hasClearanceChip = true;
                    enterToContinue();

                    cout << "You can now enter the restricted chamber at the Quantum Research Center." << endl;

                    enterToContinue();
                }

                else if (!state.repairQuestStarted) {
                    cout << "A technician looks up from a damaged service robot." << endl;
                    cout << "Technician Juno: \"I don't recognize you. Do you have a repair order?\"" << endl;
                    cout << "You explain that you are searching for the Quantum Stabilizer Core." << endl;

                    enterToContinue();

                    cout << "Technician Juno: \"That device is controlled by the "
                        << "Quantum Research Center.\"" << endl;
                    cout << "Technician Juno: \"Speak with Dr. Voss first. She must authorize "
                        << "any repairs to the facility AI.\"" << endl;

                    enterToContinue();
                }

                else {
                    future.markNPCTalkedTo("Technician Juno");
                    cout << "Technician Juno stands beside a damaged artificial intelligence core." << endl;
                    cout << "Several wires have been torn loose, and its display flashes red." << endl;

                    enterToContinue();

                    cout << "Technician Juno: \"Dr. Voss sent a message about you.\"" << endl;
                    cout << "Technician Juno: \"The energy surge damaged the facility AI's logic processor.\"" << endl;
                    cout << "Technician Juno: \"Help me restart its systems in the correct order.\"" << endl;

                    enterToContinue();

                    cout << "Three systems must be activated:" << endl;
                    cout << "1. Security Network" << endl;
                    cout << "2. Power Core" << endl;
                    cout << "3. Logic Processor" << endl;

                    cout << endl;

                    cout << "The Power Core must be activated first." << endl;
                    cout << "The Logic Processor must be activated second." << endl;
                    cout << "The Security Network must be activated last." << endl;

                    enterToContinue();

                    int firstSystem;
                    int secondSystem;
                    int thirdSystem;

                    cout << "Select the first system: ";
                    firstSystem = getValidatedChoice(1, 3);
                    cout << "Select the second system: ";
                    secondSystem = getValidatedChoice(1, 3);
                    cout << "Select the third system: ";
                    thirdSystem = getValidatedChoice(1, 3);

                    if (firstSystem == 2 && secondSystem == 3 && thirdSystem == 1) {
                        
                        cout << endl;
                        cout << "You activate the Power Core." << endl;
                        cout << "Blue energy flows into the damaged AI." << endl;
                        cout << "You activate the Logic Processor." << endl;
                        cout << "The AI's display begins processing information." << endl;
                        cout << "Finally, you activate the Security Network." << endl;

                        player.useChronoEnergy(5);
                        enterToContinue();

                        cout << "Facility AI: \"System restoration complete.\"" << endl;
                        cout << "Facility AI: \"Temporal energy signature confirmed.\"" << endl;
                        cout << "Facility AI: \"The Quantum Stabilizer Core originated outside this timeline.\"" << endl;

                        state.aiRepaired = true;
                        enterToContinue();

                        cout << "Technician Juno: \"That confirms your story.\"" << endl;
                        cout << "Technician Juno creates a Research Clearance Chip." << endl;
                        cout << "Technician Juno: \"Take this to Dr. Voss. It will unlock "
                            << "the restricted chamber.\"" << endl;

                        state.hasClearanceChip = true;
                        enterToContinue();

                    }

                    else {
                        cout << endl;
                        cout << "The systems activate in the wrong order." << endl;
                        cout << "Warning lights flash throughout the workshop." << endl;
                        cout << "A burst of electricity forces you away from the console." << endl;

                        player.useChronoEnergy(5);
                        cout << "You lose 5 Chrono Energy." << endl;
                        enterToContinue();

                        if (player.getChronoEnergy() > 0) {
                            cout << "Technician Juno: \"The AI was not permanently damaged.\"" << endl;
                            cout << "Technician Juno: \"Remember: Power, Logic, then Security.\"" << endl;
                            cout << "Technician Juno: \"Come back when you are ready to try again.\"" << endl;

                            enterToContinue();

                        }

                    }

                }

                break;

            }
            case 3: {
                cout << endl;
                cout << "You enter Neon Gardens." << endl;
                cout << "Holographic trees glow beneath a dark artificial sky." << endl;
                cout << "The park appears abandoned, but shadows move between the ruins." << endl;

                player.useChronoEnergy(2);

                enterToContinue();

                if (state.hasTunnelCode) {
                    cout << "Nyx waits beside a broken holographic fountain." << endl;
                    cout << "Nyx: \"You already have the maintenance tunnel code.\"" << endl;
                    cout << "Nyx: \"The entrance is beneath the Quantum Research Center.\"" << endl;
                    cout << "Nyx: \"Go there when you're ready to break in.\"" << endl;

                    enterToContinue();
                }
                else if (state.smugglingRoute && state.metNyx) {
                    cout << "Nyx steps from behind a flickering holographic tree." << endl;
                    cout << "Nyx: \"You came back. Good.\"" << endl;
                    cout << "Nyx: \"I found an abandoned maintenance tunnel beneath the "
                        << "Research Center.\"" << endl;

                    enterToContinue();

                    cout << "Nyx: \"The tunnel is protected by an old security lock.\"" << endl;
                    cout << "Nyx: \"I can give you the access code, but once you enter, "
                        << "you're on your own.\"" << endl;

                    enterToContinue();

                    cout << "Nyx transfers the maintenance tunnel code to your device." << endl;
                    cout << "The code reads: 7-3-9-2." << endl;

                    state.hasTunnelCode = true;

                    player.useChronoEnergy(5);
                    player.lowerTimeStability(5);

                    cout << endl;
                    cout << "Planning the illegal break-in costs you 5 Chrono Energy "
                        << "and 5 Time Stability." << endl;

                    enterToContinue();

                    cout << "Nyx: \"Return to the Quantum Research Center.\"" << endl;
                    cout << "Nyx: \"Look for the maintenance hatch behind the east wall.\"" << endl;

                    enterToContinue();
                }
                else if (!state.metNyx) {
                    future.markNPCTalkedTo("Nyx");
                    cout << "A hooded figure watches you from beneath a glowing tree." << endl;
                    cout << "The figure approaches slowly." << endl;

                    enterToContinue();

                    cout << "Nyx: \"You must be the traveler looking for the quantum core.\"" << endl;
                    cout << "You: \"How do you know about that?\"" << endl;
                    cout << "Nyx: \"Nothing enters this city without the underground hearing about it.\"" << endl;

                    enterToContinue();

                    cout << "Nyx: \"The Research Center will make you complete inspections, "
                        << "repairs, and security checks.\"" << endl;
                    cout << "Nyx: \"I can get you inside much faster.\"" << endl;
                    cout << "Nyx: \"But getting caught could permanently alert city security.\"" << endl;

                    enterToContinue();

                    cout << "1. Agree to work with Nyx" << endl;
                    cout << "2. Refuse and use the legal route" << endl;
                    cout << "Enter Choice: ";

                    int nyxChoice = getValidatedChoice(1, 2);

                    state.metNyx = true;

                    if (nyxChoice == 1) {
                        state.smugglingRoute = true;

                        cout << endl;
                        cout << "Nyx smiles beneath the hood." << endl;
                        cout << "Nyx: \"Good choice. Come back when you're ready for the tunnel code.\"" << endl;

                        enterToContinue();
                    }
                    else {
                        state.smugglingRoute = false;

                        cout << endl;
                        cout << "Nyx: \"Suit yourself.\"" << endl;
                        cout << "Nyx: \"Go convince the scientists that you belong here.\"" << endl;
                        cout << "Nyx disappears into the glowing gardens." << endl;

                        enterToContinue();
                    }
                }
                else {
                    cout << "The holographic gardens flicker quietly." << endl;
                    cout << "Nyx is nowhere to be seen." << endl;
                    cout << "You decided not to join the smuggling operation." << endl;
                    cout << "The legal route through the Quantum Research Center remains available." << endl;

                    enterToContinue();
                }

                break;
            }
            case 4:
                cout << endl;
                cout << "You return to the time portal." << endl;
                break;
        }
    }

    FutureResult result = {
        player,
        future,
        componentRecovered,
        state
    };

    return result;
}

struct PortalResult {
    Player player;

    Era egypt;
    bool egyptComponentRecovered;
    EgyptState egyptState;

    Era wildWest;
    bool wildWestComponentRecovered;
    WildWestState wildWestState;

    Era future;
    bool futureComponentRecovered;
    FutureState futureState;
};

PortalResult displayPortalMenu(
    Player player,

    Era egypt,
    bool egyptComponentRecovered,
    EgyptState egyptState,

    Era wildWest,
    bool wildWestComponentRecovered,
    WildWestState wildWestState,

    Era future,
    bool futureComponentRecovered,
    FutureState futureState
){

        int portalChoice = 0;
        
        while (portalChoice != 4 &&
               player.getChronoEnergy() > 0 &&
               player.getTimeStability() > 0) {
            cout << endl;

            cout << "Recovered Components:" << endl;
            if (egyptComponentRecovered) {
                cout << "- Scarab of the Endless Dawn" << endl;
            }
            if (wildWestComponentRecovered) {
                cout << "- Temporal Cog" << endl;
            }
            if (futureComponentRecovered) {
                cout << "- Quantum Stabilizer Core" << endl;
            cout << endl;
            cout << endl;
}
            cout << "======== TIME PORTALS ========" << endl;
            cout << "1. Ancient Egypt" << endl;
            cout << "2. Wild West" << endl;
            cout << "3. Future 2352" << endl;
            cout << "4. Return to Main Menu" << endl;
            cout << "Enter Choice: ";
            
            portalChoice = getValidatedChoice(1, 4);

            cout << endl;
            cout << endl;

            switch (portalChoice) {
                case 1: {
                    cout << "You step through the portal to Ancient Egypt." << endl;
                    EgyptResult egyptResult = playEgypt(
                        player,
                        egypt,
                        egyptComponentRecovered,
                        egyptState
                    );

                    player = egyptResult.player;
                    egypt = egyptResult.egypt;
                    egyptComponentRecovered = egyptResult.componentRecovered;
                    egyptState = egyptResult.state;
                    break;
                }
                case 2: {
                    cout << "You step through the portal to the Wild West." << endl;
                    WildWestResult wildWestResult = playWildWest(
                        player,
                        wildWest,
                        wildWestComponentRecovered,
                        wildWestState
                    );

                    player = wildWestResult.player;
                    wildWest = wildWestResult.wildWest;
                    wildWestComponentRecovered = wildWestResult.componentRecovered;
                    wildWestState = wildWestResult.state;
                    break;
                }
                case 3: {
                    cout << "You step through the portal to the year 2352." << endl;
                    FutureResult futureResult = playFuture(
                        player,
                        future,
                        futureComponentRecovered,
                        futureState
                    );

                    player = futureResult.player;
                    future = futureResult.future;
                    futureComponentRecovered = futureResult.componentRecovered;
                    futureState = futureResult.state;

                    break;
                }
                case 4:
                    cout << "You step away from the portals." << endl;
                    break;
            }
        }
        PortalResult result = {
            player,

            egypt,
            egyptComponentRecovered,
            egyptState,

            wildWest,
            wildWestComponentRecovered,
            wildWestState,

            future,
            futureComponentRecovered,
            futureState
        };
        return result;
}

int loadCharacterChoices(
    string filename,
    CharacterChoice choices[],
    int maxChoices
){
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
    choice = getValidatedChoice(1,numChoices);

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
    srand (time(0));
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
    laboratory.addSubLocation("Time Portals");
    laboratory.addSubLocation("Repair Workbench");
    laboratory.addNPC(scientist);

    Era egypt("Ancient Egypt");
    egypt.addSubLocation("Crypt");
    egypt.addSubLocation("Worship Center");
    egypt.addSubLocation("Market");
    bool egyptComponentRecovered = false;
    EgyptState egyptState = {
        false,
        false,
        false,
        false,
        false,
        false,
        0
    };

    //EgyptNPCs
    NPC seti(
        "Seti",
        100,
        "I know another way into the crypt.",
        "Steal the scarab.",
        "Access to the crypt"
    );

    NPC anhur(
        "High Priest Anhur",
        100,
        "Trust must be earned through action.",
        "Help the people in the market.",
        "Royal Seal"
    );

    NPC nefru(
        "Nefru",
        100,
        "The market needs replacement water jars.",
        "Carry replacement jars.",
        "Trust of the merchants"
    );

    egypt.addNPC(seti);
    egypt.addNPC(anhur);
    egypt.addNPC(nefru);



    Era wildWest("Wild West");
    wildWest.addSubLocation("Gold Mine");
    wildWest.addSubLocation("Town Saloon");
    wildWest.addSubLocation("Old Man Jankins' Cabin");
    bool wildWestComponentRecovered = false;
    WildWestState wildWestState = {
        false,
        false,
        false,
        false,
        false,
        false,
        false
    };
    // Wild West NPCs
    NPC wade(
        "Wade Blackwell",
        100,
        "I have a job for you.",
        "Steal the stagecoach.",
        "Mining equipment"
    );

    NPC sheriff(
        "Sheriff",
        100,
        "Wade Blackwell must be stopped.",
        "Help arrest Wade.",
        "Access to the mine"
    );

    NPC jankins(
        "Old Man Jankins",
        100,
        "My wife is buried on the hill.",
        "Bring flowers to Martha's grave.",
        "Jankins' gratitude"
    );

    wildWest.addNPC(wade);
    wildWest.addNPC(sheriff);
    wildWest.addNPC(jankins);



    Era future("2352");
    future.addSubLocation("Quantum Research Facility");
    future.addSubLocation("AI Workshop");
    future.addSubLocation("Neon Gardens");
    bool futureComponentRecovered = false;
    FutureState futureState = {
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        0
    };
    //Future NPCs
    NPC voss(
        "Dr. Elara Voss",
        100,
        "The Quantum Stabilizer Core is inside the Research Center.",
        "Repair the facility AI.",
        "Research access"
    );

    NPC juno(
        "Technician Juno",
        100,
        "The facility AI needs repairs.",
        "Restart the AI systems.",
        "Research Clearance Chip"
    );

    NPC nyx(
        "Nyx",
        100,
        "I know a hidden route into the Research Center.",
        "Break into the Research Center.",
        "Maintenance tunnel code"
    );

    future.addNPC(voss);
    future.addNPC(juno);
    future.addNPC(nyx);



    int menuChoice = 0;
    int maxMenuChoice = 5;
    bool gameFinished = false;

    while (menuChoice != maxMenuChoice && !gameFinished){
        cout << endl;
        cout << "========== MAIN MENU ==========" << endl;
        cout << "1. View Player Stats" << endl;
        cout << "2. Talk to Dr. Baige" << endl;
        cout << "3. Explore the Laboratory" << endl;
        cout << "4. Enter a Time Portal" << endl;
        cout << "5. Quit Game" << endl;
        cout << "Enter Choice: ";

        menuChoice = getValidatedChoice(1,5);

        cout << endl;

        switch (menuChoice){
            case 1:
                player.displayInfo();
                player.showInventory();
                break;
            case 2:{
                bool allComponentsRecovered = 
                    egyptComponentRecovered &&
                    wildWestComponentRecovered &&
                    futureComponentRecovered;

                if (!allComponentsRecovered){
                    scientist.speak();
                }
                else{
                    cout << endl;
                    cout << "Dr. Baige: \"Incredible! You recovered every missing stability component.\"" << endl;
                    cout << "Dr. Baige: \"The Scarab, the Temporal Cog, and the Quantum Stabilizer Core are all intact.\"" << endl;

                    enterToContinue();

                    cout << "Dr. Baige: \"Meet me at the Repair Workbench.\"" << endl;
                    cout << "Dr. Baige: \"If the remaining Time Stability is strong enough, we can restore the timeline.\"" << endl;
                    enterToContinue();
                }
                break;
            }
            case 3: {
                int laboratoryChoice = 0;

                while (laboratoryChoice != 2 && !gameFinished) {
                    cout << endl;
                    cout << "========== LABORATORY ==========" << endl;
                    laboratory.displayEra();

                    cout << endl;
                    cout << "1. Approach the Repair Workbench" << endl;
                    cout << "2. Return to Main Menu" << endl;
                    cout << "Enter Choice: ";

                    laboratoryChoice = getValidatedChoice(1, 2);

                    if (laboratoryChoice == 1) {
                        bool allComponentsRecovered =
                            egyptComponentRecovered &&
                            wildWestComponentRecovered &&
                            futureComponentRecovered;

                        cout << endl;
                        cout << "You approach the damaged time machine at the "
                            << "Repair Workbench." << endl;

                        enterToContinue();

                        if (!allComponentsRecovered) {
                            cout << "Dr. Baige examines the empty component slots." << endl;
                            cout << "Dr. Baige: \"We cannot repair the machine yet.\"" << endl;
                            cout << "Dr. Baige: \"Some of the stability components are "
                                << "still missing.\"" << endl;

                            cout << endl;
                            cout << "Recovered Components:" << endl;
                            cout << "Scarab of the Endless Dawn: ";
                            if (egyptComponentRecovered) {
                                cout << "Recovered" << endl;
                            }
                            else {
                                cout << "Missing" << endl;
                            }

                            cout << "Temporal Cog: ";
                            if (wildWestComponentRecovered) {
                                cout << "Recovered" << endl;
                            }
                            else {
                                cout << "Missing" << endl;
                            }

                            cout << "Quantum Stabilizer Core: ";
                            if (futureComponentRecovered) {
                                cout << "Recovered" << endl;
                            }
                            else {
                                cout << "Missing" << endl;
                            }

                            enterToContinue();

                            cout << "Dr. Baige: \"Return to the portals and recover "
                                << "everything before the timeline collapses.\"" << endl;

                            enterToContinue();
                        }
                        else {
                            cout << "Dr. Baige waits beside the damaged machine." << endl;
                            cout << "Dr. Baige: \"You have everything. This is our only chance.\"" << endl;

                            enterToContinue();

                            cout << "You place the Scarab of the Endless Dawn into "
                                << "the first component slot." << endl;
                            cout << "Golden energy flows through the machine." << endl;

                            enterToContinue();

                            cout << "You install the Temporal Cog into the damaged "
                                << "portal drive." << endl;
                            cout << "The ancient gear begins turning." << endl;

                            enterToContinue();

                            cout << "Finally, you connect the Quantum Stabilizer Core." << endl;
                            cout << "Blue energy races through the laboratory." << endl;

                            enterToContinue();

                            cout << "Dr. Baige: \"All components are connected.\"" << endl;
                            cout << "Dr. Baige: \"Beginning timeline stabilization now!\"" << endl;

                            enterToContinue();

                            cout << "The time machine begins winding down." << endl;
                            cout << "The portals flicker as the displaced timelines "
                                << "are pulled back into alignment." << endl;

                            enterToContinue();

                            int successChance = player.getTimeStability();

                            if (successChance >= 80) {
                                successChance = 100;
                            }

                            else if (successChance < 10){
                                successChance = 10;
                            }

                            int repairRoll = rand() % 100 + 1;

                            cout << "Chrono Energy Remaining: "
                                << player.getChronoEnergy() << endl;
                            cout << "Time Stability Remaining: "
                                << player.getTimeStability() << endl;

                            enterToContinue();

                            if (repairRoll <= successChance) {
                                cout << "The shaking begins to slow." << endl;
                                cout << "One by one, the unstable portals collapse "
                                    << "harmlessly into points of light." << endl;
                                cout << "The time machine returns to a quiet hum." << endl;

                                enterToContinue();

                                cout << "Dr. Baige stares at the stabilized readings." << endl;
                                cout << "Dr. Baige: \"You did it, "
                                    << player.getName() << ".\"" << endl;
                                cout << "Dr. Baige: \"Every era has returned to its proper "
                                    << "place in history.\"" << endl;
                                cout << "Dr. Baige: \"Your choices preserved enough energy "
                                    << "to save the timeline.\"" << endl;

                                enterToContinue();

                                cout << endl;
                                cout << "========================================" << endl;
                                cout << "              YOU WIN!                  " << endl;
                                cout << "        THE TIMELINE IS RESTORED         " << endl;
                                cout << "========================================" << endl;
                                cout << endl;
                                cout << "Thanks for playing Temporal Collapse!" << endl;

                                gameFinished = true;
                            }
                            else {
                                cout << "The time machine suddenly begins shaking violently." << endl;
                                cout << "Warning lights flash across the laboratory." << endl;
                                cout << "The remaining Time Stability cannot contain the reaction." << endl;

                                enterToContinue();

                                cout << "Dr. Baige: \"The readings are collapsing!\"" << endl;
                                cout << "Dr. Baige: \"The machine does not have enough "
                                    << "power to stabilize the timeline!\"" << endl;

                                enterToContinue();

                                cout << "A portal tears open beneath your feet." << endl;
                                cout << "The laboratory disappears in a blinding explosion." << endl;

                                enterToContinue();

                                string trappedEras[3] = {
                                    "Ancient Egypt",
                                    "the Wild West",
                                    "the ruined city of 2352"
                                };

                                int trappedEra = rand() % 3;

                                cout << "You awaken alone in "
                                    << trappedEras[trappedEra] << "." << endl;
                                cout << "The portal has vanished." << endl;
                                cout << "With the time machine destroyed, there is no "
                                    << "way home." << endl;

                                enterToContinue();

                                cout << endl;
                                cout << "========================================" << endl;
                                cout << "               GAME OVER                " << endl;
                                cout << "         LOST SOMEWHERE IN TIME         " << endl;
                                cout << "========================================" << endl;
                                cout << endl;
                                cout << "Thanks for playing Temporal Collapse!" << endl;

                                gameFinished = true;
                            }
                        }
                    }
                }

                break;
            }
            case 4:{
                PortalResult portalResult = displayPortalMenu(
                    player,

                    egypt,
                    egyptComponentRecovered,
                    egyptState,

                    wildWest,
                    wildWestComponentRecovered,
                    wildWestState,

                    future,
                    futureComponentRecovered,
                    futureState
                );

                player = portalResult.player;

                egypt = portalResult.egypt;
                egyptComponentRecovered = portalResult.egyptComponentRecovered;
                egyptState = portalResult.egyptState;

                wildWest = portalResult.wildWest;
                wildWestComponentRecovered = portalResult.wildWestComponentRecovered;
                wildWestState = portalResult.wildWestState;

                future = portalResult.future;
                futureComponentRecovered = portalResult.futureComponentRecovered;
                futureState = portalResult.futureState;

                break;
            }

            case 5:
                cout << "Thanks for playing Temporal Collapse!" << endl;
                break;
        }

        if (player.getChronoEnergy() <= 0) {
            cout << endl;
            cout << "You ran out of Chrono Energy." << endl;
            cout << "The time machine shuts down and you are stranded in time." << endl;
            cout << endl;
            cout << "GAME OVER" << endl;
            cout << "Thanks for playing Temporal Collapse!" << endl;
            menuChoice = maxMenuChoice;

            gameFinished = true;
        }
        else if (player.getTimeStability() <= 0) {
            cout << endl;
            cout << "Time Stability has reached zero." << endl;
            cout << "The time portal collapses." << endl;
            cout << endl;
            cout << "GAME OVER" << endl;
            cout << "Thanks for playing Temporal Collapse!" << endl;
            menuChoice = maxMenuChoice;

            gameFinished = true;
        }
    }


    return 0;
}


