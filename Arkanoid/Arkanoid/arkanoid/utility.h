#pragma once
#include <math.h>

enum class CrossedSide {
  NONE,
  TOP,
  BOTTOM,
  LEFT,
  RIGHT,
};

class Vector {
  float x;
  float y;

 public:
  Vector() : Vector(0, 0) {}
  Vector(float xx, float yy) : x(xx), y(yy) {}
  Vector(const Vector& v) : Vector(v.x, v.y) {}

  Vector& operator=(const Vector& v) {
    x = v.x;
    y = v.y;
    return *this;
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
  float length() { return sqrtf(x * x + y * y); }
  float X() const { return x; }
  float Y() const { return y; }
};

const Vector operator-(const Vector&l, const Vector& r);
const Vector operator+(const Vector&l, const Vector& r);
const Vector operator*(const Vector& l, float r);

CrossedSide IsCrossed(const Vector& p0, const Vector& p1, const Vector& box_lt, Vector* out);