//Polygon.h

#ifndef POLYGON_H
#define POLYGON_H


class Line;
class Point;
class Vector2D;
class Shapes;
//Up until this point it works

#include "Shapes.h"
class Polygon : Shapes
{
private:

public:
	//Taken from Anders Pantzar, not checked if OK
    void Projection(Vector2D,float&,float&);
    float IntervalDistance(float,float,float,float);

   	std::vector<Point> points;
    
    Polygon();
    Polygon(std::vector<Point> points);
    ~Polygon();
    
    void Edges(std::vector<Line>& lines);
    void PointsAsVectors(std::vector<Vector2D>& vectors);
    
    bool Intersect(Point&);
    bool Intersect(Polygon&);
    bool Intersect(Circle&);

};
#include "Rectangle.h"
#include "Triangle.h"
#endif