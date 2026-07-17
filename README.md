# CSCI1300_Final_Project

# CSCI 1300 Final Project

## Theme

Temporal Collapse is a text-based adventure game where a prototype time machine malfunctions, opening portals to four different eras: Ancient Egypt, the Wild West, and the year 2352. The player chooses a character from the research team and travels through each era to recover the missing stability components before the portals collapse from weakening time stability. Along the way, players can either negotiate honestly for the components or take the riskier route by stealing them, with each choice affecting the stability of the timeline and the game's ending.

## Goal

The goal of the game is to recover all three missing stability components:

- Scarab of the Endless Dawn from Ancient Egypt
- Temporal Cog from the Wild West
- Quantum Stabilizer Core from the year 2352

After collecting all three components, the player must return to the laboratory and use the Repair Workbench to stabilize the timeline.
The player loses if Chrono Energy or Time Stability reaches zero. The final repair is based on the amount of Time Stability remaining.

## How to compile and run

Compile:

g++ -std=c++11 -Wall -Werror -Wpedantic main.cpp player.cpp character.cpp NPC.cpp era.cpp -o game

Run:

./temporalCollapse

(The program also requires these input files: playerClasses.txt & portal.txt)

## How to play

1. Enter a player name.
2. Select a character type from the options loaded from playerClasses.txt.
3. Use the main menu to:
    * View player stats and inventory
    * Talk to Dr. Baige
    * Explore the laboratory
    * Enter a time portal
    * Quit the game
4. Travel to Ancient Egypt, the Wild West, and the year 2352.
5. Explore locations and interact with characters in each era.
6. Choose between honest and risky routes to recover each component.
7. Monitor Chrono Energy and Time Stability throughout the game.
8. Return to the laboratory after recovering all three components.
9. Use the Repair Workbench to attempt to restore the timeline.

Chrono Energy is used when traveling, exploring, and completing major actions. If Chrono Energy reaches zero, the player becomes stranded in time.

Time Stability acts as the game’s time limit. Portal jumps and risky decisions weaken Time Stability. If it reaches zero, the timeline collapses.

## Classes

Character - The Character class is the base class for characters in the game.
    It stores:

    * Name
    * Health

    Both the Player and NPC classes inherit from Character.



Player - The Player class represents the person playing the game.
    It stores:

    * Character type
    * Chrono Energy
    * Time Stability
    * Luck
    * Sociability
    * Inventory

    Luck affects the success of risky actions, while Sociability can help the player succeed during honest interactions.



NPC - The NPC class represents non-player characters found throughout the game.
    It stores:

    * Dialogue
    * Quest information
    * Reward information
    * Whether the player has talked to the NPC

    NPCs provide quests, information, access to locations, and possible rewards.



Era - The Era class represents an area that the player can visit.
    It stores:

    * Era name
    * Sublocations
    * NPC objects
    * Whether the era’s component has been recovered

    The Era class stores a vector of NPC objects, allowing each era to track its own characters and whether they have been encountered.

## Extra credit

None.