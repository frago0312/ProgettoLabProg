#include <iostream>
#include <memory>

#include "Item.h"
#include "UserInterface.h"
#include "UserManager.h"


int main()
{
    // Crea un'istanza di UserManager usando std::unique_ptr
    std::unique_ptr<UserManager> userManager(new UserManager());

    // Crea l'interfaccia utente, passandole il puntatore unico a UserManager
    UserInterface userInterface(std::move(userManager));

    while (true) {
        // Seleziona o crea un utente. Restituisce nullptr se l'utente vuole uscire dal programma
        std::shared_ptr<User> currentUser = userInterface.userSelection();
        if (!currentUser) {
            break;
        }

        // Esegue il main menu della gestione delle liste. Restituisce true se l'utente vuole selezionare un altro utente e false se vuole uscire dal programma.
        bool restartUserSelection = userInterface.mainMenu(currentUser);

        // Controllo dell'uscita dal programma. Se arriva true il programma si ferma, altrimenti torna alla selezione utenti.
        if (!restartUserSelection) {
            break;
        }
    }
    return 0;
}

