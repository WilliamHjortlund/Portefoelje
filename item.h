#pragma once
#include <string>

enum class ItemType {
    STRENGTH_BOOST,     // Øger styrke
    HEALTH_BOOST,       // Øger HP
    DEFENSE_BOOST,      // Øger forsvar
};

class Item {
public:
    Item(const std::string& name, ItemType type, int bonus);
    Item();

    std::string getName() const;
    ItemType getType() const;
    int getBonus() const;
    void printInfo() const;

private:
    std::string name;
    ItemType type;
    int bonus;
};
