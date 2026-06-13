#pragma once
#include "character.h"
#include "item.h"
#include "caves.h"
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
    void equipMonsterWithItems(Monster& monster);
    void giveItemToMonster(Character& character);
    void caveAdventure(Character& character);
    void handleCaveReward(Character& character, const std::vector<Item>& rewards);

    static std::vector<Monster> buildEnemyPool();
    static std::vector<Item> buildItemPool();
    static void printSeparator();
    static int readInt(const std::string& prompt, int min, int max);
    static std::string readLine(const std::string& prompt);
};