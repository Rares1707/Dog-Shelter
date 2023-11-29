//
// Created by Rares on 21.05.2023.
//

#ifndef A89_RARES1707_USERMODEGUI_H
#define A89_RARES1707_USERMODEGUI_H

#include <QWidget>
#include "Services.h"

QT_BEGIN_NAMESPACE
namespace Ui { class UserModeGUI; }
QT_END_NAMESPACE

class UserModeGUI : public QWidget {
Q_OBJECT

public:
    explicit UserModeGUI(const Services& servicesToBeUsed,  QWidget *parent = nullptr);
    void populateAdoptionList();
    ~UserModeGUI() override;

private:
    Ui::UserModeGUI *ui;
    Services services;
    bool wantedBreedWasSpecified = false;
    void connectSignalsAndSlots();

    void showCurrentDogOfTheIteration(bool breedWasSpecified);
    void displayChart();
};


#endif //A89_RARES1707_USERMODEGUI_H
