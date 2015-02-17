//Line

#ifndef LINE_H
#define LINE_H

#include "Shapes.h"
class Line : public Shapes{
private:
public:
	float x1,x2;
	float y1,y2;
	Line();
	~Line();
	Line(float,float,float,float);
	Line(Point,Point);

	float getFirstXpos();
	float getFirstYpos();
	float getSecondXpos();
	float getSecondYpos();

	Point getFirstLineSegment();
	Point getSecondLineSegment();

	Vector2D getLineVector();

	//Methods for checking collision
	bool Intersect(Point& other);
	bool Intersect(Line& other);
	bool Intersect(Circle& other);
	//bool Intersect(Triangle& other);
	
		/*
	bool Intersect(Rectangle*);
	bool Intersect(Polygon*);
	
	*/
};

#endif