#include <gtest/gtest.h>
#include <memory>
#include "../shoppinglist.h"
#include "../item.h"
#include "../user.h"

class MockObserver : public Observer {
public:
    void update(const std::string& message) override {
        lastMessage = message;
    }
    std::string lastMessage;
};

class ShoppingListTest : public ::testing::Test {
protected:
    std::shared_ptr<Item> item1;
    std::shared_ptr<Item> item2;
    std::shared_ptr<MockObserver> observer;

    void SetUp() override {
        item1 = std::make_shared<Item>("Mele", 5, ItemCategory::Alimentari);
        item2 = std::make_shared<Item>("Pane", 2, ItemCategory::Alimentari);
        observer = std::make_shared<MockObserver>();
    }
};

// Verifica che il costruttore inizializzi correttamente la lista della spesa
TEST_F(ShoppingListTest, DefaultConstructor) {
    ShoppingList list("Test List");
    EXPECT_TRUE(list.getItems().empty());
    EXPECT_EQ(list.getName(), "Test List");
    EXPECT_EQ(list.getItemCount(), 0);
}

// Controlla che l'aggiunta e la rimozione degli oggetti funzionino correttamente
TEST_F(ShoppingListTest, AddRemoveItems) {
    ShoppingList list("Test List");

    list.addItem(item1);
    EXPECT_EQ(list.getItemCount(), 1);
    EXPECT_EQ(list.getItemAt(0), item1);

    list.addItem(item2);
    EXPECT_EQ(list.getItemCount(), 2);

    list.removeItem(0);
    EXPECT_EQ(list.getItemCount(), 1);
    EXPECT_EQ(list.getItemAt(0), item2);
}

// Verifica che getItemQuantities() restituisca la quantità totale corretta
TEST_F(ShoppingListTest, GetItemQuantities) {
    ShoppingList list("Test List");
    list.addItem(item1);
    list.addItem(item2);

    EXPECT_EQ(list.getItemQuantities(), 7); // 5 mele + 2 pani
}

// Controlla che il pattern Observer funzioni correttamente
TEST_F(ShoppingListTest, ObserverPattern) {
    ShoppingList list("Observer Test List");

    list.attach(observer);
    EXPECT_EQ(list.getObservers().size(), 1);

    list.notifyObservers("Test Message");
    EXPECT_EQ(observer->lastMessage, "Test Message");

    list.detach(observer);
    EXPECT_TRUE(list.getObservers().empty());
}

// Verifica se la lista della spesa è eliminabile in base agli osservatori
TEST_F(ShoppingListTest, Deletability) {
    ShoppingList list("Deletability Test List");
    EXPECT_TRUE(list.isDeletable());

    list.attach(observer);
    EXPECT_FALSE(list.isDeletable());

    list.detach(observer);
    EXPECT_TRUE(list.isDeletable());
}

// Controlla che la gestione del nome della lista funzioni correttamente
TEST_F(ShoppingListTest, NameManagement) {
    ShoppingList list("Original Name");
    list.setName("Spesa Settimanale");
    EXPECT_EQ(list.getName(), "Spesa Settimanale");
}

