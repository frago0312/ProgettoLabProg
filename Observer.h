//
// Created by franc on 24/09/2024.
//

#ifndef OBSERVER_H
#define OBSERVER_H


class Observer {
public:
    virtual void update(const std::string& message) = 0;
    virtual ~Observer() = default;
};


#endif //OBSERVER_H
