//
// Created by franc on 24/09/2024.
//

#ifndef SUBJECT_H
#define SUBJECT_H
#include <memory>
#include <vector>

#include "Observer.h"


class Subject {
public:
    virtual void attach(Observer* observer)=0;
    virtual void detach(Observer* observer)=0;
    virtual void notifyObservers()=0;
    virtual ~Subject() = default;
};


#endif //SUBJECT_H
