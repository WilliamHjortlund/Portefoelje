#include "database.h"
#include <iostream>

static Item createItemFromName(const std::string& name)
{
    if (name == "Sværd")
        return Item("Sværd", ItemType::STRENGTH_BOOST, 5);

    if (name == "Energidrik")
        return Item("Energidrik", ItemType::HEALTH_BOOST, 10);

    if (name == "Skjold")
        return Item("Skjold", ItemType::DEFENSE_BOOST, 3);

    if (name == "Løbesko")
        return Item("Løbesko", ItemType::STATUS_EFFECT,
                    StatusEffect::SPEED_II);

    return Item();
}

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
        "strength INTEGER);"

        "CREATE TABLE IF NOT EXISTS monster_item ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "character_name TEXT,"
        "monster_name TEXT,"
        "item_name TEXT);";

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

    std::string deleteItemsSql =
        "DELETE FROM monster_item WHERE character_name='" +
        character.getName() + "';";
    
    sqlite3_exec(db, deleteItemsSql.c_str(), nullptr, nullptr, &errMsg);

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
    
        for (const auto& item : monster->getItems())
        {
            std::string itemSql =
                "INSERT INTO monster_item(character_name,monster_name,item_name)"
                " VALUES('" +
                character.getName() + "','" +
                monster->getName() + "','" +
                item.getName() +
                "');";

            sqlite3_exec(db, itemSql.c_str(), nullptr, nullptr, &errMsg);
        }
    }
    return true;
}

bool Database::loadCharacter(Character& character)
{
    character.clearMonsters();

    std::string sql =
        "SELECT name, hp, strength "
        "FROM monster "
        "WHERE character_name='" +
        character.getName() + "';";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }

    bool foundAny = false;

    while (sqlite3_step(stmt) == SQLITE_ROW) {

        std::string monsterName =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));

        int hp = sqlite3_column_int(stmt, 1);
        int strength = sqlite3_column_int(stmt, 2);

        Monster monster(monsterName, hp, strength);

        character.addMonster(monster);

        foundAny = true;
    }

    sqlite3_finalize(stmt);

    // LOAD ITEMS
    std::string itemSql =
        "SELECT monster_name, item_name "
        "FROM monster_item "
        "WHERE character_name='" +
        character.getName() + "';";

    sqlite3_stmt* itemStmt = nullptr;

    if (sqlite3_prepare_v2(db, itemSql.c_str(), -1,
                           &itemStmt, nullptr) == SQLITE_OK)
    {
        while (sqlite3_step(itemStmt) == SQLITE_ROW)
        {
            std::string monsterName =
                reinterpret_cast<const char*>(
                    sqlite3_column_text(itemStmt, 0));

            std::string itemName =
                reinterpret_cast<const char*>(
                    sqlite3_column_text(itemStmt, 1));

            Item item = createItemFromName(itemName);

            for (int i = 0; i < character.getMonsterCount(); i++)
            {
                Monster* monster = character.getMonster(i);

                if (monster != nullptr &&
                    monster->getName() == monsterName)
                {
                    monster->equipItem(item);
                    break;
                }
            }
        }

        sqlite3_finalize(itemStmt);
    }

    return foundAny;
}

std::vector<std::string> Database::getCharacterNames()
{
    std::vector<std::string> names;

    const char* sql =
        "SELECT name FROM character ORDER BY name;";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            names.push_back(
                reinterpret_cast<const char*>(
                    sqlite3_column_text(stmt, 0)
                )
            );
        }
    }

    sqlite3_finalize(stmt);

    return names;
}