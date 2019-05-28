/*
####################################################################
# Program description: "While revenge is served cold and vengeance #
#                       is served hot revengeance is often seen    #
#                       served with Cajun with a side of onion     #
#                       rings and often dumplings in the Orient."  #
#                       - urbandictionary                          #
#                                                                  #
# File: bodypart.cpp                                               #
# Description: Defines a class for snake bodyparts for the game.   #
#                                                                  #
# Author: Jani Niittymäki,                                         #
####################################################################
*/
#include "bodypart.hh"
#include <QBrush>
#include <QPen>
BodyPart::BodyPart(QColor col,const double snakeSize){
    //Rectangle size
    setRect(0, 0, snakeSize, snakeSize);
    //Color settings
    QPen p(Qt::white,0);
    setPen(p);
    setBrush(col);


}
