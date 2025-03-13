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
        if (list) {
            list->detach(this);  // Rimuove l'observer da ogni lista
        }
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



std::vector<std::shared_ptr<ShoppingList> > User::getShoppingLists() const {
    return shoppingLists;
}

void User::removeShoppingList(std::shared_ptr<ShoppingList> list) {
    // Verifica se l'utente è presente nella lista e rimuovilo
    auto it = std::find(shoppingLists.begin(), shoppingLists.end(), list);
    if (it != shoppingLists.end()) {
        shoppingLists.erase(it);
        // Rimuovi l'utente come osservatore dalla lista
        list->detach(this);  // Usando "this" perché "User" è un Observer
    }
}
