//
// Created by franc on 24/09/2024.
//

#include "Item.h"

#include <iostream>
#include <limits>

#include "utility.h"

Item::Item(std::string n, int a, ItemCategory c) {
    name=n;
    amount=a;
    category=c;
    bought=false;
}



int Item::getAmount() const {
    return amount;
}

std::string Item::getName() const {
    return name;
}

bool Item::isBought() const {
    return bought;
}

void Item::changeBought() {
    bought=!bought;
}



