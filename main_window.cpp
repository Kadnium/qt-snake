/*
####################################################################
# Program description: "While revenge is served cold and vengeance #
#                       is served hot revengeance is often seen    #
#                       served with Cajun with a side of onion     #
#                       rings and often dumplings in the Orient."  #
#                       - urbandictionary                          #
#                                                                  #
# File: main_window.cpp                                            #
# Description: Defines a class implementing a UI for the game.     #
#                                                                  #
# Author: Jani Niittymäki                                          #
####################################################################
*/

#include "main_window.hh"
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <iostream>
#include "settingdialog.hh"
#include <chrono>
#include <memory>



MainWindow::MainWindow(QWidget* parent):
    QMainWindow(parent) {
    // Set up mainwindow
    ui_.setupUi(this);
    ui_.graphicsView->setScene(&scene_);
    // Create settings window
    popUp_ = std::make_shared<SettingDialog>(this);
    // Connections for timers and settings window
    connect(&timer_, &QTimer::timeout, this, &MainWindow::moveSnake);
    connect(&gameTimer_, &QTimer::timeout, this, &MainWindow::updateCounter);
    connect(popUp_.get(), &SettingDialog::buttonPressed,this,&MainWindow::getData);

    ui_.restartButton->setEnabled(false);
    ui_.stopButton->setEnabled(false);
    ui_.foodCounter->setStyleSheet("background-color:darkRed");
    ui_.timerCounter->setStyleSheet("background-color:darkCyan");
    // Show settings window to the user
    popUp_->exec();



}

void MainWindow::updateCounter(){
    // Increment the current gametimer value by one
    ui_.timerCounter->display(ui_.timerCounter->intValue()+1);
}
void MainWindow::getData(std::shared_ptr<Difficulty> d){
    // If user pressed exit on the settings window,
    // close mainwindow as well
    if(d == nullptr){
        close();
    }
    // Set the difficulty values from the inputted difficulty
    areaWidth_ = d->gridSizeX();
    areaHeight_ = d->gridSizeY();
    foodAmount_ = d->foodAmount();
    snakeSpeed_ =d->snakeSpeed();
    gameDifficulty = d;

}
void MainWindow::keyPressEvent(QKeyEvent* event) {
    // If game is paused or not yet started,
    // dont do anything
    if(timer_.isActive()){
        QPointF oldDir = direction_;
        // Set directions according to the key pressed
        switch(event->key()){
        case Qt::Key_A:
            setDirection(-SNAKESIZE_,0);
            break;
        case Qt::Key_D:
            setDirection(SNAKESIZE_,0);
            break;
        case Qt::Key_W:
            setDirection(0,-SNAKESIZE_);
            break;
        case Qt::Key_S:
            setDirection(0,SNAKESIZE_);
            break;
        }
        // If user is trying to move snake back to same direction,
        // change direction back to the old
        if(!checkDirection()){
            direction_ =oldDir;
        }
    }



}
void MainWindow::setDirection(int x, int y){
    direction_.setX(x);
    direction_.setY(y);
    clicks_+=1;
}


bool MainWindow::checkDirection(){
    QPointF newHead = getNewHead()->scenePos();
    // If the destination square is the square before the head,
    // snake can't move
    if (snake_.size() > 1 && isInSquare(newHead)) {
        QPointF neck = snake_[snake_.size()-2]->scenePos();
        if (newHead == neck) {
            return false;

        }
    }
    return true;

}
void MainWindow::on_playButton_clicked() {
    // If user closed settings with x, open the settings dialog again
    if(gameDifficulty!= nullptr){
        // Seed for the food randomizer
        rng_.seed(std::chrono::system_clock::now().time_since_epoch().count());
        // Create head
        std::shared_ptr<BodyPart> head = std::make_shared<BodyPart>(HEADCOLOR_,SNAKESIZE_);
        scene_.addItem(head.get());
        head->setPos(1,1);
        snake_.push_back(head);
        // Create food
        const QRectF foodRect(0, 0, 1, 1);
        const QPen pen(Qt::white, 0);
        const QBrush brush(FOODCOLOR_);
        food_ = scene_.addEllipse(foodRect,pen,brush);
        moveFood();
        // Start timers, modify screen area and buttons
        adjustSceneArea();
        if(!timer_.isActive()){
            gameTimer_.start(1000);
            timer_.start(snakeSpeed_);
        }
        ui_.playButton->setEnabled(false);
        ui_.restartButton->setEnabled(true);
        ui_.stopButton->setEnabled(true);
        ui_.settingButton->setEnabled(false);
    }else{
        popUp_->exec();
    }
}

std::shared_ptr<BodyPart> MainWindow::getNewHead(){
    // Create a new head and set the location of it to
    // the current direction
    std::shared_ptr<BodyPart> newHead = std::make_shared<BodyPart>(HEADCOLOR_,SNAKESIZE_);
    QPointF tempPoint= getHead()->scenePos()+direction_;
    // If snake is going out of bounds, teleport it to
    // the other side
    if(tempPoint.x()>=areaWidth_){
        tempPoint.setX(0);
    }else if(tempPoint.x()<0){
        tempPoint.setX(areaWidth_-1);
    }else if(tempPoint.y()>=areaHeight_){
        tempPoint.setY(0);
    }else if(tempPoint.y()<0){
        tempPoint.setY(areaHeight_-1);
    }
    newHead->setPos(tempPoint.x(),tempPoint.y());
    return newHead;
}


void MainWindow::moveSnake() {
    std::shared_ptr<BodyPart> newHead = getNewHead();
    QPointF newHeadPoint = newHead->scenePos();
    // If the destination square contains anything but the "neck" or
    // the tail, the snake dies.
    if (snake_.size() > 1 && isInSquare(newHeadPoint)) {
        QPointF neck = snake_[snake_.size()-2]->scenePos();
        if (newHeadPoint == neck||newHeadPoint == getTail()->scenePos()){

        }else{
            handleEnding(false);
        }
    }
    // Set color for the bodypart and after that increment the greenvalue by
    // a defined step.
    changeBodyColor();

    // Move the snake.
    scene_.addItem(newHead.get());
    snake_.push_back(newHead);

    // New food must be placed somewhere once one gets eaten.
    // Also, the snake should stretch a little.
    if (newHead->scenePos() ==food_->scenePos()) {
        foodAmount_-=1;
        // If player has not collected all food yet,
        // calculate if snake will speed up after collecting the food
        if(foodAmount_ > 0){
            int oldInterval = timer_.interval();
            // 80 ms timer cycle is the fastest speed for the snake
            if(foodAmount_%gameDifficulty->snakeFastenerConst() == 0 && oldInterval >=80){
                timer_.stop();
                timer_.start(oldInterval-20);
            }
            moveFood();
        }else{
            // If player collected all food, game won
            ui_.foodCounter->display(foodAmount_);
            handleEnding(true);
        }
    } else {
        // If player moved to non food square, remove one piece from the tail
        scene_.removeItem(snake_.begin()->get());
        snake_.erase(snake_.begin());
    }
    if(snake_.size() >1){
        // Change color for the tail
        std::shared_ptr<BodyPart> tempEnd =getTail();
        tempEnd->setBrush(TAILCOLOR_);
    }


}
void MainWindow::changeBodyColor(){
    getHead()->setBrush(QColor::fromRgb(BODYCOLOR_.red(),greenValue_,BODYCOLOR_.blue()));
    greenValue_ +=greenValueIncrement_;
    if(greenValue_<=100){
        greenValueIncrement_ = 5;
    }else if(greenValue_>=250){
        greenValueIncrement_ = -5;
    }
}
void MainWindow::handleEnding(bool victory){
    timer_.stop();
    gameTimer_.stop();
    QString victoryText;
    if(victory){
        victoryText = "Voitit pelin!";
    }else{
        victoryText = "Hävisit pelin!";
    }
    // Endresults vector contains:
    // difficulty
    // food collected/total
    // time spent
    // number of clicks
    std::vector<QString> endResults;
    endResults.push_back(gameDifficulty->difficulty());
    QString foodString = QString::number(gameDifficulty->foodAmount()-foodAmount_)
            +"/"+QString::number(gameDifficulty->foodAmount());
    endResults.push_back(foodString);
    endResults.push_back(QString::number(ui_.timerCounter->intValue())+" s ");
    endResults.push_back(QString::number(clicks_));
    // Show ending screen to the user
    vicDial_ = std::make_shared<VictoryDialog>(endResults,victoryText,this);
    vicDial_->exec();
}

void MainWindow::moveFood() {
    // If snake has filled the whole grid, game won
    if(int(snake_.size()) == areaWidth_*areaHeight_){
        handleEnding(true);
        return;
    }
    // Randomize location for the food
    std::uniform_int_distribution<int> width_dist(0, (areaWidth_-1));
    std::uniform_int_distribution<int> height_dist(0, (areaHeight_-1));
    while (true) {
        int foodX = width_dist(rng_);
        int foodY = height_dist(rng_);
        food_->setX(foodX);
        food_->setY(foodY);
        if (!isInSquare(food_->scenePos())) {
            ui_.foodCounter->display(foodAmount_);
            //Snakeless square found, stop moving the food around.
            return;
        }
    }
}



bool MainWindow::isInSquare(const QPointF& square) {
    // Check if any of the parts stored in snake_ match the given point.
    for (const std::shared_ptr<BodyPart> part : snake_) {
        if (part->scenePos()== square) {
            return true;
        }
    }

    return false;
}

std::shared_ptr<BodyPart> MainWindow::getHead()  {
    // The snake's head is the last one in the vector.
    return snake_.back();
}

std::shared_ptr<BodyPart> MainWindow::getTail()  {
    // The snake's tail is the first one in the vector.
    return snake_.front();
}








void MainWindow::adjustSceneArea() {
    //Adjust the play area to grid size
    const QRectF area(0, 0, areaWidth_,areaHeight_ );
    scene_.setSceneRect(area);
    ui_.graphicsView->fitInView(area);
}

void MainWindow::on_stopButton_clicked(){
    //stop and start timers
    if(timer_.isActive()){
        ui_.stopButton->setDown(true);
        timer_.stop();
        gameTimer_.stop();
    }else{
        ui_.stopButton->setDown(false);
        timer_.start();
        gameTimer_.start();

    }

}

void MainWindow::on_restartButton_clicked(){
    // Stop timers and reset variables
    timer_.stop();
    gameTimer_.stop();
    direction_.setX(0);
    direction_.setY(0);
    snake_.clear();
    delete food_;
    ui_.playButton->setEnabled(true);
    ui_.restartButton->setEnabled(false);
    ui_.stopButton->setEnabled(false);
    ui_.settingButton->setEnabled(true);
    foodAmount_ = gameDifficulty->foodAmount();
    snakeSpeed_ = gameDifficulty->snakeSpeed();
    ui_.foodCounter->display(foodAmount_);
    ui_.timerCounter->display(0);

}



void MainWindow::on_settingButton_clicked(){
    // Show settings screen to the user
    popUp_->exec();
}
