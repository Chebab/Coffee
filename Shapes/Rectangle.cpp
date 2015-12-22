//
//  Rectangle.cpp
//  Coffe_Quest
//
//  Created by Viktor Johansson on 2015-09-21.
//  Copyright (c) 2015 Viktor Johansson. All rights reserved.
//

#include "Rectangle.h"

Rectangle::Rectangle(){
    
}
Rectangle::~Rectangle(){
    points.clear();
}

Rectangle::Rectangle(Point A,Point B,Point C,Point D)
{
    points.push_back(A);
    points.push_back(B);
    points.push_back(C);
    points.push_back(D);
};
Rectangle::Rectangle(std::vector<Point> points)
{
    if (points.size()==4) {
        for (int i = 0; i<points.size(); i++) {
            this->points.push_back(points[i]);
        }
    }
};

Rectangle::Rectangle(Point start_point,float length)
{
    Point rPoint = Point(start_point.x+length,start_point.y);
    Point dPoint = Point(start_point.x,start_point.y+length);
    Point rdPoint = Point(start_point.x+length,start_point.y+length);
    
    points.push_back(start_point);
    points.push_back(rPoint);
    points.push_back(rdPoint);
    points.push_back(dPoint);
    
};

