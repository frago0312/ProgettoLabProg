//
// Created by franc on 24/09/2024.
//

#ifndef ITEM_H
#define ITEM_H
#include <string>

#include "ItemCategory.h"


class Item {
public:
    Item();
    void initAmount();
    void initCategory();
    int getAmount() const;
    std::string getName() const;
    bool isBought() const;

private:
    std::string name;
    int amount;
    bool bought;
    ItemCategory category;
};



#endif //ITEM_H
