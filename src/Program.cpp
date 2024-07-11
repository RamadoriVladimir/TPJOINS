#include <Program.h>

Program::Program(std::shared_ptr<SqliteDatabaseHandler> dbHandler) : dbHandler (dbHandler)
{
    gamesManager = std::make_unique<GamesManager>(dbHandler);
    userManager = std::make_unique<UserManager>(dbHandler);
    usersGamesManager = std::make_unique<UsersGamesManager>(dbHandler);
}

void Program::run()
{
    bool exit = false;
    while(!exit)
    {
        MainMenu();
        int choice;
        std::cin >> choice;
        switch (choice) { 
            case 1:
                UserMenu();
                break;
            case 2:
                GameMenu();
                break;
            case 3:
                AssociationMenu();
                break;
            case 4:
                JoinMenu();
                break;
            case 5:
                exit = true;
                break;
            default:
                std::cout << "Invalid choice. Try again." << std::endl;
                break;
        }
    }
}

void Program::MainMenu()
{
    std::cout << "Main Menu:" << std::endl;
    std::cout << "1. User Management" << std::endl;
    std::cout << "2. Game Management" << std::endl;
    std::cout << "3. Association Management" << std::endl;
    std::cout << "4. Join Operations" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

void Program::UserMenu()
{
    bool back = false;
    while (!back) {
        std::cout << "\nUser Management Menu:" << std::endl;
        std::cout << "1. Add User" << std::endl;
        std::cout << "2. Remove User" << std::endl;
        std::cout << "3. Update User" << std::endl;
        std::cout << "4. List Users" << std::endl;
        std::cout << "5. Return to Main Menu" << std::endl;
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1: {
                std::string name;
                std::cout << "Enter user name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                userManager->addUser(name);
                break;
            }
            case 2: {
                int id;
                std::cout << "Enter user ID to remove: ";
                std::cin >> id;
                userManager->removeUser(id);
                break;
            }
            case 3: {
                int id;
                std::string name;
                std::cout << "Enter user ID to update: ";
                std::cin >> id;
                std::cout << "Enter new name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                userManager->updateUser(id, name);
                break;
            }
            case 4: {
                std::vector<Row> users = userManager->listUsers();
                std::cout << "\nList of Users:" << std::endl;
                for (const auto& user : users) {
                    std::cout << "ID: " << user.at("id") << ", Name: " << user.at("name") << std::endl;
                }
                break;
            }
            case 5:
                back = true;
                break;
            default:
                std::cout << "Invalid choice. Try again." << std::endl;
                break;
        }
    }
    BackToMenu();
}

void Program::GameMenu()
{
    bool back = false;
    while (!back) {
        std::cout << "\nGame Management Menu:" << std::endl;
        std::cout << "1. Add Game" << std::endl;
        std::cout << "2. Remove Game" << std::endl;
        std::cout << "3. Update Game" << std::endl;
        std::cout << "4. List Games" << std::endl;
        std::cout << "5. Return to Main Menu" << std::endl;
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1: {
                std::string name;
                double price;
                std::cout << "Enter game name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Enter game price: ";
                std::cin >> price;
                gamesManager->addGame(name);
                break;
            }
            case 2: {
                int id;
                std::cout << "Enter game ID to remove: ";
                std::cin >> id;
                gamesManager->removeGame(id);
                break;
            }
            case 3: {
                int id;
                std::string name;
                double price;
                std::cout << "Enter game ID to update: ";
                std::cin >> id;
                std::cout << "Enter new name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Enter new price: ";
                std::cin >> price;
                gamesManager->updateGame(id, name);
                break;
            }
            case 4: {
                std::vector<Row> games = gamesManager->listGames();
                std::cout << "\nList of Games:" << std::endl;
                for (const auto& game : games) {
                    std::cout << "ID: " << game.at("id") << ", Name: " << game.at("name") << std::endl;
                }
                break;
            }
            case 5:
                back = true;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }
    BackToMenu();
}

void Program::AssociationMenu()
{
    bool back = false;
    while (!back) {
        std::cout << "\nAssociation Management Menu:" << std::endl;
        std::cout << "1. Add Association (User to Game)" << std::endl;
        std::cout << "2. Remove Association (User from Game)" << std::endl;
        std::cout << "3. Return to Main Menu" << std::endl;
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1: {
                int userId, gameId;
                std::cout << "Enter user ID: ";
                std::cin >> userId;
                std::cout << "Enter game ID: ";
                std::cin >> gameId;
                usersGamesManager->addAssociation(userId, gameId);
                break;
            }
            case 2: {
                int userId, gameId;
                std::cout << "Enter user ID: ";
                std::cin >> userId;
                std::cout << "Enter game ID: ";
                std::cin >> gameId;
                usersGamesManager->removeAssociation(userId, gameId);
                break;
            }
            case 3:
                back = true;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }
    BackToMenu();
}

void Program::JoinMenu()
{
    bool back = false;
    while (!back) {
        std::cout << "\nJoin Operations Menu:" << std::endl;
        std::cout << "1. Perform INNER JOIN (Users and Games)" << std::endl;
        std::cout << "2. Perform LEFT JOIN (Users and Games)" << std::endl;
        std::cout << "3. Perform RIGHT JOIN (Users and Games)" << std::endl;
        std::cout << "4. Perform OUTER JOIN (Users and Games)" << std::endl;
        std::cout << "5. Return to Main Menu" << std::endl;
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1: {
                std::vector<Row> result = usersGamesManager->innerJoin();
                std::cout << "\nINNER JOIN Results:" << std::endl;
                for (const auto& row : result) {
                    std::cout << "User: " << row.at("user_name") << ", Game: " << row.at("game_name") << std::endl;
                }
                break;
            }
            case 2: {
                std::vector<Row> result = usersGamesManager->leftJoin();
                std::cout << "\nLEFT JOIN Results:" << std::endl;
                for (const auto& row : result) {
                    std::cout << "User: " << row.at("user_name") << ", Game: " << row.at("game_name") << std::endl;
                }
                break;
            }
            case 3: {
                std::vector<Row> result = usersGamesManager->rightJoin();
                std::cout << "\nRIGHT JOIN Results:" << std::endl;
                for (const auto& row : result) {
                    std::cout << "User: " << row.at("user_name") << ", Game: " << row.at("game_name") << std::endl;
                }
                break;
            }
            case 4: {
                std::vector<Row> result = usersGamesManager->outerJoin();
                std::cout << "\nOUTER JOIN Results:" << std::endl;
                for (const auto& row : result) {
                    std::cout << "User: " << row.at("user_name") << ", Game: " << row.at("game_name") << std::endl;
                }
                break;
            }
            case 5:
                back = true;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }
    BackToMenu();
}

void Program::BackToMenu()
{
    ClearScreen();
    std::cout << "\nReturning to Main Menu..." << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
}

void Program::ClearScreen()
{
    #ifdef _WIN32
        std::system("cls"); 
    #else
        std::system("clear"); 
    #endif
}

