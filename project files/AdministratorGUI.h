//
// Created by Rares on 16.05.2023.
//

#ifndef A89_RARES1707_ADMINISTRATORGUI_H
#define A89_RARES1707_ADMINISTRATORGUI_H
#include "Services.h"
#include "QListWidget"
#include "QLineEdit"
#include "QPushButton"
#include "qwidget.h"

class AdministratorGUI: public QWidget{
    Q_OBJECT

private:
    Services services;

public:
    AdministratorGUI(const Services& servicesToBeUsed, QWidget* parent = 0);

    void initialiseGUI();

private:
    QListWidget* dogList;
    QLineEdit* nameEdit;
    QLineEdit* breedEdit;
    QLineEdit* ageEdit;
    QLineEdit* photographEdit;
    QLineEdit* nameOfDogToBeUpdatedEdit;
    QPushButton *addDogButton;
    QPushButton *removeDogButton;
    QPushButton *updateDogButton;

    void populateListOfDogs();
    void connectSignalsAndSlots();

    void listDogChanged();
    int getSelectedIndex();

    signals:
    void mySignal();
};


#endif //A89_RARES1707_ADMINISTRATORGUI_H
