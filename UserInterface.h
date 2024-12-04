//
// Created by franc on 25/09/2024.
//

#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "UserManager.h"
#include <memory>

class UserInterface {
public:
    explicit UserInterface(std::unique_ptr<UserManager> um) : userManager(std::move(um)) {}

    std::shared_ptr<User> userSelection() const;

    bool mainMenu(std::shared_ptr<User> user);

    void openList(std::shared_ptr<ShoppingList> & list, std::shared_ptr<User> user);

    void displayShoppingLists(std::shared_ptr<User> user);

    void createShoppingList(std::shared_ptr<User> user);


private:
    std::unique_ptr<UserManager> userManager;
};




#endif //USERINTERFACE_H
