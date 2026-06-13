#pragma once
#include "monsters.h"
#include "character.h"
#include "item.h"
#include <vector>

class Caves {
public:
    static std::vector<Monster> generateCaveGroup(const Character& character);
    static std::vector<Item> getItemReward();
    static void printCaveInfo();
};