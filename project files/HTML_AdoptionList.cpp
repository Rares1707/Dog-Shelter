//
// Created by Rares on 30.04.2023.
//

#include "HTML_AdoptionList.h"
#include <windows.h>
#include <shellapi.h>
#include <fstream>

using namespace std;
void HTML_AdoptionList::writeToFile() {
    ofstream fout(fileName);
    if (!fout.is_open())
    {
        //throw exception
        return;
    }
    fout << "<!DOCTYPE html>" << '\n';
    fout << "<html>" << '\n';
    fout << "<head>" << '\n';
    fout << '\t' << "<title>" << "Adoption list " << "</title>" << '\n';
    fout << "</head>" << '\n';
    fout << "<body>" << '\n';
    fout << "<table border=\"1\">" << '\n';

    fout << "\t<tr>" << '\n';
    fout << "\t\t<td>" << "Name" << "</td>" << '\n';
    fout << "\t\t<td>" << "Breed" << "</td>" << '\n';
    fout << "\t\t<td>" << "Age" << "</td>" << '\n';
    fout << "\t\t<td>" << "Photograph" << "</td>" << '\n';
    fout << "\t</tr>" << '\n';

    for (auto& dog: adoptedDogs)
    {
        fout << "\t<tr>" << '\n';
        fout << "\t\t<td>" << dog.getName() << "</td>" << '\n';
        fout << "\t\t<td>" << dog.getBreed() << "</td>" << '\n';
        fout << "\t\t<td>" << dog.getAge() << "</td>" << '\n';
        fout << "\t\t<td><a href=\"" << dog.getPhotograph() << "\">Link</a></td>" << '\n';
        fout << "\t</tr>" << '\n';
    }

    fout << "</table>\n";
    fout << "</body>\n";
    fout << "</html>\n";
    fout.close();
}

void HTML_AdoptionList::displayAdoptionList() {
    ShellExecuteA(NULL, NULL, "chrome.exe", fileName.c_str(), NULL, SW_SHOWMAXIMIZED);
}
