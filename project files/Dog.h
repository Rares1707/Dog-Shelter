#pragma once
#include <string>
#include <iostream>


class Dog
{
private:
    std::string name;
    std::string breed;
    int age;
    std::string photograph;
public:
    friend std::ostream &operator<<(std::ostream &outputStream, const Dog &dog);
    friend std::istream &operator>>(std::istream &inputStream, Dog &dog);

public:
    Dog();
    Dog(const std::string &dogName, const std:: string &dogBreed, int dogAge, const std::string &dogPhotograph);
    Dog(const Dog&);
    ~Dog();

    std::string getName() const {return name;}
    void setName(const std::string& newName) {name = newName;}

    std::string getBreed() const {return breed;}
    void setBreed(const std::string& newBreed) {breed = newBreed;}

    int getAge() const {return  age;}
    void setAge(int newAge) {age = newAge;}

    std::string getPhotograph() const {return photograph;}
    void setPhotograph(const std::string& newPhotograph) {photograph = newPhotograph;}

    std::string toString() const;

    static void test_dog();

};

