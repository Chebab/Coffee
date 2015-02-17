
#ifndef MATH_SIMPLE_H
#define MATH_SIMPLE_H

#include <math.h>
//Imported from Anders Pantzars math file
#define PI 3.14159265359

int inline Min(int x, int y)
{
	if (x < y)
		return x;
	return y;
}
int inline Max(int x, int y)
{
	if (x > y)
		return x;
	return y;
}
float inline Min(float x, float y)
{
	if (x < y)
		return x;
	return y;
}
float inline Max(float x, float y)
{
	if (x > y)
		return x;
	return y;
}

#endif