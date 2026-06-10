#include "combat.h"
#include <iostream>
#include <cstdlib>

bool Combat::coinFlip() {
    return (std::rand() % 2) == 0;
}

bool Combat::fight(Monster& playerMonster, Monster& enemyMonster) {
    std::cout << "\n--- KAMP START ---\n";
    std::cout << "Dit monster:    ";
    playerMonster.printStats();
    std::cout << "Fjende monster: ";
    enemyMonster.printStats();
    std::cout << "\n";

    bool playerFirst = coinFlip();
    if (playerFirst) {
        std::cout << "Dit monster angriber foerst!\n";
    } else {
        std::cout << "Fjendemonster angriber foerst!\n";
    }

    while (playerMonster.isAlive() && enemyMonster.isAlive()) {
        if (playerFirst) {
            int dmg = playerMonster.getStrength();
            enemyMonster.takeDamage(dmg);
            std::cout << playerMonster.getName() << " angriber "
                      << enemyMonster.getName() << " for " << dmg << " skade! "
                      << "(fjende HP: " << enemyMonster.getHp() << ")\n";

            if (!enemyMonster.isAlive()) break;

            dmg = enemyMonster.getStrength();
            playerMonster.takeDamage(dmg);
            std::cout << enemyMonster.getName() << " angriber "
                      << playerMonster.getName() << " for " << dmg << " skade! "
                      << "(dit HP: " << playerMonster.getHp() << ")\n";
        } else {
            int dmg = enemyMonster.getStrength();
            playerMonster.takeDamage(dmg);
            std::cout << enemyMonster.getName() << " angriber "
                      << playerMonster.getName() << " for " << dmg << " skade! "
                      << "(dit HP: " << playerMonster.getHp() << ")\n";

            if (!playerMonster.isAlive()) break;

            dmg = playerMonster.getStrength();
            enemyMonster.takeDamage(dmg);
            std::cout << playerMonster.getName() << " angriber "
                      << enemyMonster.getName() << " for " << dmg << " skade! "
                      << "(fjende HP: " << enemyMonster.getHp() << ")\n";
        }
    }

    std::cout << "\n";
    if (playerMonster.isAlive()) {
        std::cout << "*** " << playerMonster.getName() << " vandt kampen! ***\n";
        return true;
    } else {
        std::cout << "*** " << playerMonster.getName() << " blev besejret... ***\n";
        return false;
    }
}