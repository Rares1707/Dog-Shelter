//
// Created by Rares on 29.04.2023.
//

#ifndef A7_RARES1707_1_FILEADOPTIONLIST_H
#define A7_RARES1707_1_FILEADOPTIONLIST_H
#include "AdoptionList.h"
#include <string>
class FileAdoptionList:
        public AdoptionList
{
protected:
    std::string fileName;

public:
    explicit FileAdoptionList(const std::string& fileToBeUsed): fileName(fileToBeUsed){};
    virtual void writeToFile()=0;
    virtual void displayAdoptionList()=0;

    virtual ~FileAdoptionList()=default;
};


#endif //A7_RARES1707_1_FILEADOPTIONLIST_H
