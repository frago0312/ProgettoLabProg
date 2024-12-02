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

void ShoppingList::removeItem(std::shared_ptr<Item> item) {
    auto it = std::find(items.begin(), items.end(), item);
    if (it != items.end()) {
        items.erase(it);
        notifyObservers();
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

int ShoppingList::getItemCount() const {
    int count = 0;
    for (auto it: items)
        count+=it->getAmount();
    return count;
}

const std::string& ShoppingList::getName() const {
    return name;
}

std::vector<std::shared_ptr<Item>> ShoppingList::getItems() const {
    return items;
}

void ShoppingList::displayList() const {
    int i = 1;
    std::cout << "Lista della spesa: " << name << "\n";
    for (const auto& item : items) {
        std::cout <<i<<". "<< item->getName() << "\t-\t" << item->getAmount() << " unita'\n";
        ++i;
    }
    std::cout << "Totale elementi: " << getItemCount() << "\n";
    printSeparator();
}

void ShoppingList::shareListWith(std::shared_ptr<Observer> user)  {
    attach(user);
}
