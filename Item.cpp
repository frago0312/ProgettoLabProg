//
// Created by franc on 24/09/2024.
//

#include "Item.h"

#include <iostream>
#include <limits>

#include "utility.h"

Item::Item(std::string n, int a, ItemCategory c) {
    name = n;

    // Controllo per quantità negativa, lancia eccezione
    if (a < 0) {
        throw std::invalid_argument("La quantità non può essere negativa");
    }

    // Se la quantità è 0, l'oggetto è uncountable
    countable = (a > 0);
    amount = a;
    category = c;
    bought = false;
}

// Nuovo metodo per verificare se l'oggetto è countable
bool Item::isCountable() const {
    return countable;
}

int Item::getAmount() const {
    return amount;
}

void Item::increaseAmount(int a) {
    // Se l'oggetto è uncountable, non modificare la quantità
    if (!countable) {
        return;
    }

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



