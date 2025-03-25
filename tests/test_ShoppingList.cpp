//
// Created by franc on 25/03/2025.
//

#include <gtest/gtest.h>
#include <memory>
#include "../ShoppingList.h"
#include "../Item.h"
#include "../Observer.h"

// Mock Observer per testare le notifiche
class MockObserver : public Observer {
public:
    int updateCallCount = 0;
    std::string lastMessage;

    void update(const std::string& message) override {
        updateCallCount++;
        lastMessage = message;
    }
};

class ShoppingListTest : public ::testing::Test {
protected:
    std::shared_ptr<Item> testItem1;
    std::shared_ptr<Item> testItem2;
    MockObserver mockObserver1;
    MockObserver mockObserver2;

    void SetUp() override {
        // Ricrea gli item prima di ogni test, assicurandoti che siano sempre nuovi
        testItem1 = std::make_shared<Item>("Mele", 2, ItemCategory::Alimentari);
        testItem2 = std::make_shared<Item>("Pane", 1, ItemCategory::Abbigliamento);

        // Resetta anche gli observer
        mockObserver1 = MockObserver();
        mockObserver2 = MockObserver();
    }
};

// Test del costruttore con nome
TEST_F(ShoppingListTest, ConstructorWithNameTest) {
    ShoppingList list("Lista Spesa");
    EXPECT_EQ(list.getName(), "Lista Spesa");
}

// Test aggiunta item
TEST_F(ShoppingListTest, AddItemTest) {
    ShoppingList list("Lista Spesa");
    list.addItem(testItem1);

    EXPECT_EQ(list.getItemCount(), 1);
    EXPECT_EQ(list.getItemAt(0), testItem1);
}

// Test rimozione item
TEST_F(ShoppingListTest, RemoveItemTest) {
    ShoppingList list("Lista Spesa");
    list.addItem(testItem1);
    list.addItem(testItem2);

    list.removeItem(0);

    EXPECT_EQ(list.getItemCount(), 1);
    EXPECT_EQ(list.getItemAt(0), testItem2);
}

// Test calcolo quantità totale items (cambiato nome)
TEST_F(ShoppingListTest, CalculateTotalItemQuantitiesTest) {
    // Crea nuovi item locali invece di usare quelli di classe
    auto localItem1 = std::make_shared<Item>("Mele", 2, ItemCategory::Alimentari);
    auto localItem2 = std::make_shared<Item>("Pane", 1, ItemCategory::Abbigliamento);

    ShoppingList list("Lista Spesa");
    list.addItem(localItem1);
    list.addItem(localItem2);

    int totalQuantities = list.getItemQuantities();

    EXPECT_EQ(totalQuantities, 3);
}

// Test gestione observer
TEST_F(ShoppingListTest, ObserverManagement) {
    ShoppingList list("Lista Spesa");

    list.attach(&mockObserver1);
    list.attach(&mockObserver2);

    EXPECT_EQ(list.getObservers().size(), 2);

    list.detach(&mockObserver1);

    EXPECT_EQ(list.getObservers().size(), 1);
}

// Test isDeletable
TEST_F(ShoppingListTest, IsDeletable) {
    ShoppingList list("Lista Spesa");

    EXPECT_TRUE(list.isDeletable());

    list.attach(&mockObserver1);

    EXPECT_FALSE(list.isDeletable());
}

// Test set e get nome
TEST_F(ShoppingListTest, SetAndGetName) {
    ShoppingList list("Lista Spesa");

    list.setName("Nuova Lista");

    EXPECT_EQ(list.getName(), "Nuova Lista");
}