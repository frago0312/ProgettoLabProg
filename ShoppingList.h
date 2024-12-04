//
// Created by franc on 24/09/2024.
//

#ifndef SHOPPINGLIST_H
#define SHOPPINGLIST_H
#include <memory>
#include <string>
#include <vector>

#include "Item.h"
#include "Observer.h"
#include "Subject.h"


class ShoppingList : public Subject{
public:
    explicit ShoppingList();

    void addItem(std::shared_ptr<Item> item);

    void removeItem(int index);

    void attach(Observer* observer) override;

    void detach(Observer* observer) override;

    void notifyObservers(const std::string& message) override;

    std::vector<std::shared_ptr<Item>> getItems() const;

    int getItemQuantities() const;

    int getItemCount() const;

    std::shared_ptr<Item> getItemAt(int index) const;

    const std::string &getName() const;

    std::vector<Observer *> getObservers() const;

private:
    std::string name;
    std::vector<std::shared_ptr<Item> > items;
    std::vector<Observer*> observers;
};




#endif //SHOPPINGLIST_H
