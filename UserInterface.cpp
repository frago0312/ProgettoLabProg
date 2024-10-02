//
// Created by franc on 25/09/2024.
//
#include "UserInterface.h"
#include <iostream>
#include <limits>

#include "Utility.h"

std::shared_ptr<User> UserInterface::userSelection() const {
    std::shared_ptr<User> selectedUser = nullptr;

    while (selectedUser == nullptr) {
        // Continua finché non si seleziona un utente
        std::cout << "Benvenuto! Seleziona un'opzione:\n";
        std::cout << "1. Accedi come utente esistente\n";
        std::cout << "2. Crea nuovo utente\n";
        std::cout << "3. Esci dal programma\n";

        int choice = integerInput();
        printSeparator();

        if (choice == 1) {
            auto users = userManager->getUsers(); // Usa il puntatore unico
            if (users.empty()) {
                std::cout << "Nessun utente trovato. Devi prima creare un utente.\n";
                printSeparator();
                continue; // Torna all'inizio del ciclo
            }

            int userChoice = -1; // Inizializza con un valore non valido

            while (userChoice < 1 || userChoice > users.size()) { // Continua a chiedere finché non si sceglie un utente valido
                std::cout << "Seleziona un utente esistente:\n";
                for (size_t i = 0; i < users.size(); ++i) {
                    std::cout << i + 1 << ". " << users[i]->getName() << "\n";
                }
                std::cout << users.size() + 1 << ". Torna al menu principale\n";

                userChoice = integerInput();

                if (userChoice == users.size() + 1) { // Torna al menu principale
                    printSeparator();
                    break; // Esce dal ciclo interno e torna al menu principale
                }

                if (userChoice > 0 && userChoice <= users.size()) {
                    selectedUser = users[userChoice - 1]; // Seleziona l'utente
                } else {
                    std::cout << "Utente non esistente. Riprova.\n";
                    printSeparator();
                }
            }

        } else if (choice == 2) {
            std::cout << "Inserisci il nome del nuovo utente: ";
            std::string newName = stringInput();
            userManager->addUser(newName); // Usa il puntatore unico
            std::cout << "Utente " << newName << " creato con successo!\n";
            printSeparator();
            // Non uscire dal ciclo, permette di scegliere di nuovo
        } else if (choice == 3) {
            std::cout << "Uscita dal programma...\n";
            return nullptr;
        } else {
            std::cout << "Opzione non valida. Riprova.\n";
            printSeparator();
        }
    }

    return selectedUser;
}


bool UserInterface::mainMenu(std::shared_ptr<User> user) {

    while (true) {
        std::cout << "Benvenuto " << user->getName() << "!\n";
        std::cout << "Seleziona un'opzione:\n";
        std::cout << "1. Visualizza le tue liste della spesa\n";
        std::cout << "2. Crea una nuova lista della spesa\n";
        std::cout << "3. Cambia utente\n";
        std::cout << "4. Esci dal programma\n";

        int choice = integerInput(); // Funzione che ottiene un input intero dall'utente

        printSeparator();

        switch (choice) {
            case 1: {
                // Visualizza le liste dell'utente corrente
                displayShoppingLists(user);
                break;
            }
            case 2: {
                // Crea una nuova lista della spesa
                createShoppingList(user);
                break;
            }
            case 3: {
                // Restituisco true se voglio tornare alla selezione utente
                std::cout << "Tornando alla selezione utente...\n";
                return true;
            }
            case 4: {
                // Restituisco false se voglio uscire dal programma
                std::cout << "Uscita dal programma...\n";
                return false;
            }
            default: {
                std::cout << "Opzione non valida. Riprova.\n";
                break;
            }
        }
    }
}


// Funzione per visualizzare le liste della spesa dell'utente
void UserInterface::displayShoppingLists(std::shared_ptr<User> user) {
    const auto& lists = user->getShoppingLists();

    if (lists.empty()) {
        std::cout << "Nessuna lista della spesa trovata.\n";
        printSeparator();
        return;
    }

    while (true) {
        std::cout << "Ecco le tue liste della spesa, scegli quale vuoi aprire:\n";
        for (size_t i = 0; i < lists.size(); ++i) {
            std::cout << i + 1 << ". " << lists[i]->getName() << ":\t"<<lists[i]->getItemCount()<<" oggetti\n";
        }
        std::cout << lists.size() + 1 << ". Torna al menu principale\n";

        int choice = integerInput();

        if (choice >= 1 && choice <= lists.size()) {
            // Apri la lista selezionata
            openList(lists[choice - 1]);
            printSeparator();
        } else if (choice == lists.size() + 1) {
            // Torna al menu principale
            printSeparator();
            return;
        } else {
            // Scelta non valida, ripeti la richiesta
            std::cout << "Opzione non valida. Riprova.\n";
            printSeparator();
        }
    }
}


// Funzione per creare una nuova lista della spesa e collegarla all'utente
void UserInterface::createShoppingList(std::shared_ptr<User> user) {
    auto newList = std::make_shared<ShoppingList>();
    user->addShoppingList(newList);
    std::cout << "Lista "<< newList->getName() <<" creata con successo!\n";
    printSeparator();
}

// Funzione per visualizzare una lista della spesa
void UserInterface::openList(const std::shared_ptr<ShoppingList> &list) {
    bool keepOpen = true;
    while (keepOpen) {
        list->displayList();
        std::cout << "\nScegli un'opzione:\n";
        std::cout << "1. Aggiungi un nuovo elemento\n";
        std::cout << "2. Rimuovi un elemento\n";
        std::cout << "3. Condividi questa lista\n";
        std::cout << "4. Esci dalla lista\n";
        int choice = integerInput();
        switch (choice) {
            case 1: {
                list->addItem(std::make_shared<Item>());
                std::cout << "Elemento aggiunto con successo!\n";
                break;
            }
            case 2: {
                if (list->getItemCount()<1)
                    std::cout << "Non ci sono elementi da rimuovere\n";
                else {
                    std::cout << "Inserisci l'indice dell'elemento da rimuovere: \n";
                    const int index = integerInput();
                    if (index<1 || index>list->getItems().size())
                        std::cout << "Scelta non valida\n";
                    else {
                        list->removeItem(list->getItems()[index-1]);
                        std::cout << "Elemento rimosso con successo!\n";
                    }
                    break;
                }
            }
            case 3: {
                break;
            }
            case 4: {
                keepOpen = false;
                break;
            }
            default:
                std::cout << "Scelta non valida\n";
        }
    }
}