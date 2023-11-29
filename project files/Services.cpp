#include "Services.h"
#include <iostream>
#include <cassert>
#include "TextFileRepository.h"
#include "DogValidator.h"
//Services::Services(const Repository &repository) {
//    this->repository = repository;
//}

Services::Services(const TextFileRepository &repositoryToBeUsed): repository(repositoryToBeUsed){}

bool Services::addDog(const std::string &dogName, const std::string &dogBreed, int dogAge,
                      const std::string &dogPhotograph) {
    DogValidator::validate(Dog(dogName, dogBreed, dogAge, dogPhotograph));
    return repository.addDog(Dog(dogName, dogBreed, dogAge, dogPhotograph));
}

bool Services::updateDog(const std::string &currentName, const std::string &newName, const std::string &newBreed,
                         int newAge, const std::string &newPhotograph) {
    return repository.updateDog(currentName, Dog(newName, newBreed, newAge, newPhotograph));
}

std::vector<Dog> &Services::getAllDogs() {
    return repository.getAllDogs();
}

/*void Services::getDogsOfThisBreed(std::vector<Dog> dogsOfChosenBreed, const std::string &breed) {
    auto listOfDogs = getAllDogs();

    for (auto &dog : listOfDogs)
    {
        if (dog.getBreed() == breed)
        {
            dogsOfChosenBreed.emplace_back(dog);
        }
    }
}*/

Dog& Services::getCurrentDogOfIteration(bool breedWasSpecified){return repository.getCurrentDog(breedWasSpecified);}

void Services::test_addDog() {
    TextFileRepository testRepo;
    Services testServices;
    Dog dog1{"Spot", "Husky", 15,"https://cdn.britannica.com/84/232784-050-1769B477/Siberian-Husky-dog.jpg"};
    Dog dog2{"Daisy", "Bichon", 13,"https://upload.wikimedia.org/wikipedia/commons/thumb/f/fa/AG_Cody.jpg/1200px-AG_Cody.jpg"};
    testServices.addDog("Spot", "Husky", 15,"https://cdn.britannica.com/84/232784-050-1769B477/Siberian-Husky-dog.jpg");
    testServices.addDog("Daisy", "Bichon", 13,"https://upload.wikimedia.org/wikipedia/commons/thumb/f/fa/AG_Cody.jpg/1200px-AG_Cody.jpg");
    assert(testServices.getAllDogs()[0].getName() == dog1.getName());
    assert(testServices.getAllDogs()[1].getName() == dog2.getName());
    assert(testServices.addDog("Spot", "Husky", 15,"1") == false);
}

void Services::test_removeDog() {
    TextFileRepository testRepo;
    Services testServices;
    testServices.addDog("Spot", "Husky", 15,"https://cdn.britannica.com/84/232784-050-1769B477/Siberian-Husky-dog.jpg");
    testServices.addDog("Daisy", "Bichon", 13,"https://upload.wikimedia.org/wikipedia/commons/thumb/f/fa/AG_Cody.jpg/1200px-AG_Cody.jpg");
    testServices.removeDog("Spot");
    assert(testServices.removeDog("Spot") == false);
    assert(testServices.getAllDogs()[0].getName() == "Daisy");
    testServices.removeDog("Daisy");
    assert(testServices.getAllDogs().empty());

}

void Services::test_updateDog() {
    TextFileRepository testRepo;
    Services testServices;
    testServices.addDog("Spot", "Husky", 15,"https://cdn.britannica.com/84/232784-050-1769B477/Siberian-Husky-dog.jpg");
    testServices.updateDog("Spot", "Daisy", "Bichon", 13,"https://upload.wikimedia.org/wikipedia/commons/thumb/f/fa/AG_Cody.jpg/1200px-AG_Cody.jpg");
    assert(testServices.getAllDogs()[0].getName() == "Daisy");
    assert(testServices.updateDog("Max", "a", "b", 3, "link") == false);
}

void Services::test_getAllDogs() {
    TextFileRepository testRepo;
    Services testServices;
    Dog dog1{"Spot", "Husky", 15,"https://cdn.britannica.com/84/232784-050-1769B477/Siberian-Husky-dog.jpg"};
    Dog dog2{"Daisy", "Bichon", 13,"https://upload.wikimedia.org/wikipedia/commons/thumb/f/fa/AG_Cody.jpg/1200px-AG_Cody.jpg"};
    testServices.addDog("Spot", "Husky", 15,"https://cdn.britannica.com/84/232784-050-1769B477/Siberian-Husky-dog.jpg");
    testServices.addDog("Daisy", "Bichon", 13,"https://upload.wikimedia.org/wikipedia/commons/thumb/f/fa/AG_Cody.jpg/1200px-AG_Cody.jpg");
    assert(testServices.getAllDogs().size() == 2);
    assert(testServices.getAllDogs()[0].getName() == dog1.getName());
    assert(testServices.getAllDogs()[1].getName() == dog2.getName());
}

void Services::test_iteratingThroughDogs() {
    TextFileRepository testRepo;
    Services testServices{testRepo};
    testServices.addDog("Spot", "Husky", 15,"https://cdn.britannica.com/84/232784-050-1769B477/Siberian-Husky-dog.jpg");
    testServices.addDog("Daisy", "Bichon", 13,"https://upload.wikimedia.org/wikipedia/commons/thumb/f/fa/AG_Cody.jpg/1200px-AG_Cody.jpg");
    testServices.addDog("Max", "Bichon", 9, "link");
    assert(testServices.getCurrentDogOfIteration(false).getName() == "Spot");
    assert(testServices.getCurrentDogOfIteration(false).getName() == "Daisy");
    assert(testServices.getCurrentDogOfIteration(false).getName() == "Max");
    assert(testServices.getCurrentDogOfIteration(false).getName() == "Spot");
    assert(testServices.getCurrentDogOfIteration(false).getName() == "Daisy");
    testServices.resetTheIterationThroughTheRepository();
    assert(testServices.getCurrentDogOfIteration(false).getName() == "Spot");
    testServices.prepareListOfDogsOfThisBreedAndOfAgeOrYounger("Bichon", 14);
    assert(testServices.getCurrentDogOfIteration(true).getName() == "Max");
    assert(testServices.getCurrentDogOfIteration(true).getName() == "Daisy");
}

void Services::test_adoptCurrentDog() {
    TextFileRepository testRepo;
    Services testServices = Services(testRepo);
    testServices.addDog("Spot", "Husky", 15,"https://cdn.britannica.com/84/232784-050-1769B477/Siberian-Husky-dog.jpg");
    testServices.addDog("Daisy", "Bichon", 13,"https://upload.wikimedia.org/wikipedia/commons/thumb/f/fa/AG_Cody.jpg/1200px-AG_Cody.jpg");

    testServices.getCurrentDogOfIteration(false);
    testServices.adoptCurrentDog(false);
    assert(testServices.getAdoptionList()[0].getName() == "Spot");

    testServices.getCurrentDogOfIteration(false);
    testServices.adoptCurrentDog(false);
    assert(testServices.getAdoptionList()[1].getName() == "Daisy");

    testServices.addDog("Spot", "Husky", 15,"https://cdn.britannica.com/84/232784-050-1769B477/Siberian-Husky-dog.jpg");
    testServices.addDog("Daisy", "Bichon", 13,"https://upload.wikimedia.org/wikipedia/commons/thumb/f/fa/AG_Cody.jpg/1200px-AG_Cody.jpg");
    testServices.addDog("Max", "Bichon", 9, "link");

    testServices.resetTheIterationThroughTheRepository();
    testServices.prepareListOfDogsOfThisBreedAndOfAgeOrYounger("Bichon", 15);

    testServices.getCurrentDogOfIteration(true);
    testServices.adoptCurrentDog(true);
    assert(testServices.getAdoptionList()[2].getName() == "Daisy");

    testServices.getCurrentDogOfIteration(true);
    testServices.adoptCurrentDog(true);
    assert(testServices.getAdoptionList()[3].getName() == "Max");
}

void Services::test_getAdoptionList() {
    TextFileRepository testRepo;
    Services *testServices = new Services(testRepo);
    testServices->addDog("Spot", "Husky", 15,"https://cdn.britannica.com/84/232784-050-1769B477/Siberian-Husky-dog.jpg");
    testServices->addDog("Daisy", "Bichon", 13,"https://upload.wikimedia.org/wikipedia/commons/thumb/f/fa/AG_Cody.jpg/1200px-AG_Cody.jpg");
    testServices->adoptCurrentDog(false);
    assert(testServices->getAdoptionList().size() == 1);
    testServices->adoptCurrentDog(false);
    assert(testServices->getAdoptionList().size() == 2);
}

void Services::test_services()
{
    test_updateDog();
    test_removeDog();
    test_getAllDogs();
    test_getAdoptionList();
    test_adoptCurrentDog();
    test_addDog();
    test_iteratingThroughDogs();
    //test_getDogsOfThisBreed();
}









