//
// Created by Rares on 30.04.2023.
//

#ifndef A7_RARES1707_1_DOGVALIDATOR_H
#define A7_RARES1707_1_DOGVALIDATOR_H
#include "Dog.h"
#include <utility>
#include <vector>


class DogException: public std::exception
{
private:
    std::vector <std::string> errors;
public:
    explicit DogException(std::vector <std::string> errorsRaised): errors(std::move(errorsRaised)){};
    std::vector <std::string> getErrorMessages() const {return errors;};

};


class DogValidator {
public:
    static void validate(const Dog& dog);
};


#endif //A7_RARES1707_1_DOGVALIDATOR_H
