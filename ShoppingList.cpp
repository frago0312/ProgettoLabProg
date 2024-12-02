//
// Created by franc on 24/09/2024.
//

#include "ShoppingList.h"
#include "Utility.h"

#include <algorithm>
#include <iostream>

ShoppingList::ShoppingList(){
    std::cout << "Inserisci il nome della lista della spesa: ";
    name = stringInput();
}

void ShoppingList::addItem(std::shared_ptr<Item> item) {
    items.push_back(item);
    notifyObservers();
}

void ShoppingList::removeItem(int index) {
    if (index < items.size()) {
            items.erase(items.begin() + index);
        }
}

void ShoppingList::attach(std::shared_ptr<Observer> observer)  {
    observers.push_back(observer);
}

void ShoppingList::detach(std::shared_ptr<Observer> observer)  {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void ShoppingList::notifyObservers()  {
    for (const auto& observer : observers) {
        observer->update();
    }
}

std::vector<std::shared_ptr<Item>> ShoppingList::getItems() const {
    return items;
}

int ShoppingList::getItemQuantities() const {
    int count = 0;
    for (auto it: items)
        count+=it->getAmount();
    return count;
}

int ShoppingList::getItemCount() const {
    return items.size();
}

const std::string& ShoppingList::getName() const {
    return name;
}


void ShoppingList::shareListWith(std::shared_ptr<Observer> user)  {
    attach(user);
}
