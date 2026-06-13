#pragma once
#include "monsters.h"
#include "item.h"
#include <vector>

class Caves {
public:
    static Monster generateCaveMonster();
    static std::vector<Item> getItemReward();
    static void printCaveInfo();
};
