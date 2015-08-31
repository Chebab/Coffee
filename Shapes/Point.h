//Point

#ifndef POINT_H
#define POINT_H

#include "Shapes.h"
class Point : public Shapes
{

private:
public:
	float x;
	float y;
	Point();
	~Point();
	Point(float,float);
	//Methods for fetching data
	float getXpos();
	float getYpos();
	//Methods for setting data
	void setXpos(float);
	void setYpos(float);
	//Methods for calculating the distance between points
	float distance(Point&);
	float distanceSquared(Point&);

	bool Intersect(Point& other);
	bool Intersect(Circle& other);
	bool Intersect(Line& other);
	//bool Intersect(Triangle& other);


};

#endif