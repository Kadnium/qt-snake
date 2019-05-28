/*
####################################################################
# Program description: "While revenge is served cold and vengeance #
#                       is served hot revengeance is often seen    #
#                       served with Cajun with a side of onion     #
#                       rings and often dumplings in the Orient."  #
#                       - urbandictionary                          #
#                                                                  #
# File: difficulty.hh                                              #
# Description: Declares a class for game difficulties              #
#                                                                  #
# Author: Jani Niittymäki                                          #
####################################################################
*/
#ifndef DIFFICULTY_HH
#define DIFFICULTY_HH
#include "QString"
/**
 * @class Difficulty
 * Class for passing information about game difficulties
 */
class Difficulty
{
public:

    /**
     * @param foodAmount: amount of total food in the grid
     * @param gridSizeX: x size of the playarea
     * @param gridsizeY: y size of the playarea
     * @param snakeSpeed: how fast the snake moves
     * @param snakeFastenerConst: how many foods to eat to speed up the snake
     * @param difficulty: name of the difficulty
     * Construct a Difficulty object
     */
    Difficulty(int foodAmount,int gridSizeX,int gridSizeY,int snakeSpeed,int snakeFastenerConst,QString difficulty);
    /**
     * Getters for the values
     */
    int foodAmount() const;
    int gridSizeX() const;
    int gridSizeY() const;
    int snakeSpeed() const;
    int snakeFastenerConst() const;
    QString difficulty() const;
private:
    // Difficulty values
    int foodAmount_;
    int gridSizeX_;
    int gridSizeY_;
    int snakeSpeed_;
    int snakeFastenerConst_;
    QString difficulty_;

};

#endif // DIFFICULTY_HH
