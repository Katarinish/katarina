#pragma once

#include "utility.h"

class Ball {
 private:
  Vector pos;
  Vector vel = Vector(15.f, -15.f);

 public:
  Ball(const Vector& a_pos) : pos(a_pos) {}

  void SetPos(const Vector& p) { pos = p; }
  const Vector& GetPos() const { return pos; }

  void SetVel(const Vector& v) { vel = v; }
  const Vector& GetVel() const { return vel; }

  float GetAcc() const { return 0.0f; }

  Vector GetNextPos(float dt) const;
};
