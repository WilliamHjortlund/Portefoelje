#pragma once
#include <string>
#include <vector>
#include "item.h"

class Monster {
public:
    Monster(const std::string& name, int hp, int strength);
    Monster();

    std::string getName() const;
    int getHp() const;
    int getStrength() const;
    int getBaseStrength() const;
    int getBaseHp() const;
    bool isAlive() const;
    void takeDamage(int damage);
    void resetHp();
    void printStats() const;
    
    void equipItem(const Item& item);
    void clearItems();

private:
    std::string name;
    int hp;
    int maxHp;
    int strength;
    int baseStrength;
    int baseHp;
    std::vector<Item> equippedItems;
    
    void recalculateStats();
};
