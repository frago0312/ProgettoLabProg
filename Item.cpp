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

void Item::increaseAmount(int a) {
    // in caso di "aumenti" negativi, la quantità viene sottratta e, se diventa negativa, viene settata a 0 e l'oggetto viene segnato come comprato
    amount += a;
    if (amount <= 0) {
        amount = 0;
        bought = true;
    }
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



