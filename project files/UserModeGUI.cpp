//
// Created by Rares on 21.05.2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_UserModeGUI.h" resolved

#include "UserModeGUI.h"
#include "ui_UserModeGUI.h"
#include "QDebug"
#include "windows.h"
#include "RepositoryExceptions.h"
#include "QMessageBox"
#include <map>
#include <set>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QWindow>
#include "QtCharts/QChart"
#include "QtCharts/QChartView"
#include <QMainWindow>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

using namespace std;

UserModeGUI::UserModeGUI(const Services& servicesToBeUsed, QWidget *parent) :
        QWidget(parent), ui(new Ui::UserModeGUI), services(servicesToBeUsed) {
    ui->setupUi(this);
    connectSignalsAndSlots();
}

UserModeGUI::~UserModeGUI() {
    delete ui;
}

void UserModeGUI::populateAdoptionList() {
    ui->adoptionListWidget->clear();
    for (auto& dog: services.getAdoptionList())
    {
        ui->adoptionListWidget->addItem(QString::fromStdString(dog.toString()));
    }
    ui->adoptionListWidget->setCurrentRow(0);
}

void UserModeGUI::connectSignalsAndSlots() {
    QObject::connect(ui->startIteratingThroughDogsButton, &QPushButton::clicked, this, [&]() {
        if (ui->chooseBreedEdit->text() == "" || ui->chooseBreedEdit->text() == "\n")
            wantedBreedWasSpecified = false;
        else {
            wantedBreedWasSpecified = true;
            services.prepareListOfDogsOfThisBreedAndOfAgeOrYounger(ui->chooseBreedEdit->text().toStdString(), 99999);
        }
        try
        {
            services.resetTheIterationThroughTheRepository();
        }
        catch (FileException &error)
        {
            QMessageBox::information(this, "Error", error.what());
        }
        showCurrentDogOfTheIteration(wantedBreedWasSpecified);
    });

    QObject::connect(ui->nextDogButton, &QPushButton::clicked, this, [&]()
    {
        showCurrentDogOfTheIteration(wantedBreedWasSpecified);
    });

    QObject::connect(ui->adoptDogButton, &QPushButton::clicked, this, [&]()
    {
        services.adoptCurrentDog(wantedBreedWasSpecified);
        populateAdoptionList();
    });

    QObject::connect(ui->openAdoptionListButton, &QPushButton::clicked, this, [&]()
    {
        services.openAdoptionList();
    });

    QObject::connect(ui->displayChartButton, &QPushButton::clicked, this, [&]()
    {
        try
        {
            displayChart();
        }
        catch (FileException &error)
        {
            QMessageBox::information(this, "Error", error.what());
        }
    });
}

void UserModeGUI::showCurrentDogOfTheIteration(bool breedWasSpecified)
{
    Dog dog = services.getCurrentDogOfIteration(breedWasSpecified);
    ui->currentDogNameLabel->setText(QString::fromStdString(dog.getName()));
    ShellExecuteA(NULL, NULL, "chrome.exe", dog.getPhotograph().c_str(), NULL, SW_MAXIMIZE);
}

void UserModeGUI::displayChart() {
    vector<Dog> listOfDogs = services.getAllDogs();
    map<string, int> numberOfDogsOfThisBreed;
    set<string> breedsKnown;
    for (auto& dog: services.getAllDogs())
    {
        string dogBreed = dog.getBreed();
        if (breedsKnown.count(dogBreed) == 0)
        {
            breedsKnown.insert(dogBreed);
            numberOfDogsOfThisBreed[dogBreed] = 1;
        }
        else if (breedsKnown.count(dogBreed) > 0)
        {
            numberOfDogsOfThisBreed[dogBreed]++;
        }
    }

    QBarSeries *series = new QBarSeries();
    for (const string &breed: breedsKnown)
    {
        QBarSet *breedSet = new QBarSet(QString::fromStdString(breed));
        *breedSet << numberOfDogsOfThisBreed[breed];
        series->append(breedSet);
    }

    QChart *barChart = new QChart();
    barChart->addSeries(series);
    barChart->setTitle("Chart for dog breeds");

    barChart->legend()->setVisible(true);
    barChart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(barChart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(700, 300);

    chartView->show();
}

