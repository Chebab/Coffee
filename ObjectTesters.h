//
//  ObjectTesters.h
//  Coffe_Quest
//
//  Created by Viktor Johansson on 2015-07-26.
//  Copyright (c) 2015 Viktor Johansson. All rights reserved.
//

#ifndef Coffe_Quest_ObjectTesters_h
#define Coffe_Quest_ObjectTesters_h
#include <SDL2/SDL.h>
#include "Shapes/Shapes.h"
#include <SDL2_image/SDL_image.h>

class CircleObject
{
private:
    float radius;
    float xPos;
    float yPos;

    
public:
    SDL_Texture* texture;
    SDL_Rect drawSurface;
    CircleObject(){}
    CircleObject(float x,float y, float rad,SDL_Texture* text)
    {
        this->radius = rad;
        this->xPos = x;
        this->yPos = y;
        this->texture = text;
        drawSurface = {(int)(xPos-radius),(int)(yPos-radius),64,64};
    }
    
    Circle getCircle()
    {
        return Circle(xPos,yPos,radius);
    }
    
    bool calculateMove(float xVelocity, float yVelocity, CircleObject& other)
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
};

#endif
