/*
####################################################################
#                                                                  #
# Program description: "While revenge is served cold and vengeance #
#                       is served hot revengeance is often seen    #
#                       served with Cajun with a side of onion     #
#                       rings and often dumplings in the Orient."  #
#                       - urbandictionary                          #
#                                                                  #
# File: bodypart.hh                                                #
# Description: Declares a class for snake bodyparts for the game.  #
#                                                                  #
# Author: Jani Niittymäki                                          #
####################################################################
*/
#ifndef BODYPART_H
#define BODYPART_H
#include <QGraphicsRectItem>

/**
 * @class BodyPart
 * Class for information about snakeparts
 *
 * Extends QGraphicsRectItem so the rectangle settings
 * can be set for the bodypart
 */
class BodyPart: public QGraphicsRectItem
{
public:
    /**
     * @param col: color for the snakepart
     * Construct a BodyPart object
     */
    BodyPart(QColor col,const double snakeSize);
private:

};

#endif // BODYPART_H
