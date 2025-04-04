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

class User;

class ShoppingList : public Subject{
public:
    explicit ShoppingList();

    ShoppingList(const std::string &listName);

    void addItem(std::shared_ptr<Item> item);

    void removeItem(int index);

    void removeItemByName(const std::string& name);

    void attach(std::shared_ptr<Observer> observer) override;

    void detach(std::shared_ptr<Observer> observer) override;

    void notifyObservers(const std::string& message) override;

    std::vector<std::shared_ptr<Item>> getItems() const;

    int getItemCount() const;

    std::shared_ptr<Item> getItemAt(int index) const;

    std::shared_ptr<Item> findItemByName(const std::string& name) const;

    const std::string &getName() const;

    const std::vector<std::shared_ptr<Observer>>& getObservers() const;

    bool isDeletable() const;

    void setName(const std::string &name);

    ~ShoppingList() override {
        observers.clear();
        items.clear();
    };

    size_t getObserverCount() const {
        return observers.size();
    }

private:
    std::string name;
    std::vector<std::shared_ptr<Item> > items;
    std::vector<std::shared_ptr<Observer>> observers;
};




#endif //SHOPPINGLIST_H
