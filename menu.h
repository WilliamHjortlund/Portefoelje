#pragma once
#include "character.h"
#include <vector>

class Menu {
public:
    void run();

private:
    void showMainMenu();
    void createCharacter();
    void startAdventure(Character& character);
    void adventureLoop(Character& character);

    Monster chooseFightMonster();
    bool offerCapturedMonster(Character& character, const Monster& captured);

    static std::vector<Monster> buildEnemyPool();
    static void printSeparator();
    static int readInt(const std::string& prompt, int min, int max);
    static std::string readLine(const std::string& prompt);
};
