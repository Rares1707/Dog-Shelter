#include "Dog.h"
#include <string>
#include <cassert>
#include <sstream>
#include <iostream>

using namespace  std;

Dog::Dog() {
    this->name = "";
    this->breed = "";
    this->age = 0;
    this->photograph = "";
}

Dog::Dog(const std::string &dogName, const std::string &dogBreed, int dogAge, const std::string &dogPhotograph):
name{dogName}, breed{dogBreed}, age{dogAge}, photograph{dogPhotograph}
{
}

Dog::Dog(const Dog& dogToBeCopied) {
    name = dogToBeCopied.name;
    breed = dogToBeCopied.breed;
    age = dogToBeCopied.age;
    photograph = dogToBeCopied.photograph;
}

Dog::~Dog() = default;


std::string Dog::toString() const {
    return name + " " + breed + " " + to_string(age) + " " + photograph;
}

void Dog::test_dog()
{
    Dog *dog = new Dog("Max", "Bichon", 9, "link");
    assert(dog->getName() == "Max");
    assert(dog->getBreed() == "Bichon");
    assert(dog->getAge() == 9);
    assert(dog->getPhotograph() == "link");
    assert(dog->toString() == string("Max Bichon 9 link"));

    Dog *dog1 = dog;
    assert(dog1->getName() == "Max");
    assert(dog1->getBreed() == "Bichon");
    assert(dog1->getAge() == 9);
    assert(dog1->getPhotograph() == "link");

    dog1->setName("1");
    dog1->setBreed("2");
    dog1->setAge(3);
    dog1->setPhotograph("4");

    assert(dog1->getName() == "1");
    assert(dog1->getBreed() == "2");
    assert(dog1->getAge() == 3);
    assert(dog1->getPhotograph() == "4");

    Dog *dog3 = new Dog();
    assert(dog3->getName() == "");
    assert(dog3->getBreed() == "");
    assert(dog3->getAge() == 0);
    assert(dog3->getPhotograph() == "");
}

ostream &operator<<(ostream &outputStream, const Dog &dog)
{
    outputStream << dog.name << "," << dog.breed << "," << dog.age << "," << dog.photograph;
    return outputStream;
}

void strip(string stringToBeModified)
{
    while(stringToBeModified[0] == '\n' || stringToBeModified[0] == ',' || stringToBeModified[0] == ' ')
        stringToBeModified.erase(stringToBeModified.begin());

    while(stringToBeModified[stringToBeModified.length() - 1] == '\n' ||
          stringToBeModified[stringToBeModified.length() - 1] == ',' ||
          stringToBeModified[stringToBeModified.length() - 1] == ' ')
    {
        stringToBeModified.erase(stringToBeModified.end() - 1);
    }
}

istream &operator>>(istream &inputStream, Dog &dog)
{
    string line;
    std::getline(inputStream, line);
    if (line.empty() || line == "\n")
        return inputStream;

    std::stringstream dogAttributes{line};
    string name, breed, age, photograph;

    std::getline(dogAttributes, name, ',');
    strip(name);

    std::getline(dogAttributes, breed, ',');
    strip(breed);

    std::getline(dogAttributes, age, ',');
    strip(age);
    int ageAsInt = stoi(age);

    std::getline(dogAttributes, photograph, ',');
    strip(photograph);

    dog = Dog(name, breed, ageAsInt, photograph);
    return inputStream;
}




