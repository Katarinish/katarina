#include "board.h"

Board::Board() {}

void Board::ThrowBall() {
  // TODO(kk): Implement this.
}

Shape Board::CreateShape() {
  Shape res(4, 1);
  for (int i = 0; i < 4; ++i) {
    res[0][i] = GetID();
  }
  return res;
}
