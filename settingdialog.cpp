/*
####################################################################
# Program description: "While revenge is served cold and vengeance #
#                       is served hot revengeance is often seen    #
#                       served with Cajun with a side of onion     #
#                       rings and often dumplings in the Orient."  #
#                       - urbandictionary                          #
#                                                                  #
# File: settingdialog.cpp                                          #
# Description: Defines a class for the game settings dialog        #
#                                                                  #
# Author: Jani Niittymäki                                          #
####################################################################
*/
#include "settingdialog.hh"
#include "ui_settingdialog.h"
#include "memory"
SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
    // Add available difficulties to the drop down menu
    ui->difficultyBox->addItem(DIFFICULTY_EASY_);
    ui->difficultyBox->addItem(DIFFICULTY_NORMAL_);
    ui->difficultyBox->addItem(DIFFICULTY_HARD_);
    // Connect sliders to the boxes and vice versa
    connect(ui->heightSlider,&QSlider::valueChanged,ui->heightValueBox,&QSpinBox::setValue);
    connect(ui->heightValueBox,qOverload<int>(&QSpinBox::valueChanged),ui->heightSlider,&QSlider::setValue);
    connect(ui->widthSlider,&QSlider::valueChanged,ui->widthValueBox,&QSpinBox::setValue);
    connect(ui->widthValueBox,qOverload<int>(&QSpinBox::valueChanged),ui->widthSlider,&QSlider::setValue);

}

SettingDialog::~SettingDialog()
{
    delete ui;
}


void SettingDialog::on_difficultyBox_activated(const QString &arg1){
    // Set difficulty according to the drop down menu
    gameDifficulty_ = difficulties_[arg1];
    // Change UI elements from the difficulty values
    ui->widthSlider->setValue(gameDifficulty_->gridSizeX());
    ui->heightSlider->setValue(gameDifficulty_->gridSizeY());
    ui->foodAmountLabel->setText(QString::number(gameDifficulty_->foodAmount()));
}



void SettingDialog::on_okButton_clicked(){
    // Player has to select a difficulty to proceed
    if(gameDifficulty_ == nullptr){
        ui->errorLabel->setText("Valitse vaikeustaso!");
    }else{
        emit buttonPressed(std::make_shared<Difficulty>(gameDifficulty_->foodAmount(),ui->widthSlider->value(),
                                                        ui->heightSlider->value(),gameDifficulty_->snakeSpeed(),
                                                        gameDifficulty_->snakeFastenerConst(),gameDifficulty_->difficulty()));
        close();
    }


}

void SettingDialog::on_exitButton_clicked(){
    emit buttonPressed(nullptr);
    close();
}
