//
// Created by franc on 25/09/2024.
//
#include "UserInterface.h"

#include <algorithm>
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

            while (userChoice < 1 || userChoice > users.size()) {
                // Continua a chiedere finché non si sceglie un utente valido
                std::cout << "Seleziona un utente esistente:\n";
                for (size_t i = 0; i < users.size(); ++i) {
                    std::cout << i + 1 << ". " << users[i]->getName() << "\n";
                }
                std::cout << users.size() + 1 << ". Torna al menu principale\n";

                userChoice = integerInput();

                if (userChoice == users.size() + 1) {
                    // Torna al menu principale
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
    // Ottieni le liste associate all'utente
    auto lists = user->getShoppingLists();

    // Sincronizza le liste rimuovendo quelle non più valide
    lists.erase(std::remove_if(lists.begin(), lists.end(),
        [&user](const std::shared_ptr<ShoppingList>& list) {
            // Rimuovi le liste a cui l'utente non è più iscritto
            return !list || std::find(list->getObservers().begin(), list->getObservers().end(), user.get()) == list->getObservers().end();
        }),
        lists.end());

    if (lists.empty()) {
        std::cout << "Nessuna lista della spesa trovata.\n";
        printSeparator();
        return;
    }

    while (true) {
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
        std::cout << "1. Aggiungi un nuovo elemento/aumenta esistente\n";
        std::cout << "2. Segna come comprato/da comprare\n";
        std::cout << "3. Rimuovi un elemento\n";
        std::cout << "4. Condividi questa lista\n";
        std::cout << "5. Disiscriviti/elimina la lista\n";
        std::cout << "6. Esci dalla lista\n";
        int choice = integerInput();
        switch (choice) {
            case 1: {
                std::cout << "Inserisci il nome dell'oggetto:";
                std::string name = stringInput();
                bool itemFound = false;
                for (auto it: list->getItems()) {
                    if (it->getName() == name) {
                        itemFound = true;
                        std::cout << "Elemento gia' presente nella lista, vuoi aumentarne la quantita'?\n";
                        std::cout << "1. Si\n";
                        std::cout << "2. No\n";
                        int amountChoice = integerInput();
                        if (amountChoice == 1) {
                            int addQuantity = integerInput("Inserisci la quantita' da aggiungere: ");
                            it->increaseAmount(addQuantity);
                            std::cout << "Quantita' aumentata con successo!\n";
                        }
                        break;
                    }
                }
                if (!itemFound) {
                    int amount = integerInput("Inserisci la quantita': ");
                    ItemCategory category = ItemCategory::None;
                    std::cout << "Seleziona una categoria (1-7):\n";
                    std::cout << "1. Alimentari\n";
                    std::cout << "2. Abbigliamento\n";
                    std::cout << "3. Elettronica\n";
                    std::cout << "4. Casa\n";
                    std::cout << "5. Salute\n";
                    std::cout << "6. Animali domestici\n";
                    std::cout << "7. Extra\n";
                    int catChoice = integerInput();
                    switch (catChoice) {
                        case 1: category = ItemCategory::Alimentari;
                            break;
                        case 2: category = ItemCategory::Abbigliamento;
                            break;
                        case 3: category = ItemCategory::Elettronica;
                            break;
                        case 4: category = ItemCategory::Casa;
                            break;
                        case 5: category = ItemCategory::Salute;
                            break;
                        case 6: category = ItemCategory::AnimaliDomestici;
                            break;
                        case 7: category = ItemCategory::Extra;
                            break;
                        default: category = ItemCategory::None;
                    }
                    list->addItem(std::make_shared<Item>(name, amount, category));
                    std::cout << "Elemento aggiunto con successo!\n";
                    list->notifyObservers("un oggetto e' stato aggiunto alla lista " + list->getName());
                }
                break;
            }
            case 2: {
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
            case 3: {
                if (list->getItemQuantities() < 1)
                    std::cout << "Non ci sono elementi da rimuovere\n";
                else {
                    std::cout << "Inserisci l'indice dell'elemento da rimuovere: \n";
                    const int index = integerInput();
                    if (index < 1 || index > list->getItemCount())
                        std::cout << "Scelta non valida\n";
                    else {
                        list->removeItem(index - 1);
                        std::cout << "Elemento rimosso con successo!\n";
                    }
                }
                list->notifyObservers("un oggetto e' stato rimosso dalla lista " + list->getName());
                break;
            }
            case 4: {
                std::cout << "Inserisci il nome dell'utente: ";
                std::string username = stringInput();
                auto shareToUser = userManager->findUser(username);
                if (shareToUser) {
                    auto observers = list->getObservers();
                    bool alreadyShared = false;
                    for (auto observer: observers) {
                        if (observer == shareToUser.get()) {
                            alreadyShared = true;
                            break;
                        }
                    }
                    if (alreadyShared) {
                        std::cout << "Lista gia' condivisa con " << username << "!\n";
                    } else {
                        shareToUser->addShoppingList(list);
                        std::cout << "Lista condivisa con " << username << "!\n";
                    }
                } else {
                    std::cout << "Utente non trovato.\n";
                }
                break;
            }
            case 5: {
                unsubscribeFromList(user, list);
                keepOpen = false;
                break;
            }
            case 6: {
                std::cout << "Uscita dalla lista...\n";
                keepOpen = false;
                break;
            }
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
        // Rimuovi l'utente dalla lista
        user->removeShoppingList(list);

        // Verifica se la lista ha ancora degli osservatori
        if (list->isDeletable()) {
            std::cout << "Sei stato l'ultimo utente. La lista verrà eliminata automaticamente.\n";
        } else {
            std::cout << "Disiscrizione avvenuta con successo. Altri utenti stanno ancora usando questa lista.\n";
        }
        std::cout << "Esci dal menu' e rientra per vedere le modifiche"<<std::endl;
    } else {
        std::cout << "Disiscrizione annullata.\n";
    }
}
