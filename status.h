#pragma once
#include <string>

enum class StatusEffect {
    SPEED_II,           // Angriber altid først
    NONE
};

class Status {
public:
    Status(StatusEffect effect);
    Status();

    StatusEffect getEffect() const;
    std::string getEffectName() const;
    void printInfo() const;

private:
    StatusEffect effect;
};