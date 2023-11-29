//
// Created by Rares on 21.05.2023.
//

#ifndef A89_RARES1707_SELECTMODEGUI_H
#define A89_RARES1707_SELECTMODEGUI_H

#include <QWidget>
#include "AdministratorGUI.h"
#include "string"
#include "UserModeGUI.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SelectModeGUI; }
QT_END_NAMESPACE

class SelectModeGUI : public QWidget {
Q_OBJECT

public:
    explicit SelectModeGUI(QWidget *parent = nullptr);

    ~SelectModeGUI() override;

private:
    const std::string CSV_FILE_PATH = "C:\\Users\\Rares\\CLionProjects\\a89-Rares1707\\adoptionList.csv";
    const std::string HTML_FILE_PATH = "C:\\Users\\Rares\\CLionProjects\\a89-Rares1707\\adoptionList.html";
    const std::string REPOSITORY_FILE_PATH = "C:\\Users\\Rares\\CLionProjects\\a89-Rares1707\\listOfDogs.txt";
    Ui::SelectModeGUI *ui;
    FileAdoptionList *adoptionList;
    TextFileRepository *repository = new TextFileRepository{"C:\\Users\\Rares\\CLionProjects\\a89-Rares1707\\listOfDogs.txt", adoptionList};
    Services *services = new Services(*repository);
    AdministratorGUI administratorGui{*services};
    UserModeGUI *userModeGui;
    void connectSignalsAndSlots();
};


#endif //A89_RARES1707_SELECTMODEGUI_H
