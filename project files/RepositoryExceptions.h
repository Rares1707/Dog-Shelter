//
// Created by Rares on 30.04.2023.
//

#ifndef A7_RARES1707_1_REPOSITORYEXCEPTIONS_H
#define A7_RARES1707_1_REPOSITORYEXCEPTIONS_H
#include <exception>
#include <string>

class FileException: public std::exception
{
protected:
    std::string message;

public:
    explicit FileException(const std::string& errorMessage): message(errorMessage){};
    virtual const char * what() {return message.c_str();}
};

class RepositoryException: public std::exception
{
protected:
    std::string message;

public:
    RepositoryException(): message("Repository exception"){};
    explicit RepositoryException(const std::string& errorMessage): message("Repository exception: " + errorMessage){};
    virtual const char *what(){return message.c_str();};
    ~RepositoryException()=default;
};

class DuplicateDogException: public RepositoryException
{
public:
    const char* what() override {return "There is another dog with the same name";}
};

class DogDoesNotExistException: public RepositoryException
{
public:
    const char * what() override {return "The dog does not exist";}
};

#endif //A7_RARES1707_1_REPOSITORYEXCEPTIONS_H
