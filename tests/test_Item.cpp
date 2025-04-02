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

// Verifica che il costruttore inizializzi correttamente i valori di Item
TEST_F(ItemTest, ConstructorWorks) {
    EXPECT_EQ(item->getName(), "Mela");
    EXPECT_EQ(item->getAmount(), 3);
    EXPECT_FALSE(item->isBought());
}

// Controlla che increaseAmount() aumenti correttamente la quantità
TEST_F(ItemTest, IncreaseAmountWorks) {
    item->increaseAmount(2);
    EXPECT_EQ(item->getAmount(), 5);
}

// Verifica che changeBought() alterni correttamente lo stato di acquisto
TEST_F(ItemTest, ChangeBoughtWorks) {
    item->changeBought();
    EXPECT_TRUE(item->isBought());
    item->changeBought();
    EXPECT_FALSE(item->isBought());
}

// Controlla che increaseAmount() aggiunga una quantità positiva
TEST_F(ItemTest, IncreaseAmountPositive) {
    item->increaseAmount(5);
    EXPECT_EQ(item->getAmount(), 8);
    EXPECT_FALSE(item->isBought());
}

// Verifica che diminuire la quantità sotto zero la imposti a zero e consideri l'oggetto acquistato
TEST_F(ItemTest, DecreaseAmountBelowZero) {
    item->increaseAmount(-4);
    EXPECT_EQ(item->getAmount(), 0);
    EXPECT_TRUE(item->isBought());
}

// Controlla che ridurre la quantità esattamente a zero imposti lo stato di acquisto
TEST_F(ItemTest, DecreaseAmountToZero) {
    item->increaseAmount(-3);
    EXPECT_EQ(item->getAmount(), 0);
    EXPECT_TRUE(item->isBought());
}

// Verifica che increaseAmount(0) non modifichi lo stato dell'oggetto
TEST_F(ItemTest, NoChangeWithZero) {
    item->increaseAmount(0);
    EXPECT_EQ(item->getAmount(), 3);
    EXPECT_FALSE(item->isBought());
}