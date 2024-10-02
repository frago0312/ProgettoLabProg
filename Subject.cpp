//
// Created by franc on 24/09/2024.
//

#include "Subject.h"

#include <bits/stl_algo.h>

void Subject::attach(std::shared_ptr<Observer> observer) {
    observers.push_back(observer);
}

void Subject::detach(std::shared_ptr<Observer> observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Subject::notifyObservers() {
    for (const auto& observer : observers) {
        observer->update();
    }
}