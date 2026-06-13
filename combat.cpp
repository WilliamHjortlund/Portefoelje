#include "combat.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <random>

void delay(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

bool Combat::fight(Monster& playerMonster, Monster& enemyMonster) {
    std::cout << "\n--- KAMP START ---\n";
    delay(800);
    std::cout << "Dit monster:    ";
    playerMonster.printStats();
    delay(400);
    std::cout << "Fjende monster: ";
    enemyMonster.printStats();
    std::cout << "\n";
    delay(1000);

    bool playerStarts;

    if (playerMonster.hasStatusEffect(StatusEffect::SPEED_II)) {
        playerStarts = true;
        std::cout << playerMonster.getName() << " har Hurtighed II og angriber altid først!\n";
    } else if (enemyMonster.hasStatusEffect(StatusEffect::SPEED_II)) {
        playerStarts = false;
        std::cout << enemyMonster.getName() << " har Hurtighed II og angriber altid først!\n";
    } else {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 1);
        playerStarts = dis(gen) == 0;
        if (playerStarts) {
            std::cout << "Dit monster angriber først!\n";
        } else {
            std::cout << "Fjendens monster angriber først!\n";
        }
    }

    delay(1000);

    while (playerMonster.isAlive() && enemyMonster.isAlive()) {
        if (playerStarts) {
            int dmg = std::max(1, playerMonster.getStrength() - enemyMonster.getDefense());
            enemyMonster.takeDamage(dmg);
            std::cout << playerMonster.getName() << " angriber "
                      << enemyMonster.getName() << " for " << dmg << " skade! "
                      << "(fjende HP: " << enemyMonster.getHp() << ")\n";
            delay(1000);
            if (!enemyMonster.isAlive()) break;

            dmg = std::max(1, enemyMonster.getStrength() - playerMonster.getDefense());
            playerMonster.takeDamage(dmg);
            std::cout << enemyMonster.getName() << " angriber "
                      << playerMonster.getName() << " for " << dmg << " skade! "
                      << "(dit HP: " << playerMonster.getHp() << ")\n";
            delay(1000);
        } else {
            int dmg = std::max(1, enemyMonster.getStrength() - playerMonster.getDefense());
            playerMonster.takeDamage(dmg);
            std::cout << enemyMonster.getName() << " angriber "
                      << playerMonster.getName() << " for " << dmg << " skade! "
                      << "(dit HP: " << playerMonster.getHp() << ")\n";
            delay(1000);
            if (!playerMonster.isAlive()) break;

            dmg = std::max(1, playerMonster.getStrength() - enemyMonster.getDefense());
            enemyMonster.takeDamage(dmg);
            std::cout << playerMonster.getName() << " angriber "
                      << enemyMonster.getName() << " for " << dmg << " skade! "
                      << "(fjende HP: " << enemyMonster.getHp() << ")\n";
            delay(1000);
        }
    }

    std::cout << "\n";
    delay(500);
    if (playerMonster.isAlive()) {
        std::cout << "*** " << playerMonster.getName() << " vandt kampen! ***\n";
        return true;
    } else {
        std::cout << "*** " << playerMonster.getName() << " blev besejret... ***\n";
        return false;
    }
}
