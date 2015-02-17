//Line.cpp

#include "Line.h"

Line::Line(){
	
}
Line::~Line(){
	
}

Line::Line(float xp1, float yp1, float xp2, float yp2){
	this->x1 = xp1;
	this->y1 = yp1;
	this->x2 = xp2;
	this->y2 = yp2;
}

Line::Line(Point p1, Point p2){
	this->x1 = p1.getXpos();
	this->y1 = p1.getYpos();
	this->x2 = p2.getXpos();
	this->y2 = p2.getYpos();
}

float Line::getFirstXpos(){
	return x1;
}
float Line::getFirstYpos(){
	return y1;
}
float Line::getSecondXpos(){
	return x2;
}
float Line::getSecondYpos(){
	return y2;
}

Point Line::getFirstLineSegment(){
	return Point(x1, y1);
}

Point Line::getSecondLineSegment(){
	return Point(x2, y2);
}

Vector2D Line::getLineVector(){
	return Vector2D(x2-x1, y2-y1);
}

//Methods for checking collision
bool Line::Intersect(Point& other){
	float dy = y2 - y1;
	float dx = x2 - x1;
	float k = 0.0f;
	float m = 0.0f;

	bool onSameLine = false;

	if (dy == 0.0f){
		onSameLine = x1 == other.getXpos();
	}
	else if (dx == 0.0f){
		onSameLine = y1 == other.getYpos();
	}
	else {
		k = dy/dx;
		m = y1 - k * x1;
		onSameLine = other.getYpos() == other.getXpos()*k+m;
	}
	if (onSameLine){
		// AB > AC && BA > BC
		Point firstPoint = getFirstLineSegment();
		Point secondPoint = getSecondLineSegment();
		float distAB = firstPoint.distanceSquared(secondPoint);
		float distAC = firstPoint.distanceSquared(other);
		float distBC = secondPoint.distanceSquared(other);
		return distAB >= distAC && distAB >= distBC;
	}
	return false;
}
bool Line::Intersect(Line& other){

	// Source
	// http://flassari.is/2008/11/line-line-intersection-in-cplusplus/

	Point p1 = getFirstLineSegment();
	Point p2 = getSecondLineSegment();
	Point p3 = other.getFirstLineSegment();
	Point p4 = other.getSecondLineSegment();

	// Store the values for fast access and easy
	// equations-to-code conversion
	float x1 = p1.getXpos(), x2 = p2.getXpos();
	float x3 = p3.getXpos(), x4 = p4.getXpos();
	float y1 = p1.getYpos(), y2 = p2.getYpos();
	float y3 = p3.getYpos(), y4 = p4.getYpos();

	float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	// If d is zero, there is no intersection
	if (d == 0) return false;

	// Get the x and y
	float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
	float x = (pre * (x3 - x4) - (x1 - x2) * post) / d;
	float y = (pre * (y3 - y4) - (y1 - y2) * post) / d;

	// Check if the x and y coordinates are within both lines
	if (x < Min(x1, x2) || x > Max(x1, x2) ||
		x < Min(x3, x4) || x > Max(x3, x4)) return false;
	if (y < Min(y1, y2) || y > Max(y1, y2) ||
		y < Min(y3, y4) || y > Max(y3, y4)) return false;
	return true;
}
bool Line::Intersect(Circle& other){
	return other.Intersect(*this);
}
/*
bool Line::Intersect(Triangle& other)
{
	return other.Intersect(*this);
}

bool Intersect(Triangle& other){
	return other.Intersect(*this);
}
*/