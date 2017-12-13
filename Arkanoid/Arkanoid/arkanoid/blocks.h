#pragma once

#include "block.h"

class Wall : public Block {
 public:
  Wall() : Block(ShapeType::WALL) {}
  bool IsDeletable() override {
    return false;
  }
};

using Brick = Block;
