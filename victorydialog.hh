/*
####################################################################
# Program description: "While revenge is served cold and vengeance #
#                       is served hot revengeance is often seen    #
#                       served with Cajun with a side of onion     #
#                       rings and often dumplings in the Orient."  #
#                       - urbandictionary                          #
#                                                                  #
# File: victorydialog.hh                                           #
# Description: Declares a class for the game ending dialog         #
#                                                                  #
# Author: Jani Niittymäki                                          #
####################################################################
*/
#ifndef VICTORYDIALOG_HH
#define VICTORYDIALOG_HH

#include <QDialog>
#include <vector>
/**
 * @class VictoryDialog
 * Class for handling the ending dialog
 */
namespace Ui {
class VictoryDialog;
}

class VictoryDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @param endresult: vector containing the game stats
     * @param victorytext: text telling if player won or lost
     * @param parent: parent widget of this VictoryDialog
     * Constructs a VictoryDialog
     */
    explicit VictoryDialog(std::vector<QString> endResult, QString victoryText,QWidget *parent = 0);
    /**
     * Destruct a VictoryDialog.
     */
    ~VictoryDialog();

private slots:
    /**
     * @brief on_okButton_clicked
     * Closes this dialog if ok button is pressed
     */
    void on_okButton_clicked();

private:
    // UI widgets
    Ui::VictoryDialog *ui;
};

#endif // VICTORYDIALOG_HH
