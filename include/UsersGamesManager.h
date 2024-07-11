#pragma once

#include <string>
#include <vector>
#include <memory>
#include <SqliteDatabaseHandler.h>

class UsersGamesManager
{
    private:
        std::shared_ptr<SqliteDatabaseHandler> dbHandler;
    public:
    UsersGamesManager(std::shared_ptr<SqliteDatabaseHandler> dbHandler);
    bool addAssociation(int userId, int gameId);
    bool removeAssociation(int userId, int gameId);
    std::vector<Row> innerJoin();
    std::vector<Row> leftJoin();
    std::vector<Row> rightJoin();
    std::vector<Row> outerJoin();
    std::vector<Row> findUsersByGame(int gameId);
    std::vector<Row> findGamesByUser(int userId);    
};