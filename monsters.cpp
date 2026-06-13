#include "monsters.h"
#include "item.h"
#include <iostream>
#include <algorithm>

Monster::Monster(const std::string& name, int hp, int strength)
    : name(name), hp(hp), maxHp(hp), strength(strength), baseStrength(strength), baseHp(hp) {}

Monster::Monster()
    : name("Hest"), hp(30), maxHp(30), strength(5), baseStrength(5), baseHp(30) {}

std::string Monster::getName() const { return name; }
int Monster::getHp() const { return hp; }
int Monster::getStrength() const { return strength; }
int Monster::getBaseStrength() const { return baseStrength; }
int Monster::getBaseHp() const { return baseHp; }
bool Monster::isAlive() const { return hp > 0; }

void Monster::takeDamage(int damage) {
    hp = std::max(0, hp - damage);
}

void Monster::resetHp() {
    hp = maxHp;
}

void Monster::printStats() const {
    std::string itemInfo = "";
    if (!equippedItems.empty()) {
        itemInfo = " [";
        for (int i = 0; i < (int)equippedItems.size(); i++) {
            if (i > 0) itemInfo += ", ";
            itemInfo += equippedItems[i].getName();
        }
        itemInfo += "]";
    }
    std::cout << "  [" << name << "] HP: " << hp << "/" << maxHp
              << "  Styrke: " << strength << itemInfo << "\n";
}

void Monster::equipItem(const Item& item) {
    equippedItems.push_back(item);
    recalculateStats();
}

void Monster::clearItems() {
    equippedItems.clear();
    strength = baseStrength;
    maxHp = baseHp;
    hp = maxHp;
}

void Monster::recalculateStats() {
    strength = baseStrength;
    maxHp = baseHp;
    
    for (const auto& item : equippedItems) {
        if (item.getType() == ItemType::STRENGTH_BOOST) {
            strength += item.getBonus();
        } else if (item.getType() == ItemType::HEALTH_BOOST) {
            maxHp += item.getBonus();
        }
    }
    
    hp = maxHp;
}
