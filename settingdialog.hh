/*
####################################################################
# Program description: "While revenge is served cold and vengeance #
#                       is served hot revengeance is often seen    #
#                       served with Cajun with a side of onion     #
#                       rings and often dumplings in the Orient."  #
#                       - urbandictionary                          #
#                                                                  #
# File: settingdialog.hh                                           #
# Description: Declares a class for the game settings dialog       #
#                                                                  #
# Author: Jani Niittymäki                                          #
####################################################################
*/
#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <difficulty.hh>
#include <map>
#include <string>
#include <memory>

/**
 * @class SettingDialog
 * Class for handling the settings dialog
 */
namespace Ui {

class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @param parent The parent widget of this SettingsDialog.
     * Construct a SettingsDialog.
     */
    explicit SettingDialog(QWidget *parent = 0);

    /**
     * Destruct a SettingsDialog.
     */
    ~SettingDialog();

private slots:

    /**
     * @brief on_difficultyBox_activated
     * @param arg1: value of the selection from the dropdown menu
     * If value is selected from the drop down menu, pass it to this function.
     * Sets difficulty from the selection and modifies the sliders
     * according to the difficulty
     */
    void on_difficultyBox_activated(const QString &arg1);

    /**
     * @brief on_okButton_clicked
     * If player has selected the difficulty, emits a buttonPressed signal
     * with the difficulty selected and close the window.
     * If difficulty not selected, tell the user
     */
    void on_okButton_clicked();

    /**
     * @brief on_exitButton_clicked
     * Emits a buttonPressed signal with nullptr,
     * closes settings and mainwindow
     */
    void on_exitButton_clicked();

signals:

    /**
     * @brief buttonPressed
     * @param difficulty: contains difficulty values
     * Sends signal containing difficulty to mainwindow
     */
    void buttonPressed(std::shared_ptr<Difficulty> difficulty);
private:
    // UI widgets
    Ui::SettingDialog *ui;
    // Difficulties
    const QString DIFFICULTY_EASY_ = "Helppo";
    const QString DIFFICULTY_NORMAL_ = "Normaali";
    const QString DIFFICULTY_HARD_ = "Vaikea";
    // Current difficulty selected
    std::shared_ptr<Difficulty> gameDifficulty_ = nullptr;
    // Map of available difficulties
    std::map<QString,std::shared_ptr<Difficulty>> difficulties_ = {
        {DIFFICULTY_EASY_,std::make_shared<Difficulty>(10,10,5,1000,2,DIFFICULTY_EASY_)},
        {DIFFICULTY_NORMAL_,std::make_shared<Difficulty>(30,20,15,500,3,DIFFICULTY_NORMAL_)},
        {DIFFICULTY_HARD_,std::make_shared<Difficulty>(60,30,15,300,3,DIFFICULTY_HARD_)},
    };

};

#endif // SETTINGDIALOG_H
