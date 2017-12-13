#include "game.h"

Game::Game() : gui::BaseGameWindow(100, 100, 1013, 537) {}

void Game::Render(gdi::Graphics& canvas) {
  // Clear background
  canvas.Clear(gdi::Color::Black);

  // Delegate rendering to game.
  arkanoid.Draw(canvas);
}

void Game::ProcessInput(const bool keys[256]) {
  // TODO(kk): map pressed key into user input.
}

void Game::Update(float dt) {
  arkanoid.UpdateWorld(dt);
}
