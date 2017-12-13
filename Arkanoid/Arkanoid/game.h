#pragma once

#include "gui/base_game_window.h"
#include "arkanoid/arkanoid.h"

class Game : public gui::BaseGameWindow {
public:
  Game();

  void Render(gdi::Graphics &canvas) override;
  void ProcessInput(const bool keys[256]);
  void Update(float dt);

private:
  Arkanoid arkanoid;
};
