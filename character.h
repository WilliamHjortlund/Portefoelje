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
    void resetAllMonstersHp();
    void clearMonsters();

    void setMonstersDefeated(int value);
    void setCavesCompleted(int value);
    void setItemsCollected(int value);

    void setName(const std::string& newName);
    void addMonsterDefeat();
    void addCaveCompleted();
    void addItemsCollected(int amount);

    int getMonstersDefeated() const;
    int getCavesCompleted() const;
    int getItemsCollected() const;

    void printStatistics() const;

    void printMonsters() const;

private:
    int monstersDefeated;
    int cavesCompleted;
    int itemsCollected;
    std::string name;
    std::array<Monster, MAX_MONSTERS> monsters;
    int monsterCount;
};
