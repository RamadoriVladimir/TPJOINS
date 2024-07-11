#include <GamesManager.h>

GamesManager::GamesManager(std::shared_ptr<SqliteDatabaseHandler> dbHandler) : dbHandler ( dbHandler )
{
    dbHandler->prepareQuery("CREATE TABLE IF NOT EXISTS Games (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)");
    dbHandler->execute();
}

bool GamesManager::addGame(const std::string& name)
{
    dbHandler->prepareQuery("INSERT INTO Games(name) VALUES(?)");
    dbHandler->addParameter(1, name);
    dbHandler->execute();
    return !dbHandler->getErrorStatus();
}

bool GamesManager::removeGame(int id)
{
    dbHandler->prepareQuery("DELETE FROM Games WHERE id = ?");
    dbHandler->addParameter(1, std::to_string(id));
    dbHandler->execute();
    return !dbHandler->getErrorStatus();
}

bool GamesManager::updateGame(int id, const std::string& name)
{
    dbHandler->prepareQuery("UPDATE Games SET name = ? WHERE id = ?");
    dbHandler->addParameter(1, name);
    dbHandler->addParameter(2, std::to_string(id));
    dbHandler->execute();
    return !dbHandler->getErrorStatus();
}

std::vector<Row> GamesManager::listGames() 
{
    dbHandler->prepareQuery("SELECT * FROM Games");
    return dbHandler->fetchAll();
}
