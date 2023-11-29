#pragma once
#include "Dog.h"
//#include "Repository.h"
#include "TextFileRepository.h"

class Services
{
private:
    TextFileRepository repository;

public:
    Services()=default;
    //explicit Services(const Repository& repository);
    explicit Services(const TextFileRepository &repository);
    void resetTheIterationThroughTheRepository(){repository.resetIndexOfCurrentDog();}
    Dog& getCurrentDogOfIteration(bool breedWasSpecified);
    bool addDog(const std::string &dogName, const std::string &dogBreed, int dogAge,
                          const std::string &dogPhotograph);
    void prepareListOfDogsOfThisBreedAndOfAgeOrYounger(const std::string &breed, int maximumAge){
        repository.findAndStoreDogsOfThisBreedAndOfAgeOrYounger(breed, maximumAge);}
    bool removeDog(const std::string &dogName) {return repository.removeDog(dogName);}

    bool updateDog(const std::string &currentName, const std::string &newName, const std::string &newBreed,
                   int newAge, const std::string &newPhotograph);

    std::vector<Dog>& getAllDogs();
    //void getDogsOfThisBreed(std::vector<Dog>, const std::string&);
    std::vector<Dog>& getAdoptionList(){return repository.getAdoptionList();}
    void adoptCurrentDog(bool breedWasSpecified){repository.adoptCurrentDog(breedWasSpecified);}
    void openAdoptionList(){repository.openAdoptionList();}

    static void test_addDog();
    static void test_removeDog();
    static void test_updateDog();
    static void test_getAllDogs();
    static void test_iteratingThroughDogs();
    static void test_adoptCurrentDog();
    static void test_getAdoptionList();
    //static void test_getDogsOfThisBreed();

    static void test_services();
};

