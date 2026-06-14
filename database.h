#pragma once

#include <string>
#include <sqlite3.h>
#include "character.h"

class Database {
public:
    Database(const std::string& filename);
    ~Database();

    bool init();

    bool saveCharacter(const Character& character);
    bool loadCharacter(Character& character);

private:
    sqlite3* db;
};