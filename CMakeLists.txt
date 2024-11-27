cmake_minimum_required(VERSION 3.29)
project(ProgettoLabProg0924)

set(CMAKE_CXX_STANDARD 11)

add_executable(ProgettoLabProg0924 main.cpp
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
