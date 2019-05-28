/*
####################################################################
# Program description: "While revenge is served cold and vengeance #
#                       is served hot revengeance is often seen    #
#                       served with Cajun with a side of onion     #
#                       rings and often dumplings in the Orient."  #
#                       - urbandictionary                          #
#                                                                  #
# File: victorydialog.cpp                                          #
# Description: Defines a class for the game victory dialog         #
#                                                                  #
# Author: Jani Niittymäki                                          #
####################################################################
*/
#include "victorydialog.hh"
#include "ui_victorydialog.h"
#include <memory>
#include <iostream>
VictoryDialog::VictoryDialog(std::vector<QString> endResult, QString victoryText, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VictoryDialog)
{
    ui->setupUi(this);
    // Set information for the UI elements
    ui->gameEndingInfo->setText(victoryText);
    ui->resultTable->setRowCount(5);
    ui->resultTable->setColumnCount(1);
    for(int i= 0;i<int(endResult.size());++i){
        ui->resultTable->setItem(i,1,new QTableWidgetItem(endResult.at(i)));
    }


}

VictoryDialog::~VictoryDialog(){
    delete ui;
}

void VictoryDialog::on_okButton_clicked(){
    close();

}
