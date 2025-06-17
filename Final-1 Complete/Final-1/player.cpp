#include "player.h"
#include "combat.h"
#include "util.h"
#include <iostream>

Player::Player()
    : name("Hero"), race(HUMAN), classType(KNIGHT),
      strength(10), dexterity(10), constitution(10),
      intelligence(10), wisdom(10), charisma(10),
      gold(3), potions(0), knowsDragonInfo(false),
      hasCloak(false), hasPoison(false), hasScroll(false), hasPendant(false),
      triedSneakOnBoard(false)
{
    calculateStats();
}

void Player::chooseRace() {
    std::cout << "Choose your race:\n1. Human\n2. Elf\n3. Kobold\n";
    int choice = Util::getChoice(3);
    switch (choice) {
        case 1: race = HUMAN; break;
        case 2: race = ELF; break;
        case 3: race = KOBOLD; break;
    }
}

void Player::chooseClass() {
    std::cout << "Choose your class:\n1. Knight\n2. Rogue\n3. Mage\n";
    int choice = Util::getChoice(3);
    switch (choice) {
        case 1: classType = KNIGHT; break;
        case 2: classType = ROGUE; break;
        case 3: classType = MAGE; break;
    }
}

void Player::calculateStats() {
    // Reset base
    strength = dexterity = constitution = intelligence = wisdom = charisma = 10;

    // Apply race bonuses
    switch (race) {
        case HUMAN:
            charisma += 2;
            break;
        case ELF:
            wisdom += 2;
            break;
        case KOBOLD:
            dexterity += 2;
            intelligence += 2;
            strength -= 1;
            constitution -= 1;
            break;
    }

    // Apply class bonuses
    switch (classType) {
        case KNIGHT:
            strength += 2;
            constitution += 1;
            break;
        case ROGUE:
            dexterity += 2;
            charisma += 1;
            break;
        case MAGE:
            intelligence += 2;
            wisdom += 1;
            break;
    }

    maxHP = 10 + constitution;
    currentHP = maxHP;
}

void Player::takeDamage(int dmg) {
    currentHP -= dmg;
    if (currentHP < 0) currentHP = 0;
}

void Player::heal(int amount) {
    currentHP += amount;
    if (currentHP > maxHP) currentHP = maxHP;
}

void Player::gainGold(int amount) {
    gold += amount;
    if (gold < 0) gold = 0;
}

bool Player::isAlive() const {
    return currentHP > 0;
}

void Player::printStats() const {
    std::cout << "Race: " << (race == HUMAN ? "Human" : race == ELF ? "Elf" : "Kobold") << "\n";
    std::cout << "Class: " << (classType == KNIGHT ? "Knight" : classType == ROGUE ? "Rogue" : "Mage") << "\n";
    std::cout << "HP: " << currentHP << "/" << maxHP << "\n";
    std::cout << "Gold: " << gold << ", Potions: " << potions << "\n";
    std::cout << "STR: " << strength << ", DEX: " << dexterity << ", CON: " << constitution << "\n";
    std::cout << "INT: " << intelligence << ", WIS: " << wisdom << ", CHA: " << charisma << "\n";
}

void Player::buyPotions() {
    if (gold <= 0) {
        std::cout << "You don't have enough gold to buy potions!\n";
        return;
    }
    int maxBuy = gold;
    potions += maxBuy * 3;
    gold = 0;
    std::cout << "You bought " << (maxBuy * 3) << " potions for " << maxBuy << " gold.\n";
}

void Player::usePotion() {
    if (potions > 0) {
        heal(5);
        potions--;
        std::cout << "You used a potion and healed 5 HP.\n";
    } else {
        std::cout << "You have no potions!\n";
    }
}

void Player::unlockInfoAboutDragon() {
    knowsDragonInfo = true;
}

bool Player::knowsAboutDragon() const {
    return knowsDragonInfo;
}

void Player::giveGoldToBeggarChildren() {
    if (gold >= 2) {
        gold -= 2;
        std::cout << "You give 2 gold to the hungry children. They smile gratefully.\n";
        std::cout << "The children tell you about the dragon's lair in the mountains.\n";
        unlockInfoAboutDragon();
    } else {
        std::cout << "You don't have enough gold, but the children still share what they know.\n";
        std::cout << "They tell you about the dragon demanding tribute from the village.\n";
        unlockInfoAboutDragon();
    }
}

void Player::enterForest() {
    std::cout << "\nYou enter the thick, enchanted forest...\n";
    std::cout << "Ancient runes glow faintly on the trees around you.\n";

    // Rune reading attempt
    bool canReadRunes = false;
    if (race == ELF) {
        std::cout << "As an elf, you can naturally read the ancient runes!\n";
        canReadRunes = true;
    } else {
        std::cout << "You attempt to decipher the mysterious runes...\n";
        if (Combat::statCheck(intelligence, 15)) {
            std::cout << "Your intelligence allows you to understand the runes!\n";
            canReadRunes = true;
        } else {
            std::cout << "The runes remain a mystery to you.\n";
        }
    }

    if (canReadRunes) {
        std::cout << "The runes offer ancient wisdom. Choose a stat to boost:\n";
        std::cout << "1. Strength\n2. Dexterity\n3. Constitution\n4. Intelligence\n5. Wisdom\n6. Charisma\n";
        int choice = Util::getChoice(6);

        switch (choice) {
            case 1: strength += 2; std::cout << "Your strength increases by 2!\n"; break;
            case 2: dexterity += 2; std::cout << "Your dexterity increases by 2!\n"; break;
            case 3: constitution += 2; maxHP += 2; currentHP += 2; std::cout << "Your constitution increases by 2!\n"; break;
            case 4: intelligence += 2; std::cout << "Your intelligence increases by 2!\n"; break;
            case 5: wisdom += 2; std::cout << "Your wisdom increases by 2!\n"; break;
            case 6: charisma += 2; std::cout << "Your charisma increases by 2!\n"; break;
        }
    }

    // Elven chest
    if (race == ELF) {
        std::cout << "\nYou discover a chest sealed with elven magic!\n";
        std::cout << "Your elven blood allows you to open it easily.\n";
        std::cout << "Inside you find a Cloak of Protection!\n";
        hasCloak = true;
    }

    // Forest encounter
    std::cout << "\nSudenly, you hear growling from the underbrush...\n";
    Combat::fightWolves(*this);
}

void Player::sailOcean() {
    std::cout << "\nYou approach the docks to board the ship sailing to the dragon's mountain...\n";

    if (!triedSneakOnBoard) {
        std::cout << "Do you want to:\n1. Pay 1 gold for passage\n2. Try to sneak aboard\n";
        int choice = Util::getChoice(2);

        if (choice == 1) {
            if (gold >= 1) {
                gold--;
                std::cout << "You pay for your passage aboard the ship.\n";
            } else {
                std::cout << "You don't have enough gold! The captain makes you work for your passage.\n";
                takeDamage(2); // Hard labor
            }
        } else {
            triedSneakOnBoard = true;
            std::cout << "You attempt to sneak aboard...\n";
            if (Combat::statCheck(dexterity, 12)) {
                std::cout << "You successfully sneak onto the ship!\n";
            } else {
                std::cout << "You're caught! The crew beats you and throws you in the brig.\n";
                takeDamage(5);
            }
        }
    }

    std::cout << "\nAs you sail across the dangerous waters, sudden shrieks fill the air!\n";
    std::cout << "Harpies attack the ship from above!\n";
    std::cout << "You see a fellow passenger who looks terrified and defenseless.\n";
    std::cout << "Do you:\n1. Help defend the passenger\n2. Focus on your own survival\n";
    int choice = Util::getChoice(2);

    if (choice == 1) {
        std::cout << "You decide to protect the frightened passenger!\n";
        std::cout << "This will make the fight harder, but the passenger might reward you.\n";
        hasPendant = true; // This will trigger harder fight in Combat::fightHarpies
        Combat::fightHarpies(*this);

        if (isAlive()) {
            std::cout << "The grateful passenger gives you a Lucky Pendant as thanks!\n";
            if (race == HUMAN) {
                std::cout << "As a human, your natural leadership inspired others to share their supplies.\n";
                potions += 2;
                std::cout << "You received 2 additional potions!\n";
            }
        }
    } else {
        hasPendant = false; // Easier fight
        Combat::fightHarpies(*this);
    }

    if (isAlive()) {
        std::cout << "The ship finally reaches the base of the dragon's mountain.\n";
    }
}

void Player::fightBugbear() {
    std::cout << "You decide to climb the treacherous mountain path!\n";
    std::cout << "Halfway up, you encounter a massive bugbear blocking the way!\n";

    std::cout << "Do you:\n1. Fight the bugbear guardian\n2. Try to sneak past\n";
    int choice = Util::getChoice(2);

    if (choice == 1) {
        Combat::fightBugbear(*this);
        if (isAlive()) {
            std::cout << "You search the bugbear's belongings and find a Protective Cloak!\n";
            hasCloak = true;
        }
    } else {
        std::cout << "You attempt to sneak past the sleeping bugbear...\n";
        if (Combat::statCheck(dexterity, 14)) {
            std::cout << "You successfully sneak past without waking it!\n";
        } else {
            std::cout << "You step on a branch! The bugbear wakes up angry!\n";
            Combat::fightBugbear(*this);
        }
    }
}

void Player::enterKoboldTunnel() {
    std::cout << "You approach the kobold tunnels at the base of the mountain.\n";
    std::cout << "Several kobold guards watch you suspiciously.\n";

    if (race == KOBOLD) {
        std::cout << "As a fellow kobold, you can speak their language!\n";
        std::cout << "\"Greetings, cousins! I seek passage to face the dragon.\"\n";
        std::cout << "The guards are impressed by your courage and give you a special poison!\n";
        std::cout << "\"This will give you +2 damage against the dragon!\" they say.\n";
        hasPoison = true;
        std::cout << "They let you pass peacefully through their tunnels.\n";
    } else {
        std::cout << "The kobolds block your path. What do you do?\n";
        std::cout << "1. Offer 1 gold as tribute\n2. Fight your way through\n";
        int choice = Util::getChoice(2);

        if (choice == 1) {
            if (gold >= 1) {
                gold--;
                std::cout << "The kobolds accept your tribute and let you pass peacefully.\n";
            } else {
                std::cout << "You don't have enough gold! The kobolds attack!\n";
                Combat::fightKobolds(*this);
            }
        } else {
            std::cout << "You charge into the kobold tunnels!\n";
            Combat::fightKobolds(*this);
        }
    }

    if (isAlive()) {
        std::cout << "You make your way through the winding tunnels to the dragon's lair.\n";
    }
}

Race Player::getRace() const {
    return race;
}

ClassType Player::getClass() const {
    return classType;
}

int Player::getStat(const std::string& statName) const {
    if (statName == "strength") return strength;
    if (statName == "dexterity") return dexterity;
    if (statName == "constitution") return constitution;
    if (statName == "intelligence") return intelligence;
    if (statName == "wisdom") return wisdom;
    if (statName == "charisma") return charisma;
    return 0;
}

int Player::getHP() const {
    return currentHP;
}

int Player::getMaxHP() const {
    return maxHP;
}

bool Player::hasItem(const std::string& itemName) const {
    if (itemName == "Protective Cloak") return hasCloak;
    if (itemName == "Dragon Poison") return hasPoison;
    if (itemName == "Scroll of Shielding") return hasScroll;
    if (itemName == "Lucky Pendant") return hasPendant;
    return false;
}