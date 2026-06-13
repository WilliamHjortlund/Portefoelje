#pragma once
#include "monsters.h"
#include "item.h"
#include <vector>

class Caves {
public:
    static std::vector<Monster> generateCaveGroup();
    static std::vector<Item> getItemReward();
    static void printCaveInfo();
};
