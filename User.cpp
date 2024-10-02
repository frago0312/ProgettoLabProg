//
// Created by franc on 24/09/2024.
//

#include "User.h"

#include <iostream>
#include <algorithm>

User::User(const std::string &name)
    : name(name) {
}

void User::update()  {
    std::cout << "User " << name << " has been notified of changes in the shopping list." << std::endl;
}

std::string User::getName() const {
    return name;
}

void User::addShoppingList(std::shared_ptr<ShoppingList> list) {
    shoppingLists.push_back(list);
    list->attach(shared_from_this());
}

void User::removeShoppingList(std::shared_ptr<ShoppingList> list) {
    auto it = std::find(shoppingLists.begin(), shoppingLists.end(), list);
    if (it != shoppingLists.end()) {
        list->detach(shared_from_this());
        shoppingLists.erase(it);
    }
}

std::vector<std::shared_ptr<ShoppingList> > User::getShoppingLists() const {
    return shoppingLists;
}
