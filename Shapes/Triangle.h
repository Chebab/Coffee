
//Triangle

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Polygon.h"


class Triangle : public Polygon
{
private:
	float x1,x2,x3;
	float y1,y2,y3;
public:
	Triangle();
	~Triangle();
	Triangle(float,float,float,float,float,float);
	Triangle(Point,Point,Point);

	Point getFirstLineSegment();
	Point getSecondLineSegment();
	Point getThirdLineSegment();

	void Edges(std::vector<Line>&);

	float getFirstXpos();
	float getFirstYpos();
	float getSecondXpos();
	float getSecondYpos();
	float getThirdXpos();
	float getThirdYpos();

	bool Intersect(Point& other);
	bool Intersect(Line& other);
	bool Intersect(Circle& other);
	bool Intersect(Triangle& other);
	
	
		/*
	bool Intersect(Rectangle*);
	bool Intersect(Polygon*);
	bool Intersect(Triangle*);
	*/
};

#endif