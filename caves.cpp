#include "caves.h"
#include <iostream>
#include <random>
#include <algorithm>

std::vector<Monster> Caves::generateCaveGroup(const Character& character) {
    // Beregn gennemsnitlig styrke og HP på spillerens levende monstre
    int totalStrength = 0;
    int totalHp = 0;
    int count = 0;

    for (int i = 0; i < character.getMonsterCount(); i++) {
        // getMonster er ikke-const, så vi caster
        Monster* m = const_cast<Character&>(character).getMonster(i);
        if (m && m->isAlive()) {
            totalStrength += m->getStrength();
            totalHp       += m->getBaseHp();
            count++;
        }
    }

    if (count == 0) {
        totalStrength = 5;
        totalHp       = 30;
        count         = 1;
    }

    int avgStr = totalStrength / count;
    int avgHp  = totalHp / count;

    // Tre fjender: svag → middel → stærk (80% / 100% / 120% af spillerniveau)
    // HP og styrke er minimum 5/10 så fjender aldrig er trivielle
    struct EnemyDef { std::string name; double strMult; double hpMult; };
    std::vector<EnemyDef> defs = {
        { "Skelet Kriger", 0.8, 0.8 },
        { "Undead Mage",   1.0, 0.7 },  // lidt mere styrke, lidt mindre HP
        { "Grotte Drage",  1.2, 1.2 },
    };

    std::vector<Monster> group;
    for (const auto& def : defs) {
        int str = std::max(5,  (int)(avgStr * def.strMult));
        int hp  = std::max(10, (int)(avgHp  * def.hpMult));
        group.emplace_back(def.name, hp, str);
    }
    return group;
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