#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <gmock/gmock-function-mocker.h>
#include <gmock/gmock-spec-builders.h>

#include "../ShoppingList.h"
#include "../User.h"

// Verifica che l'aggiunta di un observer funzioni correttamente
TEST(ObserverTest, AddObserver) {
    auto user = std::make_shared<User>("Mario");
    auto shoppingList = std::make_shared<ShoppingList>("Lista 1");

    shoppingList->attach(user);

    ASSERT_EQ(shoppingList->getObservers().size(), 1);
    ASSERT_EQ(shoppingList->getObservers().front(), user);
}

// Verifica che la rimozione di un observer funzioni correttamente
TEST(ObserverTest, RemoveObserver) {
    auto user = std::make_shared<User>("Mario");
    auto shoppingList = std::make_shared<ShoppingList>("Lista 1");

    shoppingList->attach(user);
    shoppingList->detach(user);

    ASSERT_EQ(shoppingList->getObservers().size(), 0);
}

// Controlla che la notifica degli observer venga ricevuta correttamente
class MockUser : public User {
public:
    using User::User;
    MOCK_METHOD(void, update, (const std::string& message), (override));
};

TEST(ObserverTest, NotifyObserver) {
    auto mockUser = std::make_shared<MockUser>("Mario");
    auto shoppingList = std::make_shared<ShoppingList>("Lista 1");

    shoppingList->attach(mockUser);

    EXPECT_CALL(*mockUser, update("Test notifiche")).Times(1);

    shoppingList->notifyObservers("Test notifiche");
}

// Verifica la gestione della distruzione della ShoppingList
TEST(ObserverTest, DestroyShoppingList) {
    auto user = std::make_shared<User>("Mario");

    {
        auto shoppingList = std::make_shared<ShoppingList>("Lista 1");
        user->addShoppingList(shoppingList);

        ASSERT_EQ(shoppingList->getObservers().size(), 1);
        ASSERT_EQ(user->getShoppingLists().size(), 1);
    }

    ASSERT_EQ(user->getShoppingLists().size(), 1);
    ASSERT_EQ(user->getName(), "Mario");
}
