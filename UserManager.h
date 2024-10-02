//
// Created by franc on 25/09/2024.
//

#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <vector>
#include <memory>   // Per std::shared_ptr
#include <string>
#include "User.h"

class UserManager {
    std::vector<std::shared_ptr<User>> users;

public:
    // Aggiungi un nuovo utente
    void addUser(const std::string& name);

    // Restituisce la lista degli utenti
    std::vector<std::shared_ptr<User>> getUsers() const;

    // Trova un utente in base al nome
    std::shared_ptr<User> findUser(const std::string& name);
};

#endif // USERMANAGER_H

