#include "status.h"
#include <iostream>

Status::Status(StatusEffect effect)
    : effect(effect) {}

Status::Status()
    : effect(StatusEffect::NONE) {}

StatusEffect Status::getEffect() const { return effect; }

std::string Status::getEffectName() const {
    switch (effect) {
        case StatusEffect::SPEED_II:
            return "Hurtighed II";
        case StatusEffect::NONE:
            return "Ingen effekt";
        default:
            return "Ukendt";
    }
}

void Status::printInfo() const {
    std::cout << getEffectName();
}