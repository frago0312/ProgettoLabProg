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
    void addUser(const std::string& name);

    std::vector<std::shared_ptr<User>> getUsers() const;

    std::shared_ptr<User> findUser(const std::string& name);
};

#endif // USERMANAGER_H

