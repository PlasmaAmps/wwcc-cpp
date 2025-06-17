#ifndef COMBAT_H
#define COMBAT_H

#include "player.h"

namespace Combat {

    void fightDragon(Player& player);
    void fightBugbear(Player& player);
    void fightKobolds(Player& player);
    void fightHarpies(Player& player);
    void fightWolves(Player& player);  

    // Helper functions
    int rollD20();
    bool statCheck(int statValue, int difficulty);

}
#endif