#include <iostream>
#include <memory>

#include "Item.h"
#include "UserInterface.h"
#include "UserManager.h"

/* DOMANDE DA FARE AL PROF
 * - Scegliere l'elaborato su moodle?
 *
 * - Come posso gestire la condivisione di note fra più utenti? Devo inviare agli altri utenti delle notifiche?
 *   Se sì, come faccio a gestirle avendo un solo utente loggato per volta?
 *
 * - In che modo devo implementare il design pattern Observer? Così va bene o manca di funzionalità?
 *
 * - Ci sono altre funzionalità da aggiungere al programma? Se sì, quali?
 *
 * - Unit testing: quando iniziare a farlo?
 */


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

