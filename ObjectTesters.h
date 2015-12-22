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
class RectObject;
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
    
    bool calculateMove(float xVelocity, float yVelocity, CircleObject& other);
    bool calculateMove(float xVelocity, float yVelocity, RectObject& other);
};

class RectObject
{
private:
    float start_x;
    float start_y;
    float length;
public:
    SDL_Texture* texture;
    SDL_Rect drawSurface;
    RectObject(){}
    RectObject(float x,float y, float length,SDL_Texture* text)
    {
        this->length=length;
        this->start_x=x;
        this->start_y=y;
        this->texture = text;
        drawSurface = {(int)(start_x),(int)(start_y),64,64};
    }
    
    Rectangle getRect()
    {
        Point p = Point(start_x,start_y);
        return Rectangle(p,length);
    }
    
    bool calculateMove(float xVelocity, float yVelocity, RectObject& other);
    bool calculateMove(float xVelocity, float yVelocity, CircleObject& other);
};

#endif
