
#include "utility.h"

const Vector operator-(const Vector& l, const Vector& r) {
  return Vector(l.X() - r.X(), l.Y() - r.Y());
}

const Vector operator+(const Vector& l, const Vector& r) {
  return Vector(l.X() + r.X(), l.Y() + r.Y());
}

const Vector operator*(const Vector& l, float r) {
  return Vector(l.X() * r, l.Y() * r);
}

//Vector multiplication gives us a value of "z" vector-component 
// which lets us find out the sign ( + or - ) of the multiplication (vector's direction)
float VectorMult(const Vector& a, const Vector& b) {
	float z_component = a.X()*b.Y() - a.Y()*b.X();
	return z_component;
}

bool IsVectorsCrossed(const Vector& a,
                      const Vector& b,
                      const Vector& c,
                      const Vector& d,
                      const Vector* intersection) {

  // TODO(kk): Implement this.

	auto v1 = VectorMult(c-a, b-a); //multiplication of [ac;ab]
	auto v2 = VectorMult(d-a, b-a); //multiplication of [ad;ab]
	auto v3 = VectorMult(a-c, d-c); //multiplication of [ca;cd]
	auto v4 = VectorMult(b-c, d-c); //multiplication of [cb;cd]

	if ((v1*v2 < 0.00000001) && (v3*v4 < 0.00000001))
		return true;
  return false;
}

CrossedSide IsCrossed(const Vector& p0,
                      const Vector& p1,
                      const Vector& box_lt,
                      Vector* out) {
  if (IsVectorsCrossed(p0, p1, box_lt, box_lt + Vector(1.0f, 0), out)) {
    return CrossedSide::TOP;
  }

  if (IsVectorsCrossed(p0, p1, box_lt + Vector(0, 1), box_lt + Vector(1.0f, 1),
                       out)) {
    return CrossedSide::BOTTOM;		
  }

  if (IsVectorsCrossed(p0, p1, box_lt, box_lt + Vector(0, 1), out)) {
    return CrossedSide::LEFT;
  }

  if (IsVectorsCrossed(p0, p1, box_lt + Vector(1, 0), box_lt + Vector(1, 1),
                       out)) {
    return CrossedSide::RIGHT;
  }

  return CrossedSide::NONE;
}
CrossedSide IsBoardCrossed(const Vector& p0,
	const Vector& p1,
	const Vector& board0,
	int length,
	Vector* out) {
	if (IsVectorsCrossed(p0, p1, board0, board0 + Vector(length, 0), out))
		return CrossedSide::TOP;
	return CrossedSide::NONE;
}

