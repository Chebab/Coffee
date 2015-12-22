//point.cpp
#include "Point.h"
Point::Point(){}
Point::~Point(){}

Point::Point(float xpos, float ypos){
	this->x = xpos;
	this->y = ypos;
}

//Methods for fetching data
float Point::getXpos(){
	return this->x;
}

float Point::getYpos(){
	return this->y;
}

//Methods for setting data
void Point::setXpos(float xpos){
	this->x = xpos;
}
void Point::setYpos(float ypos){
	this->y = ypos;
}

//Created by Anders Pantzar
float Point::distance(Point& other)
{
	return sqrtf(distanceSquared(other));
}
//Created by Anders Pantzar
float Point::distanceSquared(Point& other)
{
	return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y);
}

bool Point::Intersect(Point& other)
{
	return distance(other);
}

bool Point::Intersect(Circle& other)
{
	return other.Intersect(*this);
}
bool Point::Intersect(Line& other)
{
	return other.Intersect(*this);
}
bool Point::Intersect(Polygon& other)
{
    return other.Intersect(*this);
}
/*
bool Point::Intersect(Triangle& other)
{
	// TODO
	return false;
}
*/