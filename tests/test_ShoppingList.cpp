#include <gtest/gtest.h>
#include <memory>
#include "../ShoppingList.h"
#include "../Item.h"
#include "../Observer.h"

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

// Verifica che il costruttore imposti correttamente il nome della lista
TEST_F(ShoppingListTest, ConstructorWithNameTest) {
    ShoppingList list("Lista Spesa");
    EXPECT_EQ(list.getName(), "Lista Spesa");
}

// Controlla che l'aggiunta di un item funzioni correttamente
TEST_F(ShoppingListTest, AddItemTest) {
    ShoppingList list("Lista Spesa");
    list.addItem(testItem1);

    EXPECT_EQ(list.getItemCount(), 1);
    EXPECT_EQ(list.getItemAt(0), testItem1);
}

// Verifica che la rimozione di un item funzioni correttamente
TEST_F(ShoppingListTest, RemoveItemTest) {
    ShoppingList list("Lista Spesa");
    list.addItem(testItem1);
    list.addItem(testItem2);

    list.removeItem(0);

    EXPECT_EQ(list.getItemCount(), 1);
    EXPECT_EQ(list.getItemAt(0), testItem2);
}

// Controlla che il calcolo delle quantità totali degli item sia corretto
TEST_F(ShoppingListTest, CalculateTotalItemQuantitiesTest) {
    auto localItem1 = std::make_shared<Item>("Mele", 2, ItemCategory::Alimentari);
    auto localItem2 = std::make_shared<Item>("Pane", 1, ItemCategory::Alimentari);

    ShoppingList list("Lista Spesa");
    list.addItem(localItem1);
    list.addItem(localItem2);

    int totalQuantities = list.getItemQuantities();

    EXPECT_EQ(totalQuantities, 3);
}

// Verifica se la lista è eliminabile in base agli osservatori collegati
TEST_F(ShoppingListTest, IsDeletable) {
    ShoppingList list("Lista Spesa");

    EXPECT_TRUE(list.isDeletable());

    list.attach(mockObserver1);

    EXPECT_FALSE(list.isDeletable());
}

// Controlla che l'impostazione e il recupero del nome funzionino correttamente
TEST_F(ShoppingListTest, SetAndGetName) {
    ShoppingList list("Lista Spesa");

    list.setName("Nuova Lista");

    EXPECT_EQ(list.getName(), "Nuova Lista");
}