#include "combat.h"
#include <iostream>
#include <thread>
#include <chrono>

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

    std::cout << "Dit monster angriber først!\n";
    delay(1000);

    while (playerMonster.isAlive() && enemyMonster.isAlive()) {
        int dmg = playerMonster.getStrength();
        enemyMonster.takeDamage(dmg);
        std::cout << playerMonster.getName() << " angriber "
                  << enemyMonster.getName() << " for " << dmg << " skade! "
                  << "(fjende HP: " << enemyMonster.getHp() << ")\n";
        delay(1000);

        if (!enemyMonster.isAlive()) break;

        dmg = enemyMonster.getStrength();
        playerMonster.takeDamage(dmg);
        std::cout << enemyMonster.getName() << " angriber "
                  << playerMonster.getName() << " for " << dmg << " skade! "
                  << "(dit HP: " << playerMonster.getHp() << ")\n";
        delay(1000);
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