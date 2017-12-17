#include "board.h"

 Vector Board::GetNextPos(float dt) const {
	return start_pos + Vector(vx, 0) * dt;
}

void Board::ThrowBall() {
  // TODO(kk): Implement this.
}

