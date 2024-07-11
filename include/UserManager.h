#pragma once

#include <string>
#include <vector>
#include <memory>
#include <SqliteDatabaseHandler.h>

class UserManager
{
    private:
        std::shared_ptr<SqliteDatabaseHandler> dbHandler;

    public:
        UserManager(std::shared_ptr<SqliteDatabaseHandler> dbHandler);
        bool addUser(const std::string& name);
        bool removeUser(int id);
        bool updateUser(int id, const std::string& name);
        std::vector<Row> listUsers();
};  
