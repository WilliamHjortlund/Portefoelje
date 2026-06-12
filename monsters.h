#pragma once
#include <string>

class Monster {
public:
    Monster(const std::string& name, int hp, int strength);
    Monster();

    std::string getName() const;
    int getHp() const;
    int getStrength() const;
    bool isAlive() const;
    void takeDamage(int damage);
    void resetHp();
    void printStats() const;

private:
    std::string name;
    int hp;
    int maxHp;
    int strength;
};
