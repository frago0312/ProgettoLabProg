//
// Created by franc on 24/09/2024.
//

#ifndef ITEM_H
#define ITEM_H
#include <string>

#include "ItemCategory.h"


class Item {
public:
    Item(std::string n, int a, ItemCategory c);
    int getAmount() const;
    void increaseAmount(int a);
    std::string getName() const;
    bool isBought() const;
    void changeBought();
    bool isCountable() const;

private:
    std::string name;
    int amount;
    bool bought;
    ItemCategory category;
    bool countable;
};



#endif //ITEM_H
