#include "ball.h"

Vector Ball::GetNextPos(float dt) const {
  return pos + vel * dt;
}
