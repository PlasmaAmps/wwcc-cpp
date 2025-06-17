#include "game.h"
#include "config.h"
#include "combat.h"
#include "util.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <functional>

// External global config object
extern GameConfig config;

Game::Game() : currentScene(1) {}

void Game::start() {
    loadConfig();
    showIntro();
    setupPlayer();

    while (currentScene <= 5 && checkPlayerAlive()) {
        playScene(currentScene);
        currentScene++;
    }

    endGame();
}

void Game::loadConfig() {
    if (!::loadConfig("game_config.cfg", config)) {
        std::cout << "No config file found. Using default configuration...\n";
        config = getDefaultConfig();
    }
}

void Game::showIntro() {
    std::cout << "Welcome, adventurer. Your journey begins now...\n\n";
}

void Game::setupPlayer() {
    player.chooseRace();
    player.chooseClass();
    player.calculateStats();
}

void Game::playScene(int scene) {
    switch (scene) {
        case 1: handleScene1(); break;
        case 2: handleScene2(); break;
        case 3: handleScene3(); break;
        case 4: handleScene4(); break;
        case 5: handleFinalBattle(); break;
        default:
            std::cout << "Unknown scene.\n";
            break;
    }
}


void Game::processSceneChoices(const std::vector<std::string>& choices, 
                              const std::vector<std::function<void()>>& actions) {
    
    int index = 1;
    for (const auto& choice : choices) {
        std::cout << index << ". " << choice << "\n";
        index++;
    }

    int selection = Util::getChoice(choices.size());

    
    if (selection <= static_cast<int>(actions.size())) {
        actions[selection - 1]();
    }
}

void Game::handleScene1() {
    std::cout << "\n--- Scene 1: Dusty Road ---\n";
    std::cout << "You approach a village and notice a house lies in rubble, still smoldering.\n";
    std::cout << "The acrid smell of dragonfire lingers in the air.\n";

    std::cout << "\nWhat do you do?\n";
    std::cout << "1. Investigate the burned ruins\n2. Continue directly to town\n";
    int choice = Util::getChoice(2);

    if (choice == 1) {
        std::cout << "\nYou carefully search through the charred remains...\n";
        std::cout << "Among the ashes, you find signs of a dragon's devastating fire attack.\n";
        std::cout << "Hidden beneath some rubble, you discover a small pouch with 1 gold!\n";

        // Award gold for investigating
        player.gainGold(1);
        std::cout << "You gained 1 gold from your investigation.\n";

        std::cout << "\nWith evidence of the dragon's destruction in hand, you head to the village.\n";
    } else {
        std::cout << "\nYou decide not to waste time and walk directly toward the village.\n";
    }
}

void Game::handleScene2() {
    std::cout << "\n--- Scene 2: Village Square ---\n";
    std::cout << "The village bustles with nervous energy. People whisper in hushed tones.\n";
    std::cout << "You notice several hungry-looking children begging near the fountain.\n";

    bool hasVisitedLocation = false;

    while (!hasVisitedLocation) {
        std::cout << "\nWhere do you go?\n";
        std::cout << "1. Approach the begging children\n";
        std::cout << "2. Enter the tavern\n";
        std::cout << "3. Visit the merchant shops\n";
        std::cout << "4. Ask around the town square\n";
        std::cout << "5. Leave town immediately\n";

        int choice = Util::getChoice(5);

        switch (choice) {
            case 1: {
                std::cout << "\nYou approach the group of thin, dirty children.\n";
                std::cout << "\"Please sir, we're so hungry,\" one whispers.\n";
                std::cout << "\nDo you:\n1. Give them 2 gold\n2. Just ask for information\n";

                int childChoice = Util::getChoice(2);
                if (childChoice == 1) {
                    player.giveGoldToBeggarChildren();
                } else {
                    std::cout << "\"What can you tell me about what's been happening here?\"\n";
                    std::cout << "The children exchange glances before speaking:\n";
                    std::cout << "\"The dragon comes every month demanding tribute...\"\n";
                    player.unlockInfoAboutDragon();
                }
                hasVisitedLocation = true;
                break;
            }

            case 2: {
                std::cout << "\nYou push through the tavern's heavy wooden doors.\n";
                std::cout << "The air is thick with pipe smoke and fearful whispers.\n";
                std::cout << "You overhear drunken patrons talking about the dragon's greed:\n";
                std::cout << "\"...takes all our gold and livestock every month...\"\n";
                std::cout << "\"...lair is somewhere high in the mountains to the north...\"\n";
                player.unlockInfoAboutDragon();
                hasVisitedLocation = true;
                break;
            }

            case 3: {
                std::cout << "\nYou browse the merchant stalls in the marketplace.\n";
                std::cout << "A potion seller approaches: \"Healing potions! 3 for 1 gold!\"\n";
                std::cout << "\nDo you want to buy potions? (1. Yes, 2. No)\n";

                int potionChoice = Util::getChoice(2);
                if (potionChoice == 1) {
                    player.buyPotions();
                } else {
                    std::cout << "You politely decline and continue browsing.\n";
                }
                hasVisitedLocation = true;
                break;
            }

            case 4: {
                if (player.knowsAboutDragon()) {
                    std::cout << "\nYou ask the locals about the dragon's location.\n";
                    std::cout << "\"Aye, the beast lives high in the mountains to the north.\"\n";
                    std::cout << "\"You can get there by ship across the sea, or through the forest.\"\n";
                    std::cout << "\"Many have tried to reach it... few return.\"\n";
                } else {
                    std::cout << "\nThe villagers seem reluctant to talk to strangers.\n";
                    std::cout << "\"You should talk to others first,\" one mutters.\n";
                }
                break;
            }

            case 5: {
                cowardsWin();
                return;
            }
        }
    }

    std::cout << "\nWith information gathered, you prepare for the journey ahead.\n";
}

void Game::handleScene3() {
    std::cout << "\n--- Scene 3: The Journey Begins ---\n";
    std::cout << "You stand at the edge of the village, looking toward the distant mountains.\n";
    std::cout << "The dragon's lair awaits, but you must choose your path carefully.\n";

    std::cout << "\nHow will you reach the dragon's mountain?\n";
    std::cout << "1. Take the forest path (dangerous but free)\n";
    std::cout << "2. Sail across the sea (safer but costs gold)\n";
    std::cout << "3. Turn back and abandon your quest\n";

    int choice = Util::getChoice(3);

    if (choice == 1) {
        player.enterForest();
    } else if (choice == 2) {
        player.sailOcean();
    } else {
        cowardsWin();
        return;
    }
}

void Game::handleScene4() {
    std::cout << "\n--- Scene 4: The Dragon's Mountain ---\n";
    std::cout << "You stand before a towering mountain, its peak shrouded in ominous clouds.\n";
    std::cout << "Somewhere up there, the dragon waits in its lair.\n";

    std::cout << "\nHow do you want to reach the summit?\n";
    std::cout << "1. Climb the treacherous mountain face\n";
    std::cout << "2. Use the kobold tunnels at the base\n";

    int choice = Util::getChoice(2);

    if (choice == 1) {
        player.fightBugbear();
    } else {
        player.enterKoboldTunnel();
    }
}

void Game::handleFinalBattle() {
    std::cout << "\n--- Final Battle: The Dragon's Lair ---\n";
    std::cout << "You enter a vast cavern filled with piles of gold and treasure.\n";
    std::cout << "The air shimmers with heat as massive eyes open in the darkness...\n";

    Combat::fightDragon(player);
}


void Game::saveGameStats() {
    std::ofstream* file = nullptr;

    try {
        file = new std::ofstream("game_stats.txt");

        if (file != nullptr && file->is_open()) {
            *file << "=== Dragon Quest Game Statistics ===\n";

            // Get player race and class as strings for output
            std::string raceStr = (player.getRace() == HUMAN) ? "Human" : 
                                 (player.getRace() == ELF) ? "Elf" : "Kobold";
            std::string classStr = (player.getClass() == KNIGHT) ? "Knight" : 
                                  (player.getClass() == ROGUE) ? "Rogue" : "Mage";

            *file << "Player Race: " << raceStr << "\n";
            *file << "Player Class: " << classStr << "\n";
            *file << "Final HP: " << player.getHP() << "/" << player.getMaxHP() << "\n";
            *file << "Game Outcome: " << (player.isAlive() ? "Victory!" : "Defeat") << "\n";
            *file << "Strength: " << player.getStat("strength") << "\n";
            *file << "Dexterity: " << player.getStat("dexterity") << "\n";
            *file << "Constitution: " << player.getStat("constitution") << "\n";
            *file << "Intelligence: " << player.getStat("intelligence") << "\n";
            *file << "Wisdom: " << player.getStat("wisdom") << "\n";
            *file << "Charisma: " << player.getStat("charisma") << "\n";

            file->close();
            std::cout << "Game statistics saved to game_stats.txt\n";
        } else {
            std::cout << "Unable to save game statistics.\n";
        }
    } catch (...) {
        std::cout << "Error occurred while saving game statistics.\n";
    }

    // Clean up
    if (file != nullptr) {
        delete file;
        file = nullptr;
    }
}

void Game::endGame() {
    if (player.isAlive()) {
        std::cout << "\n=== VICTORY! ===\n";
        std::cout << "You have slain the dragon and freed the land from its tyranny!\n";
        std::cout << "The villagers will sing songs of your heroic deeds for generations!\n";
    } else {
        std::cout << "\n=== DEFEAT ===\n";
        std::cout << "You fought bravely, but the dragon proved too powerful.\n";
        std::cout << "Your sacrifice will not be forgotten, though the terror continues...\n";
    }

    showStats();
    saveGameStats(); // Save game statistics to file
}

bool Game::checkPlayerAlive() {
    return player.isAlive();
}

void Game::showStats() {
    std::cout << "\n--- Final Character Stats ---\n";
    player.printStats();
}

void Game::cowardsWin() {
    std::cout << "\n=== COWARD'S ENDING ===\n";
    std::cout << "You flee from the village, abandoning your quest entirely.\n";
    std::cout << "The dragon continues to terrorize the land, but hey...\n";
    std::cout << "At least you're still alive! (For now...)\n";
    std::cout << "\n[Achievement Unlocked: Better Safe Than Sorry]\n";
    currentScene = 999; // Force end game
}