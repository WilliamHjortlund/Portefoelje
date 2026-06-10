#pragma once
#include "monsters.h"
#include <string>
#include <array>

constexpr int MAX_MONSTERS = 4;

class Character {
public:
    Character(const std::string& name);

    std::string getName() const;
    int getMonsterCount() const;
    Monster* getMonster(int index);
    bool hasAliveMonsters() const;

    bool addMonster(const Monster& monster);
    bool replaceMonster(int index, const Monster& monster);
    void removeDefeatedMonsters();

    void printMonsters() const;

private:
    std::string name;
    std::array<Monster, MAX_MONSTERS> monsters;
    int monsterCount;
};