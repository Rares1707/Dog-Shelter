//
// Created by Rares on 29.04.2023.
//

#ifndef A7_RARES1707_1_CSV_ADOPTIONLIST_H
#define A7_RARES1707_1_CSV_ADOPTIONLIST_H
#include "FileAdoptionList.h"

class CSV_AdoptionList:
        public FileAdoptionList
{
public:
    explicit CSV_AdoptionList(const std::string& fileToBeUsed): FileAdoptionList(fileToBeUsed) {};
    void writeToFile() override;
    void displayAdoptionList() override;
};


#endif //A7_RARES1707_1_CSV_ADOPTIONLIST_H
