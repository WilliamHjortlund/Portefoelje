#include "caves.h"
#include <iostream>
#include <random>

std::vector<Monster> Caves::generateCaveGroup() {
    return {
        Monster("Skelet Kriger", 25,  7),
        Monster("Undead Mage",   20, 10),
        Monster("Grotte Drage",  35,  9),
    };
}

std::vector<Item> Caves::getItemReward() {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::vector<Item> itemPool = {
        Item("Sværd",      ItemType::STRENGTH_BOOST, 5),
        Item("Energidrik", ItemType::HEALTH_BOOST,   10),
        Item("Skjold",     ItemType::DEFENSE_BOOST,  3),
        Item("Løbesko",    ItemType::STATUS_EFFECT,  StatusEffect::SPEED_II),
    };

    std::uniform_int_distribution<> dis(0, (int)itemPool.size() - 1);

    std::vector<Item> rewards;
    int itemCount = 1 + (dis(gen) % 2); // 1 eller 2 items

    for (int i = 0; i < itemCount; i++) {
        rewards.push_back(itemPool[dis(gen)]);
    }
    return rewards;
}

void Caves::printCaveInfo() {
    std::cout << "\n=== GROTTEKAMP ===\n";
    std::cout << "I grottekampe møder du tre monstre efter hinanden.\n";
    std::cout << "Du skal besejre alle tre for at vinde items!\n";
}