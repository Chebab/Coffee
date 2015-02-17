//Triangle.cpp

#include "Triangle.h"


Triangle::Triangle(){

}
Triangle::~Triangle(){

}
Triangle::Triangle(float xp1,float yp1,float xp2, float yp2,
					float xp3, float yp3){

	this->x1 = xp1;
	this->x2 = xp2;
	this->x3 = xp3;
	this->y1 = yp1;
	this->y2 = yp2;
	this->y3 = yp3;
}

Triangle::Triangle(Point p1, Point p2, Point p3){
	this->x1 = p1.getXpos();
	this->x2 = p2.getXpos();
	this->x3 = p3.getXpos();
	this->y1 = p1.getYpos();
	this->y2 = p2.getYpos();
	this->y3 = p3.getYpos();
}

Point Triangle::getFirstLineSegment(){
	return Point(x1,y1);
}
Point Triangle::getSecondLineSegment(){
	return Point(x2,y2);
}
Point Triangle::getThirdLineSegment(){
	return Point(x3,y3);
}


void Triangle::Edges(std::vector<Line>& edges)
{
	edges.push_back(Line(x1, y1, x2, y2));
	edges.push_back(Line(x2, y2, x3, y3));
	edges.push_back(Line(x3, y3, x1, y1));
}

float Triangle::getFirstXpos()
{
	return x1;
}
float Triangle::getFirstYpos(){
	return y1;
}
float Triangle::getSecondXpos(){
	return x2;
}
float Triangle::getSecondYpos(){
	return y2;
}
float Triangle::getThirdXpos(){
	return x3;
}
float Triangle::getThirdYpos(){
	return y3;
}

bool Triangle::Intersect(Point& other){

	// source: http://www.blackpawn.com/texts/pointinpoly/

	// Get vectors
	Vector2D Vector_A = Vector2D(this->getFirstLineSegment());
	Vector2D Vector_B = Vector2D(this->getSecondLineSegment());
	Vector2D Vector_C = Vector2D(this->getThirdLineSegment());
	Vector2D Vector_P = Vector2D(other);

	// Compute vectors        
	//v0 = C - A
	//v1 = B - A
	//v2 = P - A

	Vector2D v0 = Vector_C - Vector_A;
	Vector2D v1 = Vector_B - Vector_A;
	Vector2D v2 = Vector_P - Vector_A;

	// Compute dot product

	float dot00 = Vector2D::ScalarProduct(v0, v0);
	float dot01 = Vector2D::ScalarProduct(v0, v1);
	float dot02 = Vector2D::ScalarProduct(v0, v2);
	float dot11 = Vector2D::ScalarProduct(v1, v1);
	float dot12 = Vector2D::ScalarProduct(v1, v2);

	float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
	float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
	float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

	return (u >= 0) && (v >= 0) && (u + v < 1);
}

bool Triangle::Intersect(Line& other){
	// Make the three lines representing the Triangle
	Line l1 = Line(getFirstLineSegment(), getSecondLineSegment());
	Line l2 = Line(getSecondLineSegment(), getThirdLineSegment());
	Line l3 = Line(getThirdLineSegment(), getFirstLineSegment());

	return other.Intersect(l1) || other.Intersect(l2) || other.Intersect(l3) ;
}
bool Triangle::Intersect(Circle& other)
{
	return other.Intersect(*this);
}

// This method does not handle when a triangle resides in another triangle
// Replace this with Separating Axis Theorem
// source: http://www.codeproject.com/Articles/15573/D-Polygon-Collision-Detection
bool Triangle::Intersect(Triangle& other)
{
	// Get the lines of the triangle
	Line l1 = Line(getFirstLineSegment(), getSecondLineSegment());
	Line l2 = Line(getSecondLineSegment(), getThirdLineSegment());
	Line l3 = Line(getThirdLineSegment(), getFirstLineSegment());

	// Check if any of this triangles sides intersect with the other triangle
	return other.Intersect(l1) || other.Intersect(l2) || other.Intersect(l3);









}