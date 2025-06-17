
/*
 * Interactive Story Game - Dragon Quest Adventure
 * Author: Jayson Bartels
 * Date: 6/10/2025
 *
 * ==== Project Features ====
 * Variables (3+ types): 
 -player.h 19-24 int
 -player.h 29 string
 -player.h 48-53 bool
 
 * If/else statements:
-combat.cpp 29-107 
 
 * Switch statement: 
-player.cpp 20-24 and 30-34
 
 * For Loop:
-combat.cpp 158 
 
 * While Loop: 
-util.cpp 10 

 * Function w/ return: 
-combat.cpp 10-12 (rollD20)
 
 * Void function: 
-game.cpp 35-37
 
 * Function w/ params: 
-util.cpp 7-22 (getChoice)
 
 * Vector usage: 
-game.cpp 59-60
 
 * Enum: 
-player.h 6-10 and 12-16
 
 * File Reading:
-config.cpp 20-38 (loadConfig)
 
 * File Writing: 
 -game.cpp 234-258
 
 * Modern Feature (auto): 
 -config.cpp 27-31
 
 * Modern Feature (nullptr):
-game.cpp 235, 240, 270, and 272
 
 * ==========================
 */
#include <iostream>
#include "game.h"

int main() {
    Game game;  

    game.start();  

    std::cout << "\nThanks for playing!\n";
    return 0;
}
