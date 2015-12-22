//Shapes.h

#ifndef SHAPES_H
#define SHAPES_H

#include "Math.h"
#include <iostream>
#include <vector>

class Point;
class Circle;
class Line;
class Vector2D;
class Triangle;
class Polygon;
class Rectangle;
class Shapes
{
public:
	virtual bool Intersect(Point& other) = 0;
	virtual bool Intersect(Circle& other) = 0;
    virtual bool Intersect(Polygon& other) =0;

	//Remove these when PolygonTypes are done
	//virtual bool Intersect(Line& other) = 0;
	//virtual bool Intersect(Triangle& other) = 0;
};

#include "Point.h"
#include "Circle.h"
#include "Line.h"
#include "2DVectorMath.h"
#include "Polygon.h" //Makes sure that all subclasses are made
//#include "Rectangle.h"

#endif