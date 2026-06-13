#include "menu.h"
#include "combat.h"
#include <iostream>
#include <limits>
#include <vector>
#include <cstdlib>
#include <ctime>

void Menu::printSeparator() {
    std::cout << "============================================\n";
}

int Menu::readInt(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= min && value <= max) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ugyldigt valg. Indtast et tal mellem " << min << " og " << max << ".\n";
    }
}

std::string Menu::readLine(const std::string& prompt) {
    std::string line;
    std::cout << prompt;
    std::getline(std::cin, line);
    return line;
}

std::vector<Monster> Menu::buildEnemyPool() {
    return {
        Monster("Slime",  15,  3),
        Monster("Goblin", 20,  6),
        Monster("Troll",  40, 10),
        Monster("Drage",  60, 15),
    };
}

std::vector<Item> Menu::buildItemPool() {
    return {
        Item("Sværd",      ItemType::STRENGTH_BOOST, 5),
        Item("Energidrik", ItemType::HEALTH_BOOST,   10),
        Item("Skjold",     ItemType::DEFENSE_BOOST,  3),
        Item("Løbesko",    ItemType::STATUS_EFFECT,  StatusEffect::SPEED_II),
    };
}

void Menu::run() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    showMainMenu();
}

void Menu::showMainMenu() {
    while (true) {
        printSeparator();
        std::cout << "       MONSTER KAMP SPIL - HOVEDMENU\n";
        printSeparator();
        std::cout << "  1. Opret ny karakter og spil\n";
        std::cout << "  2. Afslut spillet\n";
        printSeparator();

        int choice = readInt("Valg: ", 1, 2);
        if (choice == 1) {
            createCharacter();
        } else {
            std::cout << "Farvel!\n";
            return;
        }
    }
}

void Menu::createCharacter() {
    std::cout << "\n";
    printSeparator();
    std::cout << "           OPRET NY KARAKTER\n";
    printSeparator();
    std::string name = readLine("Karakterens navn: ");
    if (name.empty()) name = "Ukendt Helt";

    Character character(name);

    std::cout << "\nVelkommen, " << character.getName() << "!\n";
    std::cout << "Du starter med disse monstre:\n";
    character.printMonsters();

    adventureLoop(character);
}

void Menu::startAdventure(Character& character) {
    adventureLoop(character);
}

void Menu::adventureLoop(Character& character) {
    while (true) {
        if (!character.hasAliveMonsters()) {
            std::cout << "\nAlle dine monstre er besejret! Du vender tilbage til hovedmenuen.\n";
            return;
        }

        printSeparator();
        std::cout << "  EVENTYR - Karakter: " << character.getName() << "\n";
        printSeparator();
        character.printMonsters();
        std::cout << "\n  1. Kæmp mod en fjende\n";
        std::cout << "  2. Giv item til monster\n";
        std::cout << "  3. Gå til grotte\n";
        std::cout << "  4. Forlad til hovedmenu\n";
        printSeparator();

        int choice = readInt("Valg: ", 1, 4);
        if (choice == 4) {
            std::cout << "Du vender tilbage til hovedmenuen.\n";
            return;
        }

        if (choice == 2) {
            giveItemToMonster(character);
            continue;
        }

        if (choice == 3) {
            caveAdventure(character);
            continue;
        }

        Monster enemy = chooseFightMonster();

        bool battleWon = false;
        bool isFirstMonster = true;

        while (!battleWon && character.hasAliveMonsters()) {
            if (isFirstMonster) {
                std::cout << "\nVælg dit monster til kampen mod " << enemy.getName() << ":\n";
                isFirstMonster = false;
            } else {
                std::cout << "\nVælg næste monster til kampen mod " << enemy.getName() << ":\n";
            }

            character.printMonsters();
            int monsterChoice = readInt("Valg (nummer): ", 1, character.getMonsterCount());
            Monster* myMonster = character.getMonster(monsterChoice - 1);

            if (!myMonster->isAlive()) {
                std::cout << "Dit monster " << myMonster->getName() << " er allerede besejret!\n";
                continue;
            }

            bool won = Combat::fight(*myMonster, enemy);

            if (won) {
                std::cout << "\nDu besejrede " << enemy.getName() << "!\n";
                enemy.resetHp();
                offerCapturedMonster(character, enemy);
                battleWon = true;
            } else {
                std::cout << "\nDit monster " << myMonster->getName() << " er ude af kamp.\n";

                int aliveCount = 0;
                for (int i = 0; i < character.getMonsterCount(); i++) {
                    if (character.getMonster(i)->isAlive()) aliveCount++;
                }

                if (aliveCount > 0) {
                    std::cout << "Du har " << aliveCount << " levende monster(e) tilbage.\n";
                    std::cout << "Fjenden er stadig i live med " << enemy.getHp() << " HP.\n";
                }
            }
        }

        character.resetAllMonstersHp();
        character.removeDefeatedMonsters();
    }
}

Monster Menu::chooseFightMonster() {
    std::vector<Monster> pool = buildEnemyPool();

    std::cout << "\nVælg hvilken fjende du vil kæmpe mod:\n";
    for (int i = 0; i < (int)pool.size(); i++) {
        std::cout << "  " << (i + 1) << ". ";
        pool[i].printStats();
    }

    int choice = readInt("Valg: ", 1, (int)pool.size());
    return pool[choice - 1];
}

bool Menu::offerCapturedMonster(Character& character, const Monster& captured) {
    std::cout << "\nVil du tilføje " << captured.getName()
              << " til dit hold? (1=Ja / 2=Nej): ";
    int choice = readInt("", 1, 2);
    if (choice == 2) return false;

    if (character.getMonsterCount() < MAX_MONSTERS) {
        character.addMonster(captured);
        std::cout << captured.getName() << " er tilføjet til dit hold!\n";
    } else {
        std::cout << "Dit hold er fuldt (" << MAX_MONSTERS << "/" << MAX_MONSTERS << ").\n";
        std::cout << "Vil du udskifte et monster? (1=Ja / 2=Nej): ";
        int replace = readInt("", 1, 2);
        if (replace == 2) return false;

        std::cout << "\nVælg hvilket monster du vil udskifte:\n";
        character.printMonsters();
        int idx = readInt("Nummer: ", 1, character.getMonsterCount());
        character.replaceMonster(idx - 1, captured);
        std::cout << "Monster udskiftet med " << captured.getName() << "!\n";
    }
    return true;
}

void Menu::equipMonsterWithItems(Monster& monster) {
    std::vector<Item> items = buildItemPool();

    printSeparator();
    std::cout << "Vælg powerups til " << monster.getName() << ":\n";
    printSeparator();

    while (true) {
        std::cout << "\nTilgængelige items:\n";
        for (int i = 0; i < (int)items.size(); i++) {
            std::cout << "  " << (i + 1) << ". ";
            items[i].printInfo();
        }
        std::cout << "  " << (items.size() + 1) << ". Start kampen\n";
        printSeparator();

        int choice = readInt("Valg: ", 1, (int)items.size() + 1);
        if (choice == (int)items.size() + 1) break;

        monster.equipItem(items[choice - 1]);
        std::cout << items[choice - 1].getName() << " er givet til " << monster.getName() << "!\n";
    }
}

void Menu::giveItemToMonster(Character& character) {
    std::cout << "\nVælg hvilket monster skal få et item:\n";
    character.printMonsters();
    int monsterChoice = readInt("Valg (nummer): ", 1, character.getMonsterCount());
    Monster* monster = character.getMonster(monsterChoice - 1);

    if (monster == nullptr) {
        std::cout << "Ugyldigt valg!\n";
        return;
    }

    equipMonsterWithItems(*monster);
}

void Menu::caveAdventure(Character& character) {
    if (!character.hasAliveMonsters()) {
        std::cout << "\nDu har ingen levende monstre! Gå tilbage til hovedmenuen.\n";
        return;
    }

    Caves::printCaveInfo();

    std::vector<Monster> enemies = Caves::generateCaveGroup(character);
    int totalEnemies = (int)enemies.size();

    for (int i = 0; i < character.getMonsterCount(); i++) {
        Monster* monster = character.getMonster(i);
        if (monster != nullptr) monster->resetHp();
    }

    for (int enemyIndex = 0; enemyIndex < totalEnemies; enemyIndex++) {
        Monster& caveMonster = enemies[enemyIndex];

        std::cout << "\n--- Fjende " << (enemyIndex + 1) << "/" << totalEnemies
                  << ": " << caveMonster.getName() << " ---\n";
        delay(800);

        if (!character.hasAliveMonsters()) {
            std::cout << "\nAlle dine monstre er besejret! Du måtte flygte fra grotten.\n";
            return;
        }

        bool enemyDefeated = false;
        bool isFirstMonster = true;

        while (!enemyDefeated && character.hasAliveMonsters()) {
            if (isFirstMonster) {
                std::cout << "\nVælg dit monster til kampen mod " << caveMonster.getName() << ":\n";
                isFirstMonster = false;
            } else {
                std::cout << "\nVælg næste monster til kampen mod " << caveMonster.getName() << ":\n";
            }

            character.printMonsters();
            int monsterChoice = readInt("Valg (nummer): ", 1, character.getMonsterCount());
            Monster* myMonster = character.getMonster(monsterChoice - 1);

            if (myMonster == nullptr || !myMonster->isAlive()) {
                std::cout << "Dit monster er ikke i live!\n";
                continue;
            }

            bool won = Combat::fight(*myMonster, caveMonster);

            if (won) {
                std::cout << "\n*** " << caveMonster.getName() << " er besejret! ***\n";
                enemyDefeated = true;
            } else {
                std::cout << "\n*** Dit monster " << myMonster->getName() << " blev besejret. ***\n";

                int aliveCount = 0;
                for (int i = 0; i < character.getMonsterCount(); i++) {
                    if (character.getMonster(i)->isAlive()) aliveCount++;
                }

                if (aliveCount > 0) {
                    std::cout << "Du har " << aliveCount << " levende monster(e) tilbage.\n";
                    std::cout << "Fjenden er stadig i live med " << caveMonster.getHp() << " HP.\n";
                    std::cout << "Vil du sende et nyt monster mod " << caveMonster.getName() << "? (1=Ja / 2=Nej): ";
                    int choice = readInt("", 1, 2);
                    if (choice == 2) {
                        std::cout << "Du flygtede fra grotten.\n";
                        return;
                    }
                }
            }
        }

        if (!enemyDefeated) {
            std::cout << "\nAlle dine monstre er besejret! Du måtte flygte fra grotten.\n";
            return;
        }

        if (enemyIndex < totalEnemies - 1) {
            std::cout << "\nDu fortsætter dybere ind i grotten...\n";
            delay(1000);
        }
    }

    std::cout << "\n*** Du besejrede alle monstre i grotten! ***\n";
    std::vector<Item> rewards = Caves::getItemReward();
    handleCaveReward(character, rewards);
}

void Menu::handleCaveReward(Character& character, const std::vector<Item>& rewards) {
    printSeparator();
    std::cout << "\nDu fik følgende items fra grottekampen:\n";
    for (const auto& item : rewards) {
        std::cout << "  - ";
        item.printInfo();
    }
    printSeparator();

    std::cout << "\nVil du give disse items til dine monstre? (1=Ja / 2=Nej): ";
    int choice = readInt("", 1, 2);

    if (choice == 2) {
        std::cout << "Du forkastede items og fortsatte.\n";
        return;
    }

    for (const auto& item : rewards) {
        std::cout << "\nVælg hvilket monster skal få " << item.getName() << ":\n";
        character.printMonsters();
        int monsterChoice = readInt("Valg (nummer): ", 1, character.getMonsterCount());
        Monster* monster = character.getMonster(monsterChoice - 1);

        if (monster != nullptr) {
            monster->equipItem(item);
            std::cout << item.getName() << " er givet til " << monster->getName() << "!\n";
        }
    }
}