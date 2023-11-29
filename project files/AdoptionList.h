//
// Created by Rares on 29.04.2023.
//

#ifndef A7_RARES1707_1_ADOPTIONLIST_H
#define A7_RARES1707_1_ADOPTIONLIST_H

#include <vector>
#include "Dog.h"

class AdoptionList {
protected:
    std::vector<Dog> adoptedDogs;

public:
    void add(const Dog& dog){adoptedDogs.emplace_back(dog);}
    bool isEmpty(){return adoptedDogs.empty();};
    virtual ~AdoptionList()= default;
};


#endif //A7_RARES1707_1_ADOPTIONLIST_H
