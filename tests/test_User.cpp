#include <gtest/gtest.h>
#include "../User.h"
#include "../ShoppingList.h"

TEST(UserTest, GetName) {
    User user("Francesco");
    EXPECT_EQ(user.getName(), "Francesco");
}

TEST(UserTest, AddShoppingList) {
    auto user = std::make_shared<User>("Bob");
    auto list = std::make_shared<ShoppingList>("Esselunga");

    user->addShoppingList(list);
    EXPECT_EQ(user->getShoppingLists().size(), 1);
    EXPECT_EQ(user->getShoppingLists()[0]->getName(), "Esselunga");
    EXPECT_EQ(list->getObservers().size(), 1); // L'utente dovrebbe essere tra gli observer
}

TEST(UserTest, RemoveShoppingList) {
    auto user = std::make_shared<User>("Carlo");
    auto list = std::make_shared<ShoppingList>("Conad");

    user->addShoppingList(list);
    user->removeShoppingList(list);
    EXPECT_TRUE(user->getShoppingLists().empty());
    EXPECT_TRUE(list->getObservers().empty()); // L'utente deve essere rimosso dagli observer
}

TEST(UserTest, UpdateMessage) {
    testing::internal::CaptureStdout();
    User user("Davide");
    user.update("New items available");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Davide: New items available\n");
}

TEST(UserTest, DestructorRemovesUserFromLists) {
    auto list = std::make_shared<ShoppingList>("Office Supplies");
    std::shared_ptr<User> user = std::make_shared<User>("Emma");
    user->addShoppingList(list);
    EXPECT_FALSE(list->getObservers().empty());
}

