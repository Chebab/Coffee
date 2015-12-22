//Circle.cpp
#include "Circle.h"


Circle::Circle(){}
Circle::~Circle(){}

Circle::Circle(float xpos, float ypos, float radius){
	this -> x = xpos;
	this -> y = ypos;
	this -> radius = radius;
}
Point Circle::center(){
	return Point(x,y);
}
//Methods for fetching data
float Circle::getXpos(){
	return this->x;	
}

float Circle::getYpos(){
	return this->y;
}

float Circle::getRadius(){
	return this->radius;
}

//Methods for setting data
void Circle::setXpos(float newXpos){
	this->x = newXpos;
}
void Circle::setYpos(float newYpos){
	this->y = newYpos;
}
void Circle::setRadius(float newRadius){
	this->radius = newRadius;
}

//Methods for checking collision
bool Circle::Intersect(Circle& other){
	float squaredRadius = (radius + other.radius) * (radius + other.radius);
	Point temp = other.center();
	float distSquared = center().distanceSquared(temp);

	return squaredRadius >= distSquared;
}

bool Circle::Intersect(Point& other){
	float squaredRadius = radius * radius;
	float distSquared = center().distanceSquared(other);

	return squaredRadius >= distSquared;
}


bool Circle::Intersect(Line& other){
	// Source:
	// http://www.openprocessing.org/sketch/65771

	float a, b, c, d;
	a = other.getSecondXpos() - other.getFirstXpos();
	b = other.getSecondYpos() - other.getFirstYpos();
	c = x - other.getFirstXpos();
	d = y - other.getFirstYpos();
	
	//bool circleSideIsRight = (d*a - c*b < 0);

	bool startInside = false;
	bool endInside = false;
	bool middleInside = false;

	if ((d*a - c*b)*(d*a - c*b) <= radius*radius*(a*a + b*b))
	{
		// Collision is possible
		if (c*c + d*d <= radius*radius) 
		{
			// Line segment start point is inside the circle
			startInside = true;
		}
		if ((a - c)*(a - c) + (b - d)*(b - d) <= radius*radius) 
		{
			// Line segment end point is inside the circle
			endInside = true;
		}
		if (!startInside && !endInside && c*a + d*b >= 0 && c*a + d*b <= a*a + b*b) 
		{
			// Middle section only
			middleInside = true;
		}
	}

	return startInside || endInside || middleInside;
}
bool Circle::Intersect(Triangle& other){
    return false;
}
bool Circle::Intersect(Polygon& other)
{
    return other.Intersect(*this);
}
// TODO
/*
bool Circle::Intersect(Triangle& other)
{
	// Check if circle center is inside the triangle
	Point center = this->center();
	if(other.Intersect(center))
		return true;

	

	// Get the lines of the triangle
	Line l1 = Line(other.getFirstLineSegment(), other.getSecondLineSegment());
	Line l2 = Line(other.getSecondLineSegment(), other.getThirdLineSegment());
	Line l3 = Line(other.getThirdLineSegment(), other.getFirstLineSegment());

	// Check if the circle intersects with any of the triangle sides
	return this->Intersect(l1) || this->Intersect(l2) || this->Intersect(l3);
}

bool Circle::Intersect(Rectangle*){

}
bool Circle::Intersect(Polygon*){

}

*/