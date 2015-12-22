//Rectangle

#ifndef RECTANGLE_H
#define RECTANGLE_H


class Point;
class Polygon;
#include "Polygon.h"
class Rectangle : public Polygon
{
private:
public:
    Rectangle();
    ~Rectangle();
    Rectangle(Point,Point,Point,Point);
    Rectangle(std::vector<Point> points);
    
    
    // Creates a square rectangle
    Rectangle(Point start_point,float length);
};

#endif