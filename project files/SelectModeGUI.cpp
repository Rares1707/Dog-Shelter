//
// Created by Rares on 21.05.2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SelectModeGUI.h" resolved

#include "SelectModeGUI.h"
#include "ui_SelectModeGUI.h"
#include "CSV_AdoptionList.h"
#include "HTML_AdoptionList.h"
#include "Services.h"
#include "QMessageBox"
#include "RepositoryExceptions.h"

SelectModeGUI::SelectModeGUI(QWidget *parent) :
        QWidget(parent), ui(new Ui::SelectModeGUI) {
    ui->setupUi(this);
    connectSignalsAndSlots();
}

SelectModeGUI::~SelectModeGUI() {
    delete ui;
}

void SelectModeGUI::connectSignalsAndSlots() {
    QObject::connect(ui->chooseAdministratorModeButton, &QPushButton::clicked, this, [&](){
        administratorGui.show();
        this->hide();
    });

    QObject::connect(ui->chooseUserModeWithCSV_Button, &QPushButton::clicked, this, [&]()
    {
       adoptionList = new CSV_AdoptionList(CSV_FILE_PATH);
       repository = new TextFileRepository(REPOSITORY_FILE_PATH, adoptionList);
       services = new Services(*repository);
       userModeGui = new UserModeGUI(*services);
       try
       {
           userModeGui->populateAdoptionList();
       }
       catch (FileException &error)
       {
           QMessageBox::information(this, "Error", error.what());
       }
       userModeGui->show();
       this->hide();
    });

    QObject::connect(ui->chooseUserModeWithHTML_Button, &QPushButton::clicked, this, [&]()
    {
        adoptionList = new HTML_AdoptionList(HTML_FILE_PATH);
        repository = new TextFileRepository(REPOSITORY_FILE_PATH, adoptionList);
        services = new Services(*repository);
        userModeGui = new UserModeGUI(*services);
        userModeGui->populateAdoptionList();
        userModeGui->show();
        this->hide();
    });

}
