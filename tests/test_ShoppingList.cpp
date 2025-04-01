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
    std::shared_ptr<MockObserver> mockObserver1;
    std::shared_ptr<MockObserver> mockObserver2;

    void SetUp() override {
        testItem1 = std::make_shared<Item>("Mele", 2, ItemCategory::Alimentari);
        testItem2 = std::make_shared<Item>("Pane", 1, ItemCategory::Alimentari);
        mockObserver1 = std::make_shared<MockObserver>();
        mockObserver2 = std::make_shared<MockObserver>();
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

// Test calcolo quantità totale items
TEST_F(ShoppingListTest, CalculateTotalItemQuantitiesTest) {
    auto localItem1 = std::make_shared<Item>("Mele", 2, ItemCategory::Alimentari);
    auto localItem2 = std::make_shared<Item>("Pane", 1, ItemCategory::Alimentari);

    ShoppingList list("Lista Spesa");
    list.addItem(localItem1);
    list.addItem(localItem2);

    int totalQuantities = list.getItemQuantities();

    EXPECT_EQ(totalQuantities, 3);
}

// Test isDeletable
TEST_F(ShoppingListTest, IsDeletable) {
    ShoppingList list("Lista Spesa");

    EXPECT_TRUE(list.isDeletable());

    list.attach(mockObserver1);

    EXPECT_FALSE(list.isDeletable());
}

// Test set e get nome
TEST_F(ShoppingListTest, SetAndGetName) {
    ShoppingList list("Lista Spesa");

    list.setName("Nuova Lista");

    EXPECT_EQ(list.getName(), "Nuova Lista");
}