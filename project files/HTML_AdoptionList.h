//
// Created by Rares on 30.04.2023.
//

#ifndef A7_RARES1707_1_HTML_ADOPTIONLIST_H
#define A7_RARES1707_1_HTML_ADOPTIONLIST_H

#include "FileAdoptionList.h"
#include <string>

class HTML_AdoptionList:
        public FileAdoptionList
{
public:
    explicit HTML_AdoptionList(const std::string& fileName): FileAdoptionList(fileName){};
    void writeToFile() override;
    void displayAdoptionList() override;
};


#endif //A7_RARES1707_1_HTML_ADOPTIONLIST_H
