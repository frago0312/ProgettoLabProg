# Cerca tutti i file .cpp nella directory principale del progetto, escludendo main.cpp
file(GLOB PROJECT_SOURCES "${PROJECT_SOURCE_DIR}/*.cpp")
list(REMOVE_ITEM PROJECT_SOURCES "${PROJECT_SOURCE_DIR}/main.cpp")

# Creazione dell'eseguibile di test
add_executable(ProgettoLabProg0924_Tests
        test_main.cpp
        test_Item.cpp
        test_User.cpp
        test_ShoppingList.cpp
        #test_User.cpp
        # Aggiungi altri test qui...
)

# Linka l'eseguibile di test con Google Test e con il codice del progetto
target_link_libraries(ProgettoLabProg0924_Tests
        PRIVATE
        gtest
        gtest_main
        gmock
        gmock_main
        # Linka i file di implementazione del progetto
        ${PROJECT_SOURCES}
)

# Registra i test in CTest
add_test(NAME ProgettoLabProg0924_Tests COMMAND ProgettoLabProg0924_Tests)

