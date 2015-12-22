//
//  ObjectTesters.cpp
//  Coffe_Quest
//
//  Created by Viktor Johansson on 2015-12-22.
//  Copyright © 2015 Viktor Johansson. All rights reserved.
//

#include "ObjectTesters.h"

bool CircleObject::calculateMove(float xVelocity, float yVelocity, CircleObject& other)
{
    Circle thisCircle = Circle(xPos + xVelocity, yPos + yVelocity,radius);
    Circle otherCircle = other.getCircle();
    if (!thisCircle.Intersect(otherCircle)) {
        this->xPos = xPos + xVelocity;
        this->yPos = yPos + yVelocity;
        drawSurface.x =(int)(xPos-radius);
        drawSurface.y =(int)(yPos-radius);
        return true;
    }
    
    return false;
}
bool CircleObject::calculateMove(float xVelocity, float yVelocity, RectObject& other)
{
    Circle thisCircle = Circle(xPos + xVelocity, yPos + yVelocity,radius);
    Rectangle otherCircle = other.getRect();
    if (!thisCircle.Intersect(otherCircle)) {
        this->xPos = xPos + xVelocity;
        this->yPos = yPos + yVelocity;
        drawSurface.x =(int)(xPos-radius);
        drawSurface.y =(int)(yPos-radius);
        return true;
    }
    
    return false;
}

bool RectObject::calculateMove(float xVelocity, float yVelocity, RectObject& other)
{
    Rectangle thisRect = Rectangle(Point(start_x+xVelocity, start_y+yVelocity),length);
    Rectangle otherRect = other.getRect();
    if (!thisRect.Intersect(otherRect)) {
        this->start_x += xVelocity;
        this->start_y += yVelocity;
        drawSurface.x =(int)(start_x);
        drawSurface.y =(int)(start_y);
        return true;
    }
    
    return false;
}
bool RectObject::calculateMove(float xVelocity, float yVelocity, CircleObject& other)
{
    Rectangle thisRect = Rectangle(Point(start_x+xVelocity, start_y+yVelocity),length);
    Circle otherRect = other.getCircle();
    if (!thisRect.Intersect(otherRect)) {
        this->start_x += xVelocity;
        this->start_y += yVelocity;
        drawSurface.x =(int)(start_x);
        drawSurface.y =(int)(start_y);
        return true;
    }
    
    return false;
}