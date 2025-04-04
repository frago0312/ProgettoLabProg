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
    // Cerco se esiste già un item con lo stesso nome
    for (auto& existingItem : items) {
        if (existingItem->getName() == item->getName()) {
            // Se l'item esiste già, aumento la quantità invece di aggiungere un duplicato
            existingItem->increaseAmount(item->getAmount());
            return;
        }
    }
    // Se non esiste, aggiungo il nuovo item
    items.push_back(item);
}

void ShoppingList::removeItem(int index) {
    if (index >= 0 && index < items.size()) {
        items.erase(items.begin() + index);
    } else {
        throw std::out_of_range("Indice non valido: l'oggetto da rimuovere non esiste");
    }
}

void ShoppingList::removeItemByName(const std::string& itemName) {
    auto it = std::find_if(items.begin(), items.end(),
                          [&itemName](const std::shared_ptr<Item>& item) {
                              return item->getName() == itemName;
                          });

    if (it != items.end()) {
        items.erase(it);
    } else {
        throw std::out_of_range("L'oggetto '" + itemName + "' non esiste nella lista");
    }
}

std::shared_ptr<Item> ShoppingList::findItemByName(const std::string& name) const {
    for (const auto& item : items) {
        if (item->getName() == name) {
            return item;
        }
    }
    return nullptr;  // Ritorna nullptr se l'item non esiste
}

void ShoppingList::attach(std::shared_ptr<Observer> observer) {
    if (std::find(observers.begin(), observers.end(), observer) == observers.end()) {
        observers.push_back(observer);
    }
}

void ShoppingList::detach(std::shared_ptr<Observer> observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void ShoppingList::notifyObservers(const std::string& message) {
    for (const auto& observer : observers) {
        observer->update(message);
    }
}

std::vector<std::shared_ptr<Item>> ShoppingList::getItems() const {
    return items;
}

// Restituisce il numero di oggetti distinti nella lista, senza considerare le quantità
int ShoppingList::getItemCount() const {
    return items.size();
}

std::shared_ptr<Item> ShoppingList::getItemAt(int index) const {
    return items.at(index);
}

const std::string& ShoppingList::getName() const {
    return name;
}

const std::vector<std::shared_ptr<Observer>> & ShoppingList::getObservers() const {
    return observers;
}

bool ShoppingList::isDeletable() const {
    return observers.empty();
}

void ShoppingList::setName(const std::string &name) {
    this->name = name;
}
