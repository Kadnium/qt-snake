/*
####################################################################
# Program description: "While revenge is served cold and vengeance #
#                       is served hot revengeance is often seen    #
#                       served with Cajun with a side of onion     #
#                       rings and often dumplings in the Orient."  #
#                       - urbandictionary                          #
#                                                                  #
# File: difficulty.cpp                                             #
# Description: Defines a class for game difficulties               #
#                                                                  #
# Author: Jani Niittymäki                                          #
####################################################################
*/
#include "difficulty.hh"
#include "QString"


Difficulty::Difficulty(int foodAmount, int gridSizeX, int gridSizeY, int snakeSpeed,int snakeFastenerConst,QString difficulty){
    this->foodAmount_ = foodAmount;
    this->gridSizeX_ = gridSizeX;
    this->gridSizeY_ = gridSizeY;
    this->snakeSpeed_ = snakeSpeed;
    this->snakeFastenerConst_ = snakeFastenerConst;
    this->difficulty_=difficulty;

}

int Difficulty::foodAmount() const{
    return foodAmount_;
}

int Difficulty::gridSizeX() const{
    return gridSizeX_;
}

int Difficulty::snakeSpeed() const{
    return snakeSpeed_;
}


int Difficulty::gridSizeY() const{
    return gridSizeY_;
}


int Difficulty::snakeFastenerConst() const{
    return snakeFastenerConst_;
}

QString Difficulty::difficulty() const{
    return difficulty_;
}
