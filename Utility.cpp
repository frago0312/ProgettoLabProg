//
// Created by franc on 25/09/2024.
//

#include "utility.h"
#include <iostream>
#include <limits>

void printSeparator(int length) {
    for (int i = 0; i < length; ++i) {
        std::cout << "-";
    }
    std::cout << std::endl;
}

int integerInput(const std::string &prompt) {
    int input;
    while (true) {
        std::cout << prompt;
        std::cin >> input;

        // Controlla se l'input è valido
        if (std::cin.fail()) {
            std::cin.clear(); // Resetta lo stato di errore di cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Scarta i caratteri rimanenti nel buffer
            std::cout << "Errore: inserisci un numero intero valido.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Scarta eventuali caratteri extra nel buffer
            return input;
        }
    }
}

std::string stringInput(const std::string &prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input); // Legge l'intera linea, inclusi spazi
    return input;
}
