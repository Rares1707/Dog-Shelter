//
// Created by Rares on 29.04.2023.
//

#include "CSV_AdoptionList.h"
#include <fstream>
#include <windows.h>
#include <shellapi.h>

void CSV_AdoptionList::writeToFile() {
    std::ofstream fout(fileName);
    if (!fout.is_open())
    {
        //throw exception;
        return;
    }
    for (const auto& dog: adoptedDogs)
        fout<<dog<<'\n';
    fout.close();
}

void CSV_AdoptionList::displayAdoptionList()
{
    const std::string excelPath="C:\\Program Files\\Microsoft Office\\root\\Office16\\EXCEL.EXE";
    ShellExecuteA(NULL, "open", excelPath.c_str(), fileName.c_str(), NULL, SW_MAXIMIZE);
}