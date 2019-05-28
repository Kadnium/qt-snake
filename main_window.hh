/*
####################################################################
# Program description: "While revenge is served cold and vengeance #
#                       is served hot revengeance is often seen    #
#                       served with Cajun with a side of onion     #
#                       rings and often dumplings in the Orient."  #
#                       - urbandictionary                          #
#                                                                  #
# File: main_window.hh                                             #
# Description: Declares a class implementing a UI for the game.    #
#                                                                  #
# Author: Jani Niittymäki                                          #
####################################################################
*/

#ifndef PRG2_SNAKE2_MAINWINDOW_HH
#define PRG2_SNAKE2_MAINWINDOW_HH

#include "ui_main_window.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QMainWindow>
#include <QTimer>
#include <memory>
#include <random>
#include "bodypart.hh"
#include "settingdialog.hh"
#include "victorydialog.hh"


/** @class MainWindow
 *  Implements the main window through which the game is played.
 */


class MainWindow: public QMainWindow {
    Q_OBJECT

public:

    /**
     * @param parent The parent widget of this MainWindow.
     * Construct a MainWindow.
     */
    explicit MainWindow(QWidget* parent = nullptr);

    /** Destruct a MainWindow.
     */
    ~MainWindow() override = default;

    /**
     * @brief keyPressEvent
     * @param event Contains data on pressed and released keys.
     * Change the Snake's bearing when certain keys get pressed.
     */
    void keyPressEvent(QKeyEvent* event) override;

private slots:

    /**
     * @brief on_playButton_clicked
     * Start the game.
     */
    void on_playButton_clicked();

    /**
     * @brief moveSnake
     * Move the Snake by a square and check for collisions.
     *
     * The game ends if the Snake itself gets in the way.
     * When a food gets eaten a point is gained and the Snake grows.
     */
    void moveSnake();

    /**
     * @brief on_stopButtonClicked
     * When stop button is clicked, game will pause
     */
    void on_stopButton_clicked();

    /**
     * @brief on_restartButton_clicked
     * When restart button is clicked, game will restart
     */
    void on_restartButton_clicked();

    /**
     * @brief getData
     * @param difficulty: contains difficulty settings for a game
     * When player has selected game settings from settingdialog,
     * mainwindow will get the settings through this function
     */
    void getData(std::shared_ptr<Difficulty> difficulty);

    /**
     * @brief updateCounter
     * Updates the game timer every second
     */
    void updateCounter();

    /**
     * @brief on_settingButton_clicked
     * If setting button is clicked, this function will open
     * the settings window.
     */
    void on_settingButton_clicked();

private:
    /**
     * @brief changeBodyColor
     * Changes the snake's body's color
     */
    void changeBodyColor();

    /**
     * @brief adjustSceneArea
     * Make the play field visible and fit it into the view.
     * Should be called every time the field's size changes.
     */
    void adjustSceneArea();

    /**
     * @brief getNewHead
     * @return pointer of the new head for the snake
     * Creates new head for the snake, called every time snake moves
     */
    std::shared_ptr<BodyPart> getNewHead();

    /**
     * @brief checkDirection
     * @return bool value telling if snake can move
     * Checks if player is trying to move snake back to the same direction
     * it came from.
     */
    bool checkDirection();

    /**
     * @brief getHead
     * @return pointer to the current snake head
     * Gets the snakes head and returns it as a pointer
     */
    std::shared_ptr<BodyPart> getHead() ;

    /**
     * @brief getTail
     * @return pointer to the tail of the snake
     * Gets the snakes tail and returns it as a pointer
     */
    std::shared_ptr<BodyPart> getTail() ;

    /**
     * @brief isInSquare
     * @param square: location to check
     * @return bool value telling if snake is in square
     * Checks if square is filled with snake
     */
    bool isInSquare(const QPointF& square) ;

    /**
     * @brief moveFood
     * Moves the food everytime snake eats it
     */
    void moveFood();

    /**
     * @brief handleEnding
     * @param victory: game won or lost
     * Creates ending text and stats according to bool value,
     * also opens the ending window
     */
    void handleEnding(bool victory);

    /**
     * @brief setDirection
     * @param x: x value
     * @param y: y value
     * Sets the direction for the snake when player clicks buttons
     * also counts the button clicks
     */
    void setDirection(int x, int y);
    // Keeps track of button clicks
    int clicks_ = 0;
    // Difficulty variables
    int areaHeight_= 10;
    int areaWidth_ = 10;
    int foodAmount_ = 0;
    int snakeSpeed_ = 1000;
    std::shared_ptr<Difficulty> gameDifficulty = nullptr;

    // Accesses the UI widgets
    Ui::MainWindow ui_;
    // The food item in the scene
    QGraphicsEllipseItem* food_ = nullptr;
    // Manages drawable objects
    QGraphicsScene scene_;
    // Triggers snake to move
    QTimer timer_;
    // Handles the game time
    QTimer gameTimer_;
    // Randomizes food locations
    std::default_random_engine rng_;
    // How big square the snake takes in the grid
    const double SNAKESIZE_ = 1;
    // What is the current direction of the snake
    QPointF direction_;
    // Stores the parts for the snake
    std::vector<std::shared_ptr<BodyPart>> snake_;
    // Setting and victorywindows
    std::shared_ptr<SettingDialog> popUp_;
    std::shared_ptr<VictoryDialog> vicDial_;

    // Colors for rectangles
    const QColor FOODCOLOR_ = Qt::red;
    const QColor TAILCOLOR_ = Qt::black;
    const QColor HEADCOLOR_ = Qt::gray;
    const QColor BODYCOLOR_ = Qt::darkGreen;
    int greenValue_ = BODYCOLOR_.green();
    // Changes the green rgb value by 5 every time
    int greenValueIncrement_= -5;




};


#endif  // PRG2_SNAKE2_MAINWINDOW_HH
