#pragma once
#include <string>
#include <vector>
#include <map>

enum Race {
    HUMAN,
    ELF,
    KOBOLD
};

enum ClassType {
    KNIGHT,
    ROGUE,
    MAGE
};

struct PlayerStats {
    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;
};

class Player {
private:
    std::string name;
    Race race;
    ClassType classType;

    // Base stats
    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;

    // Gameplay stats
    int maxHP;
    int currentHP;
    int gold;
    int potions;

    // Flags
    bool knowsDragonInfo;
    bool hasCloak;
    bool hasPoison;
    bool hasScroll;
    bool hasPendant;
    bool triedSneakOnBoard;

public:
    Player();

    void chooseRace();
    void chooseClass();
    void calculateStats();

    void takeDamage(int dmg);
    void heal(int amount);
    void gainGold(int amount);  // method for adding/removing gold
    bool isAlive() const;

    void printStats() const;

    // Inventory & Info
    void buyPotions();
    void usePotion();
    void unlockInfoAboutDragon();
    bool knowsAboutDragon() const;
    void giveGoldToBeggarChildren();

    // Scene-specific methods
    void enterForest();
    void sailOcean();
    void fightBugbear();
    void enterKoboldTunnel();

    // Getters
    Race getRace() const;
    ClassType getClass() const;
    int getStat(const std::string& statName) const;
    int getHP() const;
    int getMaxHP() const;
    bool hasItem(const std::string& itemName) const;
};