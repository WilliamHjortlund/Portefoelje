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
        Monster("Slime",     15,  3),
        Monster("Goblin",    20,  6),
        Monster("Troll",     40, 10),
        Monster("Drage",     60, 15),
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

        character.removeDefeatedMonsters();

        printSeparator();
        std::cout << "  EVENTYR - Karakter: " << character.getName() << "\n";
        printSeparator();
        character.printMonsters();
        std::cout << "\n  1. Kæmp mod en fjende\n";
        std::cout << "  2. Forlad til hovedmenu\n";
        printSeparator();

        int choice = readInt("Valg: ", 1, 2);
        if (choice == 2) {
            std::cout << "Du vender tilbage til hovedmenuen.\n";
            return;
        }

        Monster enemy = chooseFightMonster();

        std::cout << "\nVælg dit monster til kampen:\n";
        character.printMonsters();
        int monsterChoice = readInt("Valg (nummer): ", 1, character.getMonsterCount());
        Monster* myMonster = character.getMonster(monsterChoice - 1);

        bool won = Combat::fight(*myMonster, enemy);

        if (won) {
            std::cout << "\nDu besejrede " << enemy.getName() << "!\n";
            enemy.resetHp();
            offerCapturedMonster(character, enemy);
        } else {
            std::cout << "\nDit monster " << myMonster->getName() << " er ude af kamp.\n";
        }
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