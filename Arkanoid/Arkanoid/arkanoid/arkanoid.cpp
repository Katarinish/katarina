#include "arkanoid.h"
#include <iostream>
#include "blocks.h"

Arkanoid::Arkanoid() : game_field(50, 25), ball(Vector(50, 48)) {
  Init();
}

Arkanoid::~Arkanoid() {}

void Arkanoid::Init() {
  // blocks
  for (int x = 1; x < game_field.GetWidth() - 1; x += 4) {
    game_field.AddBlock(x, 1, new Brick(ShapeType::REGULAR));
  }

  for (int x = 1; x < game_field.GetWidth() - 1; x += 3) {
    game_field.AddBlock(x, 2, new Brick(ShapeType::T_LETTER));
    game_field.AddBlock(x, 3, new Brick(ShapeType::H_LETTER));
    game_field.AddBlock(x, 5, new Brick(ShapeType::CROSS));
  }

  // Borders
  auto* wall_block = new Wall;

  // Top wall & temp bottom wall
  // TODO(kk): Remove bottom wall and create board.
  for (int x = 0; x < game_field.GetWidth(); x++) {
    game_field.AddBlock(x, 0, wall_block);
    game_field.AddBlock(x, game_field.GetHeight() - 1, wall_block);
  }
  // Left & Right walls.
  for (int y = 0; y < game_field.GetHeight(); ++y) {
    game_field.AddBlock(0, y, wall_block);
    game_field.AddBlock(game_field.GetWidth() - 1, y, wall_block);
  }

  ball.SetPos(Vector(game_field.GetWidth() / 2, game_field.GetHeight() - 2));
  ball.SetVel(Vector(20.0f, -13.0f));
}

void Arkanoid::Run() {}

void Arkanoid::Draw(gdi::Graphics& canvas) {
  // TODO(kk): Remove magic constants.
  // draw process should depend on window & game field sizes.
  for (int x = 0; x < game_field.GetWidth(); ++x) {
    for (int y = 0; y < game_field.GetHeight(); ++y) {
      const auto* block = game_field.GetBlock(x, y);
      if (!block)
        continue;
      gdi::Color color;
      switch (block->GetShapeType()) {
        case ShapeType::WALL:
          color = gdi::Color::Purple;
          break;
        case ShapeType::T_LETTER:
          color = gdi::Color::Aquamarine;
          break;
        case ShapeType::REGULAR:
          color = gdi::Color::Bisque;
          break;
        case ShapeType::H_LETTER:
          color = gdi::Color::Coral;
          break;
        case ShapeType::CROSS:
          color = gdi::Color::PowderBlue;
          break;
      }
      canvas.FillRectangle(&gdi::SolidBrush(color),
                           gdi::Rect(x * 10, y * 10, 9, 9));
    }
  }

  // Ball
  canvas.FillEllipse(&gdi::SolidBrush(gdi::Color::Yellow),
                     gdi::RectF(ball.GetPos().X() * 10 - 5,
                                ball.GetPos().Y() * 10 - 5, 10.0f, 10.0f));
}

void Arkanoid::UpdateWorld(double dt) {
  const float delta = 0.0001f;
  if (dt < delta)
    return;  // too small period for update, skip it.0

  for (float time = 0; time <= dt; time += delta) {
    auto next_ball_pos = ball.GetNextPos(delta);

    auto* b = game_field.GetBlock(next_ball_pos.X(), next_ball_pos.Y());
    if (!b) {
      ball.SetPos(next_ball_pos);
      continue;
    }

    int block_x = next_ball_pos.X();
    int block_y = next_ball_pos.Y();
    auto block_pos = Vector(block_x, block_y);

    Vector intersection;
    auto side =
        IsCrossed(ball.GetPos(), next_ball_pos, block_pos, &intersection);
    // TODO(kk): use intersection.

    switch (side) {
      case CrossedSide::TOP:
      case CrossedSide::BOTTOM:
        ball.SetVel(Vector(ball.GetVel().X(), -ball.GetVel().Y()));
        break;
      case CrossedSide::LEFT:
      case CrossedSide::RIGHT:
        ball.SetVel(Vector(-ball.GetVel().X(), ball.GetVel().Y()));
        break;
    }
    if (side != CrossedSide::NONE) {
      // TODO(kk): Process block hit
      game_field.DeleteCell(block_x, block_y);
    }
  }
}

bool Arkanoid::ReadyToExit() {
  // TODO(kk): Implement this.
  return false;
}
