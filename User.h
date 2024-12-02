//
// Created by franc on 24/09/2024.
//

#ifndef USER_H
#define USER_H
#include <memory>
#include <string>

#include "ShoppingList.h"


class User : public Observer, public std::enable_shared_from_this<User> {
public:
    explicit User(const std::string &name);

    ~User() override;

    void update() override;

    std::string getName() const;

    void addShoppingList(std::shared_ptr<ShoppingList> list);

    void removeShoppingList(std::shared_ptr<ShoppingList> list);

    std::vector<std::shared_ptr<ShoppingList>> getShoppingLists() const;

private:
    std::string name;
    std::vector<std::shared_ptr<ShoppingList>> shoppingLists;
};


#endif //USER_H
