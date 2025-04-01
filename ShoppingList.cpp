//
// Created by franc on 24/09/2024.
//

#include "ShoppingList.h"
#include "Utility.h"
#include "User.h"

#include <algorithm>
#include <iostream>

ShoppingList::ShoppingList(){
    std::cout << "Inserisci il nome della lista della spesa: ";
    name = stringInput();
}

//Ho creato questo secondo costruttore per implementare i google test
ShoppingList::ShoppingList(const std::string& listName) : name(listName) {
}

void ShoppingList::addItem(std::shared_ptr<Item> item) {
    items.push_back(item);
}

void ShoppingList::removeItem(int index) {
    if (index < items.size()) {
            items.erase(items.begin() + index);
        }
}

void ShoppingList::attach(std::shared_ptr<Observer> observer) {
    observers.push_back(observer);
}

void ShoppingList::detach(std::shared_ptr<Observer> observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void ShoppingList::notifyObservers(const std::string& message) {
    for (const auto& observer : observers) {
        if (observer) {
            observer->update(message);
        } else {
            std::cerr << "Errore: Observer nullo!" << std::endl;
        }
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

std::shared_ptr<Item> ShoppingList::getItemAt(int index) const {
    return items.at(index);
}

const std::string& ShoppingList::getName() const {
    return name;
}

std::vector<std::shared_ptr<Observer>> ShoppingList::getObservers() const {
    return observers;
}

bool ShoppingList::isDeletable() const {
    return observers.empty();
}

void ShoppingList::setName(const std::string &name) {
    this->name = name;
}


