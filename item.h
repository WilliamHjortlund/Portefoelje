#pragma once
#include <string>
#include "status.h"

enum class ItemType {
    STRENGTH_BOOST,     // Øger styrke
    HEALTH_BOOST,       // Øger HP
    DEFENSE_BOOST,      // Øger forsvar
    STATUS_EFFECT,      // Giver statuseffekt
};

class Item {
public:
    Item(const std::string& name, ItemType type, int bonus);
    Item(const std::string& name, ItemType type, StatusEffect effect);
    Item();

    std::string getName() const;
    ItemType getType() const;
    int getBonus() const;
    StatusEffect getStatusEffect() const;
    void printInfo() const;

private:
    std::string name;
    ItemType type;
    int bonus;
    StatusEffect statusEffect;
};
