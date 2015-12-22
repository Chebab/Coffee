//
//  PolygonType.cpp
//  Coffe_Quest
//
//  Created by Viktor Johansson on 2015-04-04.
//  Copyright (c) 2015 Viktor Johansson. All rights reserved.
//

#include "Polygon.h"


Polygon::Polygon()
{
    
}

Polygon::Polygon(std::vector<Point> points)
{
    long size = points.size();
    for (int i = 0; i < size; i++)
    {
        this->points.push_back(points[i]);
    }
}

Polygon::~Polygon()
{

}

//Taken from Anders Pantzar
void Polygon::Edges(std::vector<Line>& lines)
{
    long size = points.size();
    if (size < 2) return;
    
    for (int i = 0; i < size; i++)
    {
        Point p1 = points[i];
        Point p2;
        if (i == size - 1) p2 = points[0];
        else p2 = points[i + 1];
        
        lines.push_back(Line(p1.x, p1.y, p2.x, p2.y));
    }
}
//Taken from Anders Pantzar
void Polygon::PointsAsVectors(std::vector<Vector2D>& vectors)
{
    for(int i=0; i<points.size();i++)
    {
        vectors.push_back(Vector2D(points[i]));
    }
}

void Polygon::Projection(Vector2D axis, float& min, float& max)
{
    // get all points
    std::vector<Vector2D> points;
    PointsAsVectors(points);
    
    float dotProduct = axis.ScalarProduct(points[0]);
    min = dotProduct;
    max = dotProduct;
    int pointsCount = (int)points.size();
    
    for (int i = 0; i < pointsCount; i++)
    {
        Vector2D p = points[i];
        dotProduct = p.ScalarProduct(axis);
        if (dotProduct < min) min = dotProduct;
        else if (dotProduct > max) max = dotProduct;
    }
}

float Polygon::IntervalDistance(float minA, float maxA, float minB, float maxB)
{
    if (minA < minB) return minB - maxA;
    else return minA - maxB;
}

bool Polygon::Intersect(Point& other)
{
    std::vector<Line> edges; Edges(edges);
    unsigned long size = edges.size();
    int lastSide = 0;
    
    for (int i = 0; i < size; i++)
    {
        Line edge = edges[i];
        int currentSide = 0;
        edge.IsLeft(other) ? currentSide = 1 : currentSide = 2;
        
        if (lastSide == 0 || lastSide == currentSide)
            lastSide = currentSide;
        else
            return false;
    }
    
    return true;
}

bool Polygon::Intersect(Circle& other)
{
    Point temp = other.center();
    if (Intersect(temp)) return true;
    
    std::vector<Line> edges; Edges(edges);
    unsigned long size = edges.size();
    for (int i = 0; i < size; i++)
    {
        Line edge = edges[i];
        if (other.Intersect(edge)) return true;
    }
    
    return false;
    
}
bool Polygon::Intersect(Polygon& other)
{
    std::vector<Line> thisEdges;
    std::vector<Line> otherEdges;
    this->Edges(thisEdges);
    other.Edges(otherEdges);
    
    long edgeCountThis = thisEdges.size();
    long edgeCountOther = otherEdges.size();
    Vector2D edge;
    
    // For each edge
    for(int edgeIndex = 0; edgeIndex < edgeCountThis + edgeCountOther; edgeIndex++)
    {
        if(edgeIndex<edgeCountThis)	edge = thisEdges[edgeIndex].getLineVector();
        else edge = otherEdges[edgeIndex-edgeCountThis].getLineVector();
        
        // Find perpendicular vector
        Vector2D axis(-edge.x,edge.y);
        // Normalize vector i.e. make it of length one
        axis.Normalize();
        
        
        // Find the projection of the polygon on the current axis
        float minA = 0; float minB = 0; float maxA = 0; float maxB = 0;
        Polygon::Projection(axis, minA, maxA);
        other.Projection(axis, minB, maxB);
        
        // Check if the polygon projections are currentlty intersecting
        if (Polygon::IntervalDistance(minA, maxA, minB, maxB) > 0)
            return false;
        
    }
    
    return true;
}
