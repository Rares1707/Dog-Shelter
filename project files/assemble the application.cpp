#include <iostream>
//#include "Ui.h"
#include "CSV_AdoptionList.h"
#include "HTML_AdoptionList.h"
#include "RepositoryExceptions.h"
#include <QApplication>
#include <QDebug>
#include <QtWidgets/QLabel>
#include "AdministratorGUI.h"
#include "SelectModeGUI.h"
#include "QtCharts/QChart"

using namespace std;

int main(int argc, char* argv[])
{
//    Services::test_services();
//    Dog::test_dog();

    const string CSV_FILE_PATH = "C:\\Users\\Rares\\CLionProjects\\a7-Rares1707-1\\adoptionList.csv";
    const string HTML_FILE_PATH = "C:\\Users\\Rares\\CLionProjects\\a7-Rares1707-1\\adoptionList.html";

//    FileAdoptionList *emptyAdoptionList;
//    TextFileRepository repository{"C:\\Users\\Rares\\CLionProjects\\a89-Rares1707\\listOfDogs.txt", emptyAdoptionList};
//    Services services = Services(repository);

    QApplication application(argc, argv);
    //QChart *chart = new QChart();
    //QLabel label("Hello world!");
    //label.show();
    // qDebug() << QT_VERSION_STR;
    SelectModeGUI selectModeGui;
    selectModeGui.show();
    //selectModeGui.hide();
    //AdministratorGUI gui(services);
    //gui.show();
    return application.exec();



//    cout << "What type of file would you like to use to store the adoption list (CSV/HTML)?";
//    string userInput;
//    FileAdoptionList *adoptionList;
//
//    while (true)
//    {
//        getline(cin, userInput);
//        if(userInput == "CSV")
//        {
//            adoptionList = new CSV_AdoptionList(CSV_FILE_PATH);
//            break;
//        }
//        else if (userInput == "HTML")
//        {
//            adoptionList = new HTML_AdoptionList(HTML_FILE_PATH);
//            break;
//        }
//        cout << "Wrong input, try again\n";
//    }
//    try
//    {
//        TextFileRepository repository{"C:\\Users\\Rares\\CLionProjects\\a7-Rares1707-1\\listOfDogs.txt", adoptionList};
//        Services services = Services(repository);
//        Ui ui = Ui(services);
//        cout << "Press 1 for administrator mode or 2 for user mode: ";
//        int chosenMode = 0;
//        while (chosenMode != 1 && chosenMode != 2)
//        {
//            chosenMode = Ui::readValidNumber();
//            if (chosenMode == 1) {
//                ui.enterAdministratorMode();
//            }
//            else if (chosenMode == 2) {
//                ui.enterUserMode();
//            }
//            else cout << "Enter a valid number";
//        }
//    }
//    catch (FileException& error)
//    {
//        cout << error.what() << "\nThe application will be closed\n";
//    }
//	return 0;
}