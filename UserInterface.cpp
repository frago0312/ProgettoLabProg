//
// Created by franc on 25/09/2024.
//
#include "UserInterface.h"

#include <algorithm>
#include <iostream>
#include <limits>

#include "Utility.h"

//Classe che si occupa di gestire la parte "grafica" dell'applicazione
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
                continue;
            }

            int userChoice = -1;
            while (userChoice < 1 || userChoice > users.size()) {
                // Continua a chiedere finché non si sceglie un utente valido
                std::cout << "Seleziona un utente esistente:\n";
                for (size_t i = 0; i < users.size(); ++i) {
                    std::cout << i + 1 << ". " << users[i]->getName() << "\n";
                }
                std::cout << users.size() + 1 << ". Torna al menu principale\n";

                userChoice = integerInput();

                if (userChoice == users.size() + 1) {
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
            //Crea un nuovo utente
            std::cout << "Inserisci il nome del nuovo utente: ";
            std::string newName = stringInput();
            userManager->addUser(newName);
            std::cout << "Utente " << newName << " creato con successo!\n";
            printSeparator();
        } else if (choice == 3) {
            //Uscita dal programma
            std::cout << "Uscita dal programma...\n";
            return nullptr;
        } else {
            //Fa riprovare finché la scelta non è valida
            std::cout << "Opzione non valida. Riprova.\n";
            printSeparator();
        }
    }
    return selectedUser;    //Restituisce l'utente selezionato
}

// Funzione per il menu principale dell'applicazione, relativo all'utente selezionato sopra
bool UserInterface::mainMenu(std::shared_ptr<User> user) {
    while (true) {
        std::cout << "Benvenuto " << user->getName() << "!\n";
        std::cout << "Seleziona un'opzione:\n";
        std::cout << "1. Visualizza le tue liste della spesa\n";
        std::cout << "2. Crea una nuova lista della spesa\n";
        std::cout << "3. Cambia utente\n";
        std::cout << "4. Esci dal programma\n";

        int choice = integerInput();
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
                // Fa riprovare finché la scelta non è valida
                std::cout << "Opzione non valida. Riprova.\n";
                break;
            }
        }
    }
}


// Funzione per visualizzare le liste della spesa dell'utente
void UserInterface::displayShoppingLists(std::shared_ptr<User> user) {
    auto lists = user->getShoppingLists();

    // Sincronizza le liste rimuovendo quelle non più valide
    lists.erase(std::remove_if(lists.begin(), lists.end(),
        [&user](const std::shared_ptr<ShoppingList>& list) {
            return !list || std::find(list->getObservers().begin(), list->getObservers().end(), user) == list->getObservers().end();
        }),
        lists.end());

    if (lists.empty()) {
        std::cout << "Nessuna lista della spesa trovata.\n";
        printSeparator();
        return;
    }

    while (true) {
        //Menù di selezione della lista su cui l'utente vuole lavorare
        std::cout << "Ecco le tue liste della spesa, scegli quale vuoi aprire: \n";
        for (size_t i = 0; i < lists.size(); ++i) {
            std::cout << i + 1 << ". " << lists[i]->getName() << ":\t" << lists[i]->getItemCount() << " oggetti\n";
        }
        std::cout << lists.size() + 1 << ". Torna al menu principale\n";

        int choice = integerInput();

        if (choice >= 1 && choice <= lists.size()) {
            // Apri la lista selezionata
            openList(lists[choice - 1], user);
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
    std::cout << "Lista " << newList->getName() << " creata con successo!\n";
    printSeparator();
}

// Funzione per visualizzare una lista della spesa
void UserInterface::openList(std::shared_ptr<ShoppingList> &list, std::shared_ptr<User> user) {
    bool keepOpen = true;
    while (keepOpen) {
        int i = 1;
        std::cout << "Lista della spesa: " << list->getName() << "\n";
        for (const auto &item: list->getItems()) {
            std::string status = item->isBought() ? "[x]" : "[ ]";
            std::cout << i << ". " << status << " " << item->getName()
                      << ":\t\t" << item->getAmount() << " unita'\n";
            ++i;
        }
        std::cout << "\nScegli un'opzione:\n";
        std::cout << "1. Aggiungi un nuovo elemento\n";
        std::cout << "2. Modifica la quantita' di un elemento\n";
        std::cout << "3. Segna come comprato/da comprare\n";
        std::cout << "4. Rimuovi un elemento\n";
        std::cout << "5. Condividi questa lista\n";
        std::cout << "6. Disiscriviti/elimina la lista\n";
        std::cout << "7. Esci dalla lista\n";
        int choice = integerInput();
        switch (choice) {
            case 1: {
                std::cout << "Inserisci il nome dell'oggetto:";
                std::string name = stringInput();
                std::cout << "Inserisci la quantita': ";
                int amount = 0;
                while (amount < 1) {
                    amount = integerInput();
                    if (amount < 1)
                        std::cout << "La quantita' deve essere almeno 1\nInserisci la quantita': ";
                }
                ItemCategory category = ItemCategory::None;
                std::cout << "Seleziona una categoria (1-7):\n";
                std::cout << "1. Alimentari\n2. Abbigliamento\n3. Elettronica\n4. Casa\n5. Salute\n6. Animali domestici\n7. Extra\n";
                int catChoice = integerInput();
                switch (catChoice) {
                    case 1: category = ItemCategory::Alimentari; break;
                    case 2: category = ItemCategory::Abbigliamento; break;
                    case 3: category = ItemCategory::Elettronica; break;
                    case 4: category = ItemCategory::Casa; break;
                    case 5: category = ItemCategory::Salute; break;
                    case 6: category = ItemCategory::AnimaliDomestici; break;
                    case 7: category = ItemCategory::Extra; break;
                    default: category = ItemCategory::None;
                }
                list->addItem(std::make_shared<Item>(name, amount, category));
                std::cout << "Elemento aggiunto con successo!\n";
                list->notifyObservers("un oggetto e' stato aggiunto alla lista " + list->getName());
                break;
            }
            case 2: {
                std::cout << "Inserisci l'indice dell'oggetto da modificare:";
                int index = integerInput();
                if (index < 1 || index > list->getItemCount()) {
                    std::cout << "Indice non valido.\n";
                } else {
                    auto item = list->getItemAt(index - 1);
                    if (item) {
                        int addQuantity = integerInput("Inserisci la quantita' da aggiungere o togliere: ");
                        item->increaseAmount(addQuantity);
                        std::cout << "Quantita' cambiata con successo!\n";
                    } else {
                        std::cout << "Errore: elemento non trovato.\n";
                    }
                }
                break;
            }
            case 3: {
                // Logica per segnare un elemento come comprato o da comprare
                if (list->getItemQuantities() < 1)
                    std::cout << "Non ci sono elementi da comprare\n";
                else {
                    std::cout << "Inserisci l'indice dell'elemento da comprare: \n";
                    const int index = integerInput();
                    if (index < 1 || index > list->getItemCount())
                        std::cout << "Scelta non valida\n";
                    else {
                        auto item = list->getItemAt(index - 1);
                        if (item) {
                            item->changeBought();
                            std::cout << "Elemento aggiornato.\n";
                        } else {
                            std::cout << "Errore: elemento non trovato.\n";
                        }
                    }
                }
                list->notifyObservers("lo stato di un oggetto e' stato modificato nella lista " + list->getName());
                break;
            }
            case 4:
                // Logica per rimuovere un elemento dalla lista
                break;
            case 5:
                // Logica per condividere la lista
                break;
            case 6:
                unsubscribeFromList(user, list);
                keepOpen = false;
                break;
            case 7:
                std::cout << "Uscita dalla lista...\n";
                keepOpen = false;
                break;
            default:
                std::cout << "Scelta non valida\n";
        }
    }
}

void UserInterface::unsubscribeFromList(std::shared_ptr<User> user, std::shared_ptr<ShoppingList> list) {
    if (!user || !list) return;

    std::cout << "Vuoi davvero disiscriverti dalla lista? Se sei l'ultimo utente, la lista verra' eliminata.\n";
    std::cout << "1. Si\n2. No\n";

    int choice = integerInput();
    if (choice == 1) {
        // Rimozione dell'utente dalla lista
        user->removeShoppingList(list);

        // Verifica se la lista ha ancora degli osservatori e comunica all'utente le conseguenze
        if (list->isDeletable()) {
            std::cout << "Sei stato l'ultimo utente. La lista verra' eliminata automaticamente.\n";
        } else {
            std::cout << "Disiscrizione avvenuta con successo. Altri utenti stanno ancora usando questa lista.\n";
        }
        std::cout << "Esci dal menu' e rientra per vedere le modifiche"<<std::endl;
    } else {
        std::cout << "Disiscrizione annullata.\n";
    }
}
