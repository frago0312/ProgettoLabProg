//
// Created by franc on 25/09/2024.
//

#include "UserManager.h"

// Aggiunge un nuovo utente alla lista utilizzando smart pointer
void UserManager::addUser(const std::string& name) {
    users.push_back(std::make_shared<User>(name));  // Usa make_shared
}

// Restituisce tutti gli utenti come smart pointer
std::vector<std::shared_ptr<User>> UserManager::getUsers() const {
    return users;
}

// Cerca un utente in base al nome e restituisce un shared_ptr a quell'utente
std::shared_ptr<User> UserManager::findUser(const std::string& name) {
    for (auto& user : users) {
        if (user->getName() == name) {
            return user;
        }
    }
    return nullptr;
}
