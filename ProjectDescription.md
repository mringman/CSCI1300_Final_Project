# Project Description

## Theme

**Temporal Collapse** is a single-player, text-based adventure game set inside a research laboratory where a prototype time machine has malfunctioned. The accident sends three important stability components into different periods of history and opens unstable portals throughout time.

The player chooses a member of the research team and travels to Ancient Egypt, the Wild West, and the year 2352. In each era, the player must explore locations, interact with characters, complete quests, and recover one missing component.

The game translates the original Stardew Valley project requirements into a time-travel setting:

- The final Community Center bundle becomes the collection of three missing time-machine components.
- Stardew Valley locations become different eras and their sublocations.
- Villagers become historical and futuristic NPCs.
- The JojaMart shortcut becomes the option to use dishonest or illegal methods.
- The season time limit becomes Time Stability.
- Energy is represented by Chrono Energy.

## Classes

### Character Class

    The `Character` class is the base class for both players and NPCs.

    It stores:

    - Character name
    - Character health

    The `Player` and `NPC` classes inherit from the `Character` class.

### Player Class

    The `Player` class stores the player's important information and resources.

    It stores:

    - Player name
    - Character type
    - Chrono Energy
    - Time Stability
    - Luck
    - Sociability
    - Inventory

    Luck affects random events during risky routes. Sociability can help the player persuade characters during honest routes. The inventory stores each recovered stability component.

### NPC Class

    The `NPC` class represents the non-player characters encountered throughout the game.

    It stores:

    - NPC name and health inherited from `Character`
    - Dialogue
    - Quest information
    - Reward information
    - Whether the NPC has been encountered

    NPCs can provide quests, hints, rewards, access to restricted locations, and assistance recovering components.

### Era Class

    The `Era` class represents a major location in the game.

    It stores:

    - Era name
    - Sublocations
    - NPC objects
    - Whether the missing component has been recovered

    The `Era` class stores a vector of `NPC` objects. This allows each era to keep track of its own characters and display their encounter and quest information.

## Limited Resources

### Time Stability

Time Stability is the required time limit for the game. It represents how stable the timeline remains after the time-machine accident.

Traveling through portals and making dangerous choices can lower Time Stability. If it reaches zero, the timeline collapses and the player loses.

The amount of Time Stability remaining also affects the final attempt to repair the time machine. Finishing with high Time Stability gives the player a greater chance of successfully restoring the timeline.

### Chrono Energy

    Chrono Energy is the additional limited resource beyond time.

    The player uses Chrono Energy when:

    - Traveling through a portal
    - Exploring locations
    - Completing quests
    - Planning risky actions
    - Recovering components
    - Failing certain challenges

    If Chrono Energy reaches zero, the time machine shuts down and the player becomes stranded in time.

## Handling Time

The game handles time through the player's Time Stability value rather than through numbered days.

Major actions and portal travel reduce Time Stability. Risky or illegal decisions can reduce it more quickly than honest decisions. This gives the player a limited number of actions before the timeline collapses.

The player must decide how much exploration and risk they can afford before returning to the laboratory.

## Tradeoff System

The game's Joja-style tradeoff system allows the player to choose between honest and risky routes.

### Honest Routes

    The honest routes usually require the player to:

    - Talk to multiple NPCs
    - Complete quests
    - Help people
    - Repair equipment
    - Earn trust
    - Receive permission to enter restricted locations

    These routes may require more Chrono Energy because they involve additional actions, but they usually preserve more Time Stability.

### Risky Routes

    The risky routes may involve:

    - Stealing
    - Robbery
    - Illegal entry
    - Smuggling
    - Hacking security systems
    - Working with suspicious characters

    These routes can allow the player to reach the component more quickly, but they may cost additional Chrono Energy, lower Time Stability, trigger random challenges, or cause guards and security systems to become suspicious.

    The player must decide whether saving actions is worth the added danger.

## Map and Location Style

The laboratory acts as the main hub of the game. From the laboratory, the player can enter portals leading to three eras.

### Laboratory

    - Time Portals
    - Repair Workbench

### Ancient Egypt

    - Crypt
    - Worship Center
    - Market

    The player must recover the Scarab of the Endless Dawn. The player can earn the priests' trust by helping the market or attempt to steal the scarab with Seti.

### Wild West

    - Gold Mine
    - Town Saloon
    - Old Man Jankins' Cabin

    The player must recover the Temporal Cog from a collapsed mine. The player can cooperate with the sheriff or work with Wade Blackwell to steal mining equipment.

### Future 2352

    - Quantum Research Center
    - AI Workshop
    - Neon Gardens

    The player must recover the Quantum Stabilizer Core. The player can repair the facility AI and earn legal clearance or work with Nyx to break into the Research Center.

    Each era displays its sublocations, characters, and component-recovery status through the terminal interface.

## Main Objective

The player must recover these three missing stability components:

1. Scarab of the Endless Dawn
2. Temporal Cog
3. Quantum Stabilizer Core

After recovering all three components, the player must return to the laboratory and approach the Repair Workbench.

The collected components act as the equivalent of the final Community Center bundle.

## Win and Lose Conditions

### Win Condition

    The player wins by:

    1. Recovering all three missing components
    2. Returning to the laboratory
    3. Installing the components at the Repair Workbench
    4. Successfully stabilizing the timeline

    The final repair uses the player's remaining Time Stability to determine the chance of success. A Time Stability value of 80 or higher guarantees a successful repair.

### Lose Conditions

    The player loses if:

    - Chrono Energy reaches zero
    - Time Stability reaches zero
    - The final repair attempt fails

    If the final repair fails, the time machine is destroyed and the player is trapped in a randomly selected era.

## Extra Credit

None.

Weighted route planning and a save/load system were included in the original plan, but they were not implemented as part of the final version.