//Circle
// The outline of this class has been taken from Anders Pantzar
#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shapes.h"
class Circle : public Shapes
{
private:
	float x;
	float y;
	float radius;

public:
	Circle();
	~Circle();
	Circle(float,float,float);

	Point center();

	//Methods for fetching data
	float getXpos();
	float getYpos();
	float getRadius();
	//Methods for setting data
	void setXpos(float);
	void setYpos(float);
	void setRadius(float);

	//Methods for checking collision
	bool Intersect(Circle& other);
	bool Intersect(Point& other);
	bool Intersect(Line& other);
	//bool Intersect(Triangle& other);
	/*
	bool Intersect(Rectangle*);
	bool Intersect(Polygon*);
	bool Intersect(Triangle*);
	*/
};

#endif