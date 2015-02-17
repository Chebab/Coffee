//2DVectorMath.h

#ifndef _VECTOR2D_MATH_H
#define _VECTOR2D_MATH_H
#include "Shapes.h"
class Vector2D{
private:
public:
	float x;
	float y;
	Vector2D();
	~Vector2D();
	Vector2D(float,float);
	Vector2D(Point&);
	Vector2D(Line&);
	float magnitude(){
		return sqrtf(x*x + y*y);
	}
	float distance(Vector2D&);
	float distanceSquared(Vector2D&);

	inline void Normalize(){
		float vectorLength = magnitude();
		if(vectorLength == 0) return;
		x /= vectorLength;
		y /= vectorLength;
	}

	// The following operator member functions are made by Anders Pantzar
	inline friend Vector2D operator/ (Vector2D& v, float scalar){
		return Vector2D(v.x / scalar, v.y / scalar);
	}

	inline friend Vector2D operator* (Vector2D& v, float scalar){
		return Vector2D(v.x * scalar, v.y * scalar);
	}

	inline friend Vector2D operator* (float scalar, Vector2D& v){
		return Vector2D(v.x * scalar, v.y * scalar);
	}

	inline friend Vector2D operator+ (Vector2D& v1, Vector2D& v2){
		return Vector2D(v1.x + v2.x, v1.y + v2.y);
	}

	inline friend Vector2D operator- (Vector2D& v1, Vector2D& v2){
		return Vector2D(v1.x - v2.x, v1.y - v2.y);
	}

	static inline float ScalarProduct(Vector2D& v1, Vector2D& v2){
		return v1.x * v2.x + v1.y * v2.y;
	}
	// P(v,u) = (v * u)/(v * v)*v
	inline Vector2D OrthoProjection(Vector2D& v1, Vector2D& v2){
		return (ScalarProduct(v1, v2) / ScalarProduct(v2, v2)) * v1;
	} 
};


#endif 