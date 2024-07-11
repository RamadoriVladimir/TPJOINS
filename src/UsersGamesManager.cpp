#include <UsersGamesManager.h>
UsersGamesManager::UsersGamesManager(std::shared_ptr<SqliteDatabaseHandler> dbHandler) : dbHandler ( dbHandler )
{
    dbHandler->prepareQuery("CREATE TABLE IF NOT EXISTS Users_Games (user_id INTEGER, game_id INTEGER)");
    dbHandler->execute();
}

bool UsersGamesManager::addAssociation(int userId, int gameId)
{
    dbHandler->prepareQuery("INSERT INTO Users_Games(user_id, game_id) VALUES(?, ?)");
    dbHandler->addParameter(1, std::to_string(userId));
    dbHandler->addParameter(2, std::to_string(gameId));
    dbHandler->execute();
    return !dbHandler->getErrorStatus();
}

bool UsersGamesManager::removeAssociation(int userId, int gameId)
{
    dbHandler->prepareQuery("DELETE FROM Users_Games WHERE user_id = ? AND game_id = ?");
    dbHandler->addParameter(1, std::to_string(userId));
    dbHandler->addParameter(2, std::to_string(gameId));
    dbHandler->execute();
    return !dbHandler->getErrorStatus();
}

std::vector<Row> UsersGamesManager::innerJoin()
{
    dbHandler->prepareQuery("SELECT Users.name AS user_name, Games.name AS game_name "
                            "FROM Users "
                            "INNER JOIN Users_Games ON Users.id = Users_Games.user_id "
                            "INNER JOIN Games ON Games.id = Users_Games.game_id");
    return dbHandler->fetchAll();
}

std::vector<Row> UsersGamesManager::leftJoin()
{
    dbHandler->prepareQuery("SELECT Users.name AS user_name, Games.name AS game_name "
                            "FROM Users "
                            "LEFT JOIN Users_Games ON Users.id = Users_Games.user_id "
                            "LEFT JOIN Games ON Games.id = Users_Games.game_id");
    return dbHandler->fetchAll();
}

std::vector<Row> UsersGamesManager::rightJoin()
{
    dbHandler->prepareQuery("SELECT Users.name AS user_name, Games.name AS game_name "
                            "FROM Games "
                            "LEFT JOIN Users_Games ON Games.id = Users_Games.game_id "
                            "LEFT JOIN Users ON Users.id = Users_Games.user_id");
    return dbHandler->fetchAll();
}

std::vector<Row> UsersGamesManager::outerJoin()
{
    dbHandler->prepareQuery("SELECT Users.name AS user_name, Games.name AS game_name "
                            "FROM Users "
                            "FULL OUTER JOIN Users_Games ON Users.id = Users_Games.user_id "
                            "FULL OUTER JOIN Games ON Games.id = Users_Games.game_id");
    return dbHandler->fetchAll();
}

std::vector<Row> UsersGamesManager::findUsersByGame(int gameId)
{
    dbHandler->prepareQuery("SELECT Users.* FROM Users "
                            "INNER JOIN Users_Games ON Users.id = Users_Games.user_id "
                            "WHERE Users_Games.game_id = ?");
    dbHandler->addParameter(1, std::to_string(gameId));
    return dbHandler->fetchAll();
}

std::vector<Row> UsersGamesManager::findGamesByUser(int userId)
{
    dbHandler->prepareQuery("SELECT Games.* FROM Games "
                            "INNER JOIN Users_Games ON Games.id = Users_Games.game_id "
                            "WHERE Users_Games.user_id = ?");
    dbHandler->addParameter(1, std::to_string(userId));
    return dbHandler->fetchAll();
}
