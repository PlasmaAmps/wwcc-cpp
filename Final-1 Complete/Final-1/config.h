#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include "player.h" // For PlayerStats


struct GameConfig {
    PlayerStats baseStats;
};

// Loads stats from file, returns true if file found and parsed
bool loadConfig(const std::string& filename, GameConfig& config);

// Returns default PlayerStats if file load fails
GameConfig getDefaultConfig();

#endif
