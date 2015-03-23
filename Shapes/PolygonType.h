//PolygonType.h

#ifndef POLYGONTYPE_H
#define POLYGONTYPE_H

#include "Shapes.h"

class Line;
class Point;
class Vector2D;
//Up until this point it works

class PolygonType
{
private:
	std::vector<Point> points;
	//Taken from Anders Pantzar
	void Edges(std::vector<Line>& lines)
	{
		int size = points.size();
		if(size<=2) return;

		Point p1,p2;
		for(int i = 0;i<size;i++)
		{
			if(i >= point.size()-1) p2 = points[0];
			else p2 = points[i+1];
			//put in front
			lines.push_back(Line(p1,p2));
		}
	}
	//Taken from Anders Pantzar
	void PointsAsVectors(std::vector<Vector2D>& vectors)
	{
		for(int i=0; i<points.size();i++)
		{
			vectors.push_back(Vector2D(points[i]));
		}
	}
	//Taken from Anders Pantzar, not checked if OK
	void Projection(Vector2 axis, float& min, float& max)
	{
		// get all points
		std::vector<Vector2> points;
		PointsAsVectors(points);

		float dotProduct = axis.Dot(points[0]);
		min = dotProduct;
		max = dotProduct;
		int pointsCount = (int)points.size();

		for (int i = 0; i < pointsCount; i++)
		{
			Vector2 p = points[i];
			dotProduct = p.Dot(axis);
			if (dotProduct < min) min = dotProduct;
			else if (dotProduct > max) max = dotProduct;
		}
	}

	float IntervalDistance(float minA, float maxA, float minB, float maxB)
	{
		if (minA < minB) return minB - maxA;
		else return minA - maxB;
	}

public:
	bool Intersect(Point& other)
	{
		return false;
	}
	bool Intersect(PolygonType& other)
	{
		std::vector<Line> thisEdges;
		std::vector<Line> otherEdges;
		Edges(thisEdges);
		other.Edges(otherEdges);

		int edgeCountThis = thisEdges.size();
		int edgeCountOther = otherEdges.size();
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
		Projection(axis, minA, maxA);
		other.Projection(axis, minB, maxB);

		// Check if the polygon projections are currentlty intersecting
		if (IntervalDistance(minA, maxA, minB, maxB) > 0)
			return false;

		}

		return false;
	}
	bool Intersect(Circle& other)
	{
		return false;
	}
};

#endif