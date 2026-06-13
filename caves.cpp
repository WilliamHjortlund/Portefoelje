#include "caves.h"
#include <iostream>
#include <random>

Monster Caves::generateCaveMonster() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 2);
    
    int choice = dis(gen);
    
    switch (choice) {
        case 0:
            return Monster("Skelet Kriger", 25, 7);
        case 1:
            return Monster("Undead Mage", 20, 10);
        case 2:
            return Monster("Grotte Drage", 35, 9);
        default:
            return Monster("Skelet Kriger", 25, 7);
    }
}

std::vector<Item> Caves::getItemReward() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 2);
    
    std::vector<Item> rewards;
    int itemCount = 1 + (dis(gen) % 2); // 1 eller 2 items
    
    std::vector<Item> itemPool = {
        Item("Sværd", ItemType::STRENGTH_BOOST, 5),
        Item("Energidrik", ItemType::HEALTH_BOOST, 10),
        Item("Skjold", ItemType::DEFENSE_BOOST, 3),
    };
    
    for (int i = 0; i < itemCount; i++) {
        int randomItem = dis(gen) % itemPool.size();
        rewards.push_back(itemPool[randomItem]);
    }
    
    return rewards;
}

void Caves::printCaveInfo() {
    std::cout << "\n=== GROTTEKAMP ===\n";
    std::cout << "I grottekampe møder du stærkere monstre.\n";
    std::cout << "Hvis du vinder, får du items i stedet for monstre!\n";
}
