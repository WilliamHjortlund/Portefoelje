#include "item.h"
#include <iostream>

Item::Item(const std::string& name, ItemType type, int bonus)
    : name(name), type(type), bonus(bonus), statusEffect(StatusEffect::NONE) {}

Item::Item(const std::string& name, ItemType type, StatusEffect effect)
    : name(name), type(type), bonus(0), statusEffect(effect) {}

Item::Item()
    : name("Ukendt Item"), type(ItemType::STRENGTH_BOOST), bonus(1), statusEffect(StatusEffect::NONE) {}

std::string Item::getName() const { return name; }
ItemType Item::getType() const { return type; }
int Item::getBonus() const { return bonus; }
StatusEffect Item::getStatusEffect() const { return statusEffect; }

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
        case ItemType::STATUS_EFFECT: {
            Status status(statusEffect);
            std::cout << name << " (Effekt: ";
            status.printInfo();
            std::cout << ")\n";
            return;
        }
    }
    std::cout << name << " (" << typeStr << bonus << ")\n";
}