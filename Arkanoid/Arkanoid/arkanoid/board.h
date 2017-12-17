#pragma once
#include "block.h"
#include "utility.h"

class Board {
  float vx = 0.0f;
  Vector start_pos;
  int length;

 public:
 
  Board(const Vector& st_pos) : start_pos(st_pos), length(6) {}

  void SetPos(const Vector& pos) { start_pos = pos; }
  const Vector& GetPos() const { return start_pos; }
  int GetLength() const { return length; }
  Vector GetNextPos(float dt) const;
  void SetV(float v) { vx = v; }
  float GetV() const { return vx; }
  void ThrowBall();
};
