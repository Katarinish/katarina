#include "block.h"

Block::Block(ShapeType a_shape_type /*= ShapeType::CUSTOM*/)
    : shape_type(a_shape_type) {}

BlockID Block::GetID() {
  // TODO(kk): Oh my god, what is going on?
  return reinterpret_cast<BlockID>(this);
}

Shape Block::CreateShape() {
  switch (shape_type) {
    case ShapeType::CUSTOM:
      break;
    case ShapeType::WALL: {
      Shape res(1,1);
      res[0][0] = GetID();
      return res;
    } break;
    case ShapeType::REGULAR: {
      Shape res(4, 1);
      for (int i = 0; i < 4; ++i)
        res[i][0] = GetID();
      return res;
    } break;
    case ShapeType::H_LETTER: {
      Shape res(3, 3);
      for (int i = 0; i < 3; ++i) {
        res[0][i] = GetID();
        res[2][i] = GetID();
      }
      res[1][1] = GetID();
      return res;
    } break;
    case ShapeType::CROSS: {
      Shape res(3, 3);
      for (int i = 0; i < 3; ++i) {
        res[i][1] = GetID();
        res[1][i] = GetID();
      }
      return res;
    } break;
    case ShapeType::T_LETTER: {
      Shape res(3, 2);
      for (int i = 0; i < 3; ++i) {
        res[i][0] = GetID();
      }
      res[1][1] = GetID();
      return res;
    } break;
    case ShapeType::P_LETTER: {
      Shape res(3, 3);
      for (int i = 0; i < 3; ++i) {
        res[0][i] = GetID();
        res[i][0] = GetID();
        res[i][2] = GetID();
      }
      return res;
    } break;
  }  // switch
  return Shape();
}
