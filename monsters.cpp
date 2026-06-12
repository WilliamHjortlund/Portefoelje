#include "monsters.h"
#include <iostream>
#include <algorithm>

Monster::Monster(const std::string& name, int hp, int strength)
    : name(name), hp(hp), maxHp(hp), strength(strength) {}

Monster::Monster()
    : name("Hest"), hp(30), maxHp(30), strength(5) {}

std::string Monster::getName() const { return name; }
int Monster::getHp() const { return hp; }
int Monster::getStrength() const { return strength; }
bool Monster::isAlive() const { return hp > 0; }

void Monster::takeDamage(int damage) {
    hp = std::max(0, hp - damage);
}

void Monster::resetHp() {
    hp = maxHp;
}

void Monster::printStats() const {
    std::cout << "  [" << name << "] HP: " << hp << "/" << maxHp
              << "  Styrke: " << strength << "\n";
}
