#include "config.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "player.h"

GameConfig getDefaultConfig() {
    GameConfig config;
    config.baseStats = {
        10, // strength
        10, // dexterity
        10, // constitution
        10, // intelligence
        10, // wisdom
        10  // charisma
    };
    return config;
}

bool loadConfig(const std::string& filename, GameConfig& config) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        return false; // Could not open config file
    }

    PlayerStats stats = {};
    auto line = std::string{};  
    while (std::getline(inFile, line)) {
        auto iss = std::istringstream{line};  
        auto key = std::string{};            
        auto value = int{};                  
        if (iss >> key >> value) {
            if (key == "strength") stats.strength = value;
            else if (key == "dexterity") stats.dexterity = value;
            else if (key == "constitution") stats.constitution = value;
            else if (key == "intelligence") stats.intelligence = value;
            else if (key == "wisdom") stats.wisdom = value;
            else if (key == "charisma") stats.charisma = value;
        }
    }

    config.baseStats = stats;
    return true;
}

GameConfig config;