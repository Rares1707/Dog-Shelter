#pragma once
#include "Dog.h"
#include <vector>
#include <string>
#include "FileAdoptionList.h"

class TextFileRepository{
private:
    std::string fileName;
    std::vector<Dog> listOfDogs;
    std::vector<Dog> listOfDogsOfACertainBreed;
    std::vector<Dog> adoptionList;
    int indexOfCurrentDog = 0;
    FileAdoptionList* adoptedDogs;

public:
    TextFileRepository(){fileName="";}
    TextFileRepository(const std::string& file, FileAdoptionList*);
    void resetIndexOfCurrentDog(){indexOfCurrentDog = 0;}
    bool addDog(const Dog &dog);
    bool removeDog(const std::string&);
    bool updateDog(const std::string&, const Dog&);
    std::vector<Dog>& getAllDogs() {return this->listOfDogs;}
    std::vector<Dog>& getAdoptionList() {return this->adoptionList;}
    void getAllDogsFromTextFile();
    void saveAllDogsToTextFile();
    void findAndStoreDogsOfThisBreedAndOfAgeOrYounger(const std::string& string, int maximumAge);
    Dog& getCurrentDog(bool breedWasSpecified);
    void adoptCurrentDog(bool breedWasSpecified);
    void openAdoptionList(){adoptedDogs->displayAdoptionList();}
};



