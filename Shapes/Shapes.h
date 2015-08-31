//Shapes.h

#ifndef SHAPES_H
#define SHAPES_H

#include "Math.h"
#include <iostream>
#include <vector>

//#include "PolygonType.h"

class Point;
class Circle;
class Line;
class Vector2D;
class Triangle;
//class Triangle;
class Shapes
{
public:
	virtual bool Intersect(Point& other) = 0;
	virtual bool Intersect(Circle& other) = 0;
	//virtual bool Intersect(PolygonType& other)

	//Remove these when PolygonTypes are done
	virtual bool Intersect(Line& other) = 0;
	//virtual bool Intersect(Triangle& other) = 0;
};

#include "Point.h"
#include "Circle.h"
#include "Line.h"
#include "Triangle.h"
#include "2DVectorMath.h"
//#include "Triangle.h"

#endif