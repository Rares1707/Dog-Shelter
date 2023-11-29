//
// Created by Rares on 30.04.2023.
//

#include "DogValidator.h"

using namespace std;

void DogValidator::validate(const Dog &dog) {
    vector<string> errors;

    if (dog.getName().size() < 2)
        errors.emplace_back("The name is too short, it must have at least 2 characters\n");
    if (!isupper(dog.getName()[0]))
        errors.emplace_back("The name must start with an upper case letter\n");
    for(char character: dog.getName())
        if (!isalpha(character) && character != ' ')
        {
            errors.emplace_back("The name must only contain letters\n");
            break;
        }

    if (dog.getBreed().size() < 2)
        errors.emplace_back("The breed is too short, it must have at least 2 characters\n");
    if (!isupper(dog.getBreed()[0]))
        errors.emplace_back("The breed must start with an upper case letter\n");
    for(char character: dog.getBreed())
        if (!isalpha(character) && character != ' ')
        {
            errors.emplace_back("The breed must only contain letters\n");
            break;
        }

    if (dog.getAge() < 0)
        errors.emplace_back("The age must be at least 0\n");

    auto positionOfWWW = dog.getPhotograph().find("www");
    auto positionOfHTTP = dog.getPhotograph().find("http");

    if (positionOfHTTP != 0 && positionOfWWW != 0)
        errors.emplace_back("The link must start with 'www' or 'http'\n");

    if (!errors.empty())
        throw DogException(errors);
}
