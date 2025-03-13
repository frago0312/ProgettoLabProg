#include <gtest/gtest.h>
#include "../Item.h"

class ItemTest : public ::testing::Test {
protected:
    Item *item;

    void SetUp() override {
        item = new Item("Mela", 3, ItemCategory::Alimentari);
    }

    void TearDown() override {
        delete item;
    }
};

// Testa che il costruttore inizializzi correttamente i valori di Item
TEST_F(ItemTest, ConstructorWorks) {
    EXPECT_EQ(item->getName(), "Mela");
    EXPECT_EQ(item->getAmount(), 3);
    EXPECT_FALSE(item->isBought());
}

// Testa che increaseAmount() aggiunga correttamente alla quantità
TEST_F(ItemTest, IncreaseAmountWorks) {
    item->increaseAmount(2);
    EXPECT_EQ(item->getAmount(), 5);
}

// Testa che changeBought() modifichi correttamente lo stato di acquisto
TEST_F(ItemTest, ChangeBoughtWorks) {
    item->changeBought();
    EXPECT_TRUE(item->isBought());
    item->changeBought();
    EXPECT_FALSE(item->isBought());
}
