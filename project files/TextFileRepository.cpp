#include "TextFileRepository.h"
#include <algorithm>
#include <fstream>
#include "RepositoryExceptions.h"
#include "QDebug"
using namespace std;

TextFileRepository::TextFileRepository(const string &file, FileAdoptionList* listOfAdoptedDogs):
    fileName{file}, adoptedDogs(listOfAdoptedDogs)
{
    getAllDogsFromTextFile();
}

bool TextFileRepository::addDog(const Dog &dog) {
    for (const auto& dogInList : listOfDogs)
    {
        if (dog.getName() == dogInList.getName())
        {
            throw DuplicateDogException();
        }
    }
    listOfDogs.push_back(dog);
    saveAllDogsToTextFile();
    return true;
}

bool TextFileRepository::removeDog(const std::string &nameOfDog) {
    auto initialSize = listOfDogs.size();
    auto iterator = std::remove_if(listOfDogs.begin(), listOfDogs.end(),[nameOfDog](auto dog)
    {
        return nameOfDog == dog.getName();
    });
    listOfDogs.resize(std::distance(listOfDogs.begin(),iterator));
    saveAllDogsToTextFile();
    if (listOfDogs.size() == initialSize)
    {
        throw DogDoesNotExistException();
    }
    return true;
}

void TextFileRepository::getAllDogsFromTextFile() {
    std::ifstream fin(fileName);
    if (!fin.is_open())
        throw FileException("File couldn't be opened!");

    Dog dog;
    while (fin>>dog)
    {
        listOfDogs.emplace_back(dog);
    }
    fin.close();
}

void TextFileRepository::saveAllDogsToTextFile()
{
    std::ofstream fout(fileName, std::ios::trunc);
    if (!fout.is_open())
        throw FileException("File couldn't be opened!");

    for (auto& dog: listOfDogs)
        fout<<dog<<'\n';
    fout.close();
}

bool TextFileRepository::updateDog(const std::string &currentName, const Dog& updatedDog)
{
    for(auto & dogInList: listOfDogs)
    {
        if (currentName == dogInList.getName())
        {
            dogInList = updatedDog;
            saveAllDogsToTextFile();
            return true;
        }
    }
    throw DogDoesNotExistException();
}

Dog& TextFileRepository::getCurrentDog(bool breedWasSpecified) {
    //doesn't work if there are no dogs
    if (!breedWasSpecified)
    {
        if (indexOfCurrentDog == listOfDogs.size() - 1)
        {
            indexOfCurrentDog = 0;
            return listOfDogs[listOfDogs.size() - 1];
        }
        else
        {
            indexOfCurrentDog++;
            return listOfDogs[indexOfCurrentDog - 1];
        }
    }
    else
    {
        if (indexOfCurrentDog == listOfDogsOfACertainBreed.size() - 1)
        {
            indexOfCurrentDog = 0;
            return listOfDogsOfACertainBreed[listOfDogsOfACertainBreed.size() - 1];
        }
        else
        {
            indexOfCurrentDog++;
            return listOfDogsOfACertainBreed[indexOfCurrentDog - 1];
        }
    }
}

void TextFileRepository::adoptCurrentDog(bool breedWasSpecified)
{
    if (!breedWasSpecified)
    {
        if (indexOfCurrentDog == 0)
        {
            adoptionList.emplace_back(listOfDogs[listOfDogs.size() - 1]);
            adoptedDogs->add(listOfDogs[listOfDogs.size() - 1]);
            removeDog(listOfDogs[listOfDogs.size() - 1].getName());
        }
        else
        {
            adoptionList.emplace_back(listOfDogs[indexOfCurrentDog - 1]);
            adoptedDogs->add(listOfDogs[indexOfCurrentDog - 1]);
            removeDog(listOfDogs[indexOfCurrentDog - 1].getName());
        }
    }
    else
    {
        if (indexOfCurrentDog == 0)
        {
            adoptionList.emplace_back(listOfDogsOfACertainBreed[listOfDogsOfACertainBreed.size() - 1]);
            adoptedDogs->add(listOfDogsOfACertainBreed[listOfDogsOfACertainBreed.size() - 1]);
            removeDog(listOfDogsOfACertainBreed[listOfDogsOfACertainBreed.size() - 1].getName());
        }
        else
        {
            adoptionList.emplace_back(listOfDogsOfACertainBreed[indexOfCurrentDog - 1]);
            adoptedDogs->add(listOfDogsOfACertainBreed[indexOfCurrentDog - 1]);
            removeDog(listOfDogsOfACertainBreed[indexOfCurrentDog - 1].getName());
        }
    }
    adoptedDogs->writeToFile();
}

void TextFileRepository::findAndStoreDogsOfThisBreedAndOfAgeOrYounger(const std::string &string, int maximumAge) {
    listOfDogsOfACertainBreed.clear();
    std::copy_if(listOfDogs.begin(), listOfDogs.end(),
                 std::back_inserter(listOfDogsOfACertainBreed),
                 [string, maximumAge](auto dog)
                 {return (dog.getBreed() == string || string.length() == 0) && dog.getAge() <= maximumAge;});
}


