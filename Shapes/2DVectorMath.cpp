//2DVectorMath.cpp
#include "2DVectorMath.h"

Vector2D::Vector2D(){

}
Vector2D::~Vector2D(){

}
Vector2D::Vector2D(float xpos, float ypos){
	this->x = xpos;
	this->y = ypos;
}
Vector2D::Vector2D(Point& other){
	this->x = other.getXpos();
	this->y = other.getYpos();
}
Vector2D::Vector2D(Line& other){
	this->x = other.x2 - other.x1;
	this->y = other.y2 - other.y1;
}

//Created by Anders Pantzar
float Vector2D::distance(Vector2D& other)
{
	return sqrtf(distanceSquared(other));
}
//Created by Anders Pantzar
float Vector2D::distanceSquared(Vector2D& other)
{
	return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y);
}