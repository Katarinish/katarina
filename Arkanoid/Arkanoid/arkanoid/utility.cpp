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

bool IsVectorsCrossed(const Vector& a,
                      const Vector& b,
                      const Vector& c,
                      const Vector& d,
                      const Vector* intersection) {
  // TODO(kk): Implement this.
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
