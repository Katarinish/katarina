#pragma once
#include <math.h>

typedef enum CrossedSide {
	TOP,
	BOTTOM,
	LEFT,
	RIGHT,
} crossed_side;


class Vector {
	float x;
	float y;
	double k; // y = kx+b
	double b;
public:
	Vector() : Vector(0, 0) {}
	Vector(float xx, float yy) : x(xx), y(yy), k(0), b(0) {}
	Vector(const Vector& v):  Vector(v.x, v.y) {}
	Vector& operator=(const Vector& v) {
		x = v.x;
		y = v.y;
		k = v.k;
		b = v.b;
	}
	Vector& operator*=(float t) {
		x *= t;
		y *= t;
		return *this;
	}
	Vector& operator+=(const Vector& t) {
		x += t.x;
		y += t.y;
		return *this;
	}
	float length() {
		return sqrt(x*x + y*y);
	}
	float X() const {
		return x;
	}
	float Y() const {
		return y;
	}
	float B() const {
		return b;
	}
	float K() const {
		return k;
	}
	void Set_kb(double k, double b) {
		this->k = k;
		this->b = b;
	}
	bool If_crossed(const Vector& point) {
		if (point.X() >= this->x && point.X() <= this->x + 1 && point.Y() >= this->y && point.Y() <= this->x + 1)
			return true;
	}
	crossed_side CrossedSide(const Vector& first_line);
	
};


Vector Find_line(const Vector& v1, const Vector& v2) {
	Vector line;
	double k = (v2.Y() - v1.Y()) / (v2.X() - v1.X());
	double b = (v2.X()*v1.Y() - v1.X()*v2.Y()) / (v2.X() - v1.X());
	line.Set_kb(k, b);
	return line;
}
Vector Crossed_point(const Vector& line1, const Vector& line2) {
	int x = 0;
	int y = 0;
	x = (line2.B() - line1.B()) / (line1.K() - line2.K());
	y = line1.K()*x + line1.B();
	Vector crossed_point(x, y);
	return crossed_point;
}



/*
Vector pos(10, 9.5);
pos *= 4
*/