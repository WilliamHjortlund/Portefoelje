#include "item.h"
#include <iostream>

Item::Item(const std::string& name, ItemType type, int bonus)
    : name(name), type(type), bonus(bonus) {}

Item::Item()
    : name("Ukendt Item"), type(ItemType::STRENGTH_BOOST), bonus(1) {}

std::string Item::getName() const { return name; }
ItemType Item::getType() const { return type; }
int Item::getBonus() const { return bonus; }

void Item::printInfo() const {
    std::string typeStr;
    switch (type) {
        case ItemType::STRENGTH_BOOST:
            typeStr = "Styrke +";
            break;
        case ItemType::HEALTH_BOOST:
            typeStr = "HP +";
            break;
        case ItemType::DEFENSE_BOOST:
            typeStr = "Forsvar +";
            break;
    }
    std::cout << name << " (" << typeStr << bonus << ")\n";
}
