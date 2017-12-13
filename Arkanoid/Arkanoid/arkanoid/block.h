#pragma once

#include <vector>

using BlockID = uintptr_t;

enum class ShapeType {
  CUSTOM,
  WALL,
  BALL,
  BOARD,
  REGULAR,
  H_LETTER,
  CROSS,
  T_LETTER,
  P_LETTER,
};

// TODO(kk): What's going on?
class Shape : public std::vector<std::vector<BlockID>> {
 public:
  Shape() = default;
  Shape(size_t w, size_t h) { ResizeShape(w, h); }

  void ResizeShape(size_t w, size_t h) {
    resize(w);
    for (auto& it : *this) {
      it.resize(h);
    }
  }
};

class Block {
 private:
  ShapeType shape_type;

 public:
  Block(ShapeType a_shape_type = ShapeType::CUSTOM);

  virtual ~Block() = default;

  ShapeType GetShapeType() const { return shape_type; }

  BlockID GetID();
  virtual Shape CreateShape();

  virtual bool IsDeletable() { return true; }
};
