#include <UserManager.h>

UserManager::UserManager(std::shared_ptr<SqliteDatabaseHandler> dbHandler) : dbHandler ( dbHandler )
{
    dbHandler->prepareQuery("CREATE TABLE IF NOT EXISTS Users (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)");
    dbHandler->execute();
}

bool UserManager::addUser(const std::string& name)
{
    dbHandler->prepareQuery("INSERT INTO Users(name) VALUES(?)");
    dbHandler->addParameter(1, name);
    dbHandler->execute();
    return !dbHandler->getErrorStatus();
}

bool UserManager::removeUser(int id)
{   
    dbHandler->prepareQuery("DELETE FROM Users WHERE id = ?");
    dbHandler->addParameter(1, std::to_string(id));
    dbHandler->execute();
    return !dbHandler->getErrorStatus();
}

bool UserManager::updateUser(int id, const std::string& name)
{
    dbHandler->prepareQuery("UPDATE Users SET name = ? WHERE id = ?");
    dbHandler->addParameter(1, name);
    dbHandler->addParameter(2, std::to_string(id));
    dbHandler->execute();
    return !dbHandler->getErrorStatus();
}

std::vector<Row> UserManager::listUsers()
{
    dbHandler->prepareQuery("SELECT * FROM Users");
    return dbHandler->fetchAll();
}