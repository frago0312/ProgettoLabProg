//
// Created by franc on 24/09/2024.
//

#include "User.h"

#include <iostream>
#include <algorithm>

User::User(const std::string &name)
    : name(name) {
}

User::~User() {
    for (auto& list : shoppingLists) {
        list->detach(this);  // Rimuove l'observer da ogni lista
    }
    shoppingLists.clear();  // Svuota il vettore
}

void User::update(const std::string& message)  {
    std::cout << name << ": " << message << std::endl;
}

std::string User::getName() const {
    return name;
}

void User::addShoppingList(std::shared_ptr<ShoppingList> list) {
    shoppingLists.push_back(list);
    list->attach(this);
}

void User::removeShoppingList(std::shared_ptr<ShoppingList> list) {
    list->detach(this);
    shoppingLists.erase(std::remove(shoppingLists.begin(), shoppingLists.end(), list), shoppingLists.end());
}

std::vector<std::shared_ptr<ShoppingList> > User::getShoppingLists() const {
    return shoppingLists;
}
