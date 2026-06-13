#include "character.h"
#include <iostream>


Character::Character(const std::string& name)
    : name(name), monsterCount(0)
{
    monsters[0] = Monster("Hest", 30, 5);
    monsters[1] = Monster("Hest", 30, 5);
    monsterCount = 2;
}

std::string Character::getName() const { return name; }
int Character::getMonsterCount() const { return monsterCount; }

Monster* Character::getMonster(int index) {
    if (index < 0 || index >= monsterCount) return nullptr;
    return &monsters[index];
}

bool Character::hasAliveMonsters() const {
    for (int i = 0; i < monsterCount; i++) {
        if (monsters[i].isAlive()) return true;
    }
    return false;
}

bool Character::addMonster(const Monster& monster) {
    if (monsterCount >= MAX_MONSTERS) return false;
    monsters[monsterCount++] = monster;
    return true;
}

bool Character::replaceMonster(int index, const Monster& monster) {
    if (index < 0 || index >= monsterCount) return false;
    monsters[index] = monster;
    return true;
}

void Character::removeDefeatedMonsters() {
    int newCount = 0;
    std::array<Monster, MAX_MONSTERS> temp;
    for (int i = 0; i < monsterCount; i++) {
        if (monsters[i].isAlive()) {
            temp[newCount++] = monsters[i];
        }
    }
    monsters = temp;
    monsterCount = newCount;
}

void Character::resetAllMonstersHp() {
    for (int i = 0; i < monsterCount; i++) {
        monsters[i].resetHp();
    }
}

void Character::printMonsters() const {
    std::cout << "Karakterens monstre (" << monsterCount << "/" << MAX_MONSTERS << "):\n";
    for (int i = 0; i < monsterCount; i++) {
        std::cout << "  " << (i + 1) << ". ";
        monsters[i].printStats();
    }
}
