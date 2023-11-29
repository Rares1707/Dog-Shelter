//
// Created by Rares on 16.05.2023.
//
#include "QHBoxLayout"
#include "QVBoxLayout"
#include "QFormLayout"
#include "qlabel.h"
#include "AdministratorGUI.h"
#include "QDebug"
#include <RepositoryExceptions.h>
#include "QMessageBox"

AdministratorGUI::AdministratorGUI(const Services &servicesToBeUsed, QWidget *parent):
        QWidget(parent), services(servicesToBeUsed)
{
    initialiseGUI();
    try
    {
        populateListOfDogs();
    }
    catch (FileException &error)
    {
        QMessageBox::information(this, "Error", error.what());
    }
    connectSignalsAndSlots();
}

void AdministratorGUI::initialiseGUI() {
    QHBoxLayout* layout = new QHBoxLayout(this);

    dogList = new QListWidget();
    layout->addWidget(dogList);

    QVBoxLayout* dogDataLayout = new QVBoxLayout();

    layout->addLayout(dogDataLayout);

    QFormLayout* dogInfoLayout = new QFormLayout();
    QLabel* nameLabel = new QLabel("&Name");
    nameEdit = new QLineEdit();
    nameLabel->setBuddy(nameEdit);

    QLabel* breedLabel = new QLabel("&Breed");
    breedEdit = new QLineEdit();
    breedLabel->setBuddy(breedEdit);

    QLabel* ageLabel = new QLabel("&Age");
    ageEdit = new QLineEdit();
    ageLabel->setBuddy(ageEdit);

    QLabel* photographLabel = new QLabel("&Photograph");
    photographEdit = new QLineEdit();
    photographLabel->setBuddy(photographEdit);

    QLabel* dogToBeUpdatedNameLabel = new QLabel("&The dog you wish to update");
    nameOfDogToBeUpdatedEdit = new QLineEdit();
    dogToBeUpdatedNameLabel->setBuddy(nameOfDogToBeUpdatedEdit);

    dogInfoLayout->addRow(nameLabel, nameEdit);
    dogInfoLayout->addRow(breedLabel, breedEdit);
    dogInfoLayout->addRow(ageLabel, ageEdit);
    dogInfoLayout->addRow(photographLabel, photographEdit);
    dogInfoLayout->addRow(dogToBeUpdatedNameLabel, nameOfDogToBeUpdatedEdit);

    dogDataLayout->addLayout(dogInfoLayout);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    addDogButton = new QPushButton("Add");
    removeDogButton = new QPushButton("Remove");
    updateDogButton = new QPushButton("Update");
    buttonsLayout->addWidget(addDogButton);
    buttonsLayout->addWidget(removeDogButton);
    buttonsLayout->addWidget(updateDogButton);

    dogDataLayout->addLayout(buttonsLayout);
}

void AdministratorGUI::populateListOfDogs() {
    dogList->clear();

    for (auto& dog: services.getAllDogs())
        dogList->addItem(QString::fromStdString(dog.toString()));

    dogList->setCurrentRow(0);
}

void AdministratorGUI::connectSignalsAndSlots() {
    QObject::connect(dogList, &QListWidget::itemSelectionChanged, this, &AdministratorGUI::listDogChanged);

    QObject::connect(addDogButton, &QPushButton::clicked, this,
                     [&](){
        try
        {
            services.addDog(nameEdit->text().toStdString(), breedEdit->text().toStdString(),
                            ageEdit->text().toInt(), photographEdit->text().toStdString());
            populateListOfDogs();
        }
        catch (FileException &error)
        {
            QMessageBox::information(this, "Error", error.what());
        }
        catch (RepositoryException &error)
        {
            QMessageBox::information(this, "Error", error.what());
        }
        dogList->setCurrentRow(services.getAllDogs().size() - 1);
    });

    QObject::connect(removeDogButton, &QPushButton::clicked, this, [&]()
    {
        try
        {
            services.removeDog(nameEdit->text().toStdString());
            populateListOfDogs();
        }
        catch (FileException &error)
        {
            QMessageBox::information(this, "Error", error.what());
        }
        catch (RepositoryException &error)
        {
            QMessageBox::information(this, "Error", error.what());
        }
    });

    QObject::connect(updateDogButton, &QPushButton::clicked, this, [&]()
    {
        try
        {
            services.updateDog(nameOfDogToBeUpdatedEdit->text().toStdString(), nameEdit->text().toStdString(),
                               breedEdit->text().toStdString(), ageEdit->text().toInt(),
                               photographEdit->text().toStdString());
            populateListOfDogs();
        }
        catch (FileException &error)
        {
            QMessageBox::information(this, "Error", error.what());
        }
        catch (RepositoryException &error)
        {
            QMessageBox::information(this, "Error", error.what());
        }
        nameOfDogToBeUpdatedEdit->clear();
    });
}

void AdministratorGUI::listDogChanged() {
    int index = getSelectedIndex();

    if(index < 0)
        return;

    Dog dog = services.getAllDogs()[index];
    nameEdit->setText(QString::fromStdString(dog.getName()));
    breedEdit->setText(QString::fromStdString(dog.getBreed()));
    ageEdit->setText(QString::fromStdString(std::to_string(dog.getAge())));
    photographEdit->setText(QString::fromStdString(dog.getPhotograph()));
}

int AdministratorGUI::getSelectedIndex() {
    int currentRow = dogList->currentRow();

    return currentRow;
}

