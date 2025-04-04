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
    ShoppingList* list;

    void SetUp() override {
        testItem1 = std::make_shared<Item>("Mele", 2, ItemCategory::Alimentari);
        testItem2 = std::make_shared<Item>("Pane", 1, ItemCategory::Alimentari);
        mockObserver1 = std::make_shared<MockObserver>();
        mockObserver2 = std::make_shared<MockObserver>();
        list = new ShoppingList("Lista Spesa");
    }

    void TearDown() override {
        delete list;
    }
};

// Verifica che il costruttore imposti correttamente il nome della lista
TEST_F(ShoppingListTest, ConstructorWithNameTest) {
    EXPECT_EQ(list->getName(), "Lista Spesa");
}

// Controlla che l'aggiunta di un item funzioni correttamente
TEST_F(ShoppingListTest, AddItemTest) {
    list->addItem(testItem1);

    EXPECT_EQ(list->getItemCount(), 1);
    EXPECT_EQ(list->getItemAt(0), testItem1);
}

// Verifica che la rimozione di un item funzioni correttamente
TEST_F(ShoppingListTest, RemoveItemTest) {
    list->addItem(testItem1);
    list->addItem(testItem2);

    list->removeItem(0);

    EXPECT_EQ(list->getItemCount(), 1);
    EXPECT_EQ(list->getItemAt(0), testItem2);
}

// Controlla che il calcolo delle quantità totali degli item sia corretto
TEST_F(ShoppingListTest, CalculateTotalItemQuantitiesTest) {
    auto localItem1 = std::make_shared<Item>("Mele", 2, ItemCategory::Alimentari);
    auto localItem2 = std::make_shared<Item>("Pane", 1, ItemCategory::Alimentari);

    list->addItem(localItem1);
    list->addItem(localItem2);

    int totalQuantities = list->getItemCount();

    EXPECT_EQ(totalQuantities, 2);
}

// Verifica se la lista è eliminabile in base agli osservatori collegati
TEST_F(ShoppingListTest, IsDeletable) {
    EXPECT_TRUE(list->isDeletable());

    list->attach(mockObserver1);

    EXPECT_FALSE(list->isDeletable());
}

// Controlla che l'impostazione e il recupero del nome funzionino correttamente
TEST_F(ShoppingListTest, SetAndGetName) {
    list->setName("Nuova Lista");

    EXPECT_EQ(list->getName(), "Nuova Lista");
}

// Test per verificare che addItem() non aggiunga duplicati ma aggiorni la quantità
TEST_F(ShoppingListTest, NoDuplicateItemsAdded) {
    list->addItem(testItem1);
    int initialCount = list->getItemCount();

    // Creo un item con lo stesso nome ma quantità diversa
    auto duplicateItem = std::make_shared<Item>("Mele", 3, ItemCategory::Alimentari);
    list->addItem(duplicateItem);

    EXPECT_EQ(list->getItemCount(), initialCount);
    EXPECT_EQ(list->findItemByName("Mele")->getAmount(), 5);  // 2 + 3
}

// Test per verificare che removeItem() lanci un'eccezione con un indice non valido
TEST_F(ShoppingListTest, RemoveItemWithInvalidIndex) {
    EXPECT_THROW({
        list->removeItem(10);  // Indice non valido
    }, std::out_of_range);

    EXPECT_THROW({
        list->removeItem(-1);  // Indice negativo
    }, std::out_of_range);
}

// Test per verificare che removeItemByName() funzioni correttamente
TEST_F(ShoppingListTest, RemoveItemByNameWorks) {
    list->addItem(testItem1);
    list->addItem(testItem2);
    int initialCount = list->getItemCount();

    list->removeItemByName("Mele");

    EXPECT_EQ(list->getItemCount(), initialCount - 1);
    EXPECT_EQ(list->findItemByName("Mele"), nullptr);
}

// Test per verificare che removeItemByName() lanci un'eccezione se l'item non esiste
TEST_F(ShoppingListTest, RemoveNonExistentItemByName) {
    EXPECT_THROW({
        list->removeItemByName("Prodotto inesistente");
    }, std::out_of_range);
}

// Test per verificare che findItemByName() funzioni correttamente
TEST_F(ShoppingListTest, FindItemByNameWorks) {
    list->addItem(testItem1);

    auto foundItem = list->findItemByName("Mele");
    EXPECT_NE(foundItem, nullptr);
    EXPECT_EQ(foundItem->getName(), "Mele");

    auto notFoundItem = list->findItemByName("Prodotto inesistente");
    EXPECT_EQ(notFoundItem, nullptr);
}

// Test per verificare che addItem non aggiunga duplicati anche con categorie diverse
TEST_F(ShoppingListTest, NoDuplicatesWithDifferentCategories) {
    list->addItem(testItem1);
    int initialCount = list->getItemCount();

    // Stesso nome ma categoria diversa
    auto duplicateWithDiffCategory = std::make_shared<Item>("Mele", 3, ItemCategory::Elettronica);
    list->addItem(duplicateWithDiffCategory);

    // Dovrebbe aggiornare la quantità e non aggiungere un nuovo item
    EXPECT_EQ(list->getItemCount(), initialCount);
    EXPECT_EQ(list->findItemByName("Mele")->getAmount(), 5);
}

// Test per la gestione di oggetti uncountable nella lista
TEST_F(ShoppingListTest, UncountableItemsInList) {
    auto uncountableItem = std::make_shared<Item>("Sale", 0, ItemCategory::Alimentari);
    list->addItem(uncountableItem);

    EXPECT_FALSE(list->findItemByName("Sale")->isCountable());

    // Aggiungere un duplicato non dovrebbe modificare lo stato uncountable
    auto duplicateUncountable = std::make_shared<Item>("Sale", 0, ItemCategory::Alimentari);
    list->addItem(duplicateUncountable);

    EXPECT_FALSE(list->findItemByName("Sale")->isCountable());
}