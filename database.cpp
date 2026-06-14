#include "database.h"
#include <iostream>

Database::Database(const std::string& filename)
{
    if (sqlite3_open(filename.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Kunne ikke åbne database\n";
        db = nullptr;
    }
}

Database::~Database()
{
    if (db)
        sqlite3_close(db);
}

bool Database::init()
{
    const char* sql =
        "CREATE TABLE IF NOT EXISTS character ("
        "name TEXT PRIMARY KEY);"

        "CREATE TABLE IF NOT EXISTS monster ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "character_name TEXT,"
        "name TEXT,"
        "hp INTEGER,"
        "strength INTEGER);";

    char* errMsg = nullptr;

    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}

bool Database::saveCharacter(const Character& character)
{
    char* errMsg = nullptr;

    std::string deleteSql =
        "DELETE FROM monster WHERE character_name='" +
        character.getName() + "';";

    sqlite3_exec(db, deleteSql.c_str(), nullptr, nullptr, &errMsg);

    std::string insertCharacter =
        "INSERT OR REPLACE INTO character(name) VALUES('" +
        character.getName() + "');";

    sqlite3_exec(db, insertCharacter.c_str(), nullptr, nullptr, &errMsg);

    for (int i = 0; i < character.getMonsterCount(); i++) {
        Monster* monster =
            const_cast<Character&>(character).getMonster(i);

        std::string sql =
            "INSERT INTO monster(character_name,name,hp,strength)"
            " VALUES('" +
            character.getName() + "','" +
            monster->getName() + "'," +
            std::to_string(monster->getHp()) + "," +
            std::to_string(monster->getStrength()) +
            ");";

        sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    }

    return true;
}

bool Database::loadCharacter(Character& character)
{
    std::cout << "Load funktion skal udvides lidt først.\n";
    return true;
}