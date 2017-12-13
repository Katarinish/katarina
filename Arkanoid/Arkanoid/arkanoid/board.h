#pragma once
#include "block.h"

class Board : public Block {
  float vx = 0.0f;

 public:
  Board();
  Shape CreateShape() override;

  void SetV(float v) { vx = v; }
  float GetV() const { return vx; }

  void ThrowBall();
};
