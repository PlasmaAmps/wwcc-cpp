#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <functional>
#include "player.h"

class Game {
public:
    Game();

    void start();              // Starts the game and main loop
    void setupPlayer();        // Handles race/class selection and stat setup
    void loadConfig();         // Loads base stats from config file
    void playScene(int scene); // Advances to a specific scene
    void endGame();            // Ends the game and shows final result
    void saveGameStats();      // Saves final game statistics to file

private:
    Player player;
    int currentScene;

    void showIntro();
    void handleScene1();
    void handleScene2();
    void handleScene3();
    void handleScene4();
    void handleFinalBattle();

    void cowardsWin();         // Handles joke ending
    void showStats();          // Display player stats at various points
    void processSceneChoices(const std::vector<std::string>& choices, 
                           const std::vector<std::function<void()>>& actions);

    bool checkPlayerAlive();   // Determines if player can continue
};

#endif