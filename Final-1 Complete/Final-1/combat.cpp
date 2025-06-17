#include "combat.h"
#include "util.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

namespace Combat {

    // Roll a d20 (1-20)
    int rollD20() {
        return (std::rand() % 20) + 1;
    }

    // Stat check: roll d20 + stat/4 >= difficulty
    bool statCheck(int statValue, int difficulty) {
        int roll = rollD20();
        int total = roll + (statValue / 4);
        std::cout << "Stat check roll: " << roll << " + " << statValue / 4 << " = " << total << " (need " << difficulty << ")\n";
        return total >= difficulty;
    }

    // Simple turn-based fight helper
    void enemyAttack(Player& player, int damage) {
        std::cout << "Enemy attacks for " << damage << " damage!\n";
        player.takeDamage(damage);
        std::cout << "Your HP: " << player.getHP() << "/" << player.getMaxHP() << "\n";
    }

    void fightDragon(Player& player) {
        std::cout << "The dragon looms before you, its scales shimmering with deadly heat.\n";

        // dragon stats
        int dragonHP = 80;  
        int dragonAttackDamage = 7;  
        bool scrollUsed = false;

        while (dragonHP > 0 && player.isAlive()) {
            std::cout << "\nYour HP: " << player.getHP() << "/" << player.getMaxHP() << "\n";
            std::cout << "Dragon HP: " << dragonHP << "\n";
            std::cout << "Choose your action:\n1. Attack\n2. Defend\n3. Use Potion\n";
            int choice = Util::getChoice(3);

            bool defendThisTurn = false;
            if (choice == 1) {
                int baseDamage = player.getStat("strength") / 2 + (rollD20() / 2);
                int damage = baseDamage;

                // Apply poison bonus if player has it
                if (player.hasItem("Dragon Poison")) {
                    damage += 2;
                    std::cout << "Your poison coating adds extra damage!\n";
                }

                std::cout << "You strike the dragon for " << damage << " damage!\n";
                dragonHP -= damage;
            }
            else if (choice == 2) {
                std::cout << "You brace yourself for the dragon's next attack.\n";
                defendThisTurn = true;
            }
            else if (choice == 3) {
                player.usePotion();
            }

            if (dragonHP <= 0) break;

            // Dragon breath attack
            static int turnCount = 0;
            turnCount++;

            bool breathAttack = (turnCount % 4 == 0);

            int attackDamage = breathAttack ? dragonAttackDamage * 2 : dragonAttackDamage;

            // Scroll of Shielding auto-defend first breath
            if (player.hasItem("Scroll of Shielding") && breathAttack && !scrollUsed) {
                std::cout << "Your Scroll of Shielding activates, automatically defending the breath attack!\n";
                scrollUsed = true;
                defendThisTurn = true;
            }

            // Protective Cloak reduces damage by 2
            if (player.hasItem("Protective Cloak")) {
                attackDamage -= 2;
                if (attackDamage < 1) attackDamage = 1;
                std::cout << "Your Protective Cloak reduces the damage!\n";
            }

            if (defendThisTurn) {
                attackDamage /= 2;
                std::cout << "You reduce the incoming damage by half.\n";
            }

            if (breathAttack) {
                std::cout << "The dragon breathes fire!\n";
            }

            enemyAttack(player, attackDamage);
        }

        if (player.isAlive()) {
            std::cout << "You have slain the dragon!\n";
            std::cout << "The dragon's hoard contains incredible treasures!\n";
        } else {
            std::cout << "The dragon has defeated you...\n";
        }
    }

    void fightBugbear(Player& player) {
        std::cout << "A large bugbear blocks your path, growling fiercely.\n";

        int bugbearHP = 40;  
        int bugbearAttack = 6;  

        while (bugbearHP > 0 && player.isAlive()) {
            std::cout << "\nYour HP: " << player.getHP() << "/" << player.getMaxHP() << "\n";
            std::cout << "Bugbear HP: " << bugbearHP << "\n";
            std::cout << "Choose your action:\n1. Attack\n2. Defend\n3. Use Potion\n";
            int choice = Util::getChoice(3);

            bool defendThisTurn = false;
            if (choice == 1) {
                int damage = player.getStat("strength") / 2 + (rollD20() / 2);
                std::cout << "You hit the bugbear for " << damage << " damage!\n";
                bugbearHP -= damage;
            }
            else if (choice == 2) {
                std::cout << "You take a defensive stance.\n";
                defendThisTurn = true;
            }
            else if (choice == 3) {
                player.usePotion();
            }

            if (bugbearHP <= 0) break;

            int attackDamage = bugbearAttack;
            if (defendThisTurn) {
                attackDamage /= 2;
                std::cout << "You reduce the incoming damage by half.\n";
            }
            enemyAttack(player, attackDamage);
        }

        if (player.isAlive())
            std::cout << "You defeated the bugbear and can proceed.\n";
        else
            std::cout << "The bugbear has defeated you...\n";
    }

    void fightKobolds(Player& player) {
        std::cout << "You enter the kobold tunnels and are swarmed by small, quick kobolds!\n";

        const int koboldCount = 3;  
        int koboldHP[koboldCount] = {12, 12, 12};  
        int koboldAttack = 4;  

        for (int i = 0; i < koboldCount && player.isAlive(); i++) {
            std::cout << "\nKobold " << (i+1) << " attacks!\n";

            while (koboldHP[i] > 0 && player.isAlive()) {
                std::cout << "\nYour HP: " << player.getHP() << "/" << player.getMaxHP() << "\n";
                std::cout << "Kobold " << (i+1) << " HP: " << koboldHP[i] << "\n";
                std::cout << "Choose your action:\n1. Attack\n2. Defend\n3. Use Potion\n";
                int choice = Util::getChoice(3);

                bool defendThisTurn = false;
                if (choice == 1) {
                    int damage = player.getStat("strength") / 2 + (rollD20() / 2);
                    std::cout << "You strike kobold " << (i+1) << " for " << damage << " damage!\n";
                    koboldHP[i] -= damage;
                }
                else if (choice == 2) {
                    std::cout << "You take a defensive stance.\n";
                    defendThisTurn = true;
                }
                else if (choice == 3) {
                    player.usePotion();
                }

                if (koboldHP[i] <= 0) {
                    std::cout << "You have defeated kobold " << (i+1) << "!\n";
                    break;
                }

                int attackDamage = koboldAttack;
                if (defendThisTurn) {
                    attackDamage /= 2;
                    std::cout << "You reduce the incoming damage by half.\n";
                }
                enemyAttack(player, attackDamage);
            }
        }

        if (player.isAlive())
            std::cout << "You cleared the kobold tunnels!\n";
        else
            std::cout << "The kobolds have overwhelmed you...\n";
    }

    void fightHarpies(Player& player) {
        std::cout << "The screeching harpy descends from above!\n";

        int harpyHP = 25;  
        int harpyAttack = 6;  

        // Second harpy if player helped crewmate
        bool secondHarpy = player.hasItem("Lucky Pendant");
        if (secondHarpy) {
            std::cout << "A second harpy joins the fight - this will be tougher!\n";
        }

        for (int i = 0; i < (secondHarpy ? 2 : 1); i++) {
            int currentHP = harpyHP;
            std::cout << "\nFighting harpy " << (i+1) << "!\n";

            while (currentHP > 0 && player.isAlive()) {
                std::cout << "\nYour HP: " << player.getHP() << "/" << player.getMaxHP() << "\n";
                std::cout << "Harpy " << (i+1) << " HP: " << currentHP << "\n";
                std::cout << "Choose your action:\n1. Attack\n2. Defend\n3. Use Potion\n";
                int choice = Util::getChoice(3);

                bool defendThisTurn = false;
                if (choice == 1) {
                    int damage = player.getStat("strength") / 2 + (rollD20() / 2);
                    std::cout << "You hit harpy " << (i+1) << " for " << damage << " damage!\n";
                    currentHP -= damage;
                }
                else if (choice == 2) {
                    std::cout << "You take a defensive stance.\n";
                    defendThisTurn = true;
                }
                else if (choice == 3) {
                    player.usePotion();
                }

                if (currentHP <= 0) {
                    std::cout << "You defeated harpy " << (i+1) << "!\n";
                    break;
                }

                int attackDamage = harpyAttack;
                if (defendThisTurn) {
                    attackDamage /= 2;
                    std::cout << "You reduce the incoming damage by half.\n";
                }
                enemyAttack(player, attackDamage);
            }
        }

        if (player.isAlive())
            std::cout << "You have survived the harpy attack!\n";
        else
            std::cout << "The harpies have defeated you...\n";
    }

    void fightWolves(Player& player) {
        std::cout << "A pack of dire wolves emerges from the forest!\n";

        int wolfHP = 20;  
        int wolfAttack = 6;

        while (wolfHP > 0 && player.isAlive()) {
            std::cout << "\nYour HP: " << player.getHP() << "/" << player.getMaxHP() << "\n";
            std::cout << "Wolf Pack HP: " << wolfHP << "\n";
            std::cout << "Choose your action:\n1. Attack\n2. Defend\n3. Use Potion\n";
            int choice = Util::getChoice(3);

            bool defendThisTurn = false;
            if (choice == 1) {
                int damage = player.getStat("strength") / 2 + (rollD20() / 2);
                std::cout << "You strike the wolves for " << damage << " damage!\n";
                wolfHP -= damage;
            }
            else if (choice == 2) {
                std::cout << "You take a defensive stance.\n";
                defendThisTurn = true;
            }
            else if (choice == 3) {
                player.usePotion();
            }

            if (wolfHP <= 0) break;

            int attackDamage = wolfAttack;
            if (defendThisTurn) {
                attackDamage /= 2;
                std::cout << "You reduce the incoming damage by half.\n";
            }

            enemyAttack(player, attackDamage);
        }

        if (player.isAlive()) {
            std::cout << "You defeated the wolf pack and continue through the forest!\n";
        } else {
            std::cout << "The wolves have overwhelmed you...\n";
        }
    }
}