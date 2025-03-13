cmake_minimum_required(VERSION 3.29)
project(ProgettoLabProg0924)

set(CMAKE_CXX_STANDARD 11)

# Creazione dell'eseguibile principale
add_executable(ProgettoLabProg0924
        main.cpp
        ItemCategory.h
        Item.cpp
        Item.h
        ShoppingList.cpp
        ShoppingList.h
        Observer.h
        Subject.h
        User.cpp
        User.h
        UserManager.cpp
        UserManager.h
        UserInterface.cpp
        UserInterface.h
        Utility.cpp
        Utility.h
)

# Scaricare e rendere disponibile Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.12.1
)

FetchContent_MakeAvailable(googletest)

# Abilita il supporto ai test
enable_testing()

# Aggiungere la sottodirectory per i test
add_subdirectory(tests)
