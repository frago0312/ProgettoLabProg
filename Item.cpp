//
// Created by franc on 24/09/2024.
//

#include "Item.h"

#include <iostream>
#include <limits>

#include "utility.h"

Item::Item() {
    amount=0;
    category=ItemCategory::None;
    bought=false;
    std::cout << "Insert item name:";
    name=stringInput();
    initAmount();
    initCategory();
}


void Item::initAmount() {
    while (true) {
        std::cout << "Insert amount: ";
        std::cin >> amount;

        // Controllo se l'input è valido
        if (std::cin.fail() || amount < 0) {
            std::cin.clear(); // Ripristina lo stato di errore
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora l'input errato
            std::cout << "Invalid input. Please enter a valid integer for amount.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Pulisci il buffer
            break; // Uscita dal ciclo se l'input è valido
        }
    }
}

void Item::initCategory() {
    int choice;
    std::cout << "Select a category:\n";
    std::cout << "1. Groceries\n";
    std::cout << "2. Clothing\n";
    std::cout << "3. Electronics\n";
    std::cout << "4. Home\n";
    std::cout << "5. Health\n";
    std::cout << "6. Pets\n";
    std::cout << "7. Extras\n";
    std::cout << "Enter your choice (1-7): ";
    std::cin >> choice;

    switch (choice) {
        case 1: category = ItemCategory::Groceries; break;
        case 2: category = ItemCategory::Clothing; break;
        case 3: category = ItemCategory::Electronics; break;
        case 4: category = ItemCategory::Home; break;
        case 5: category = ItemCategory::Health; break;
        case 6: category = ItemCategory::Pets; break;
        case 7: category = ItemCategory::Extras; break;
        default: category = ItemCategory::None;
    }
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



