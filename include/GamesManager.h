#pragma once

#include <string>
#include <vector>
#include <memory>
#include <SqliteDatabaseHandler.h>

class GamesManager
{
    private:
        std::shared_ptr<SqliteDatabaseHandler> dbHandler;
    public:
        GamesManager(std::shared_ptr<SqliteDatabaseHandler> dbHandler);
        bool addGame(const std::string& name);
        bool removeGame(int id);
        bool updateGame(int id, const std::string& name);
        std::vector<Row> listGames();
};
