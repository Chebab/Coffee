//testShapes.cpp

#include "Circle.h"
#include "Point.h"
#include <iostream>
#include "Shapes.h"

using namespace std;
class Point;
class Circle;

int shapemain(int argc, char** args){
	cout << "True is: " << true << ". False is: " << false << endl;

	Circle c1 = Circle(5,5,10);
	Circle c2 = Circle(5,21,5);
	cout << c1.Intersect(c2) << endl;;
	Point(3,3);


	return 0;
}