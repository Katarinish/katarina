#pragma once

#include "../gui/base_game_window.h"
#include "ball.h"
#include "board.h"
#include "game_field.h"

enum class PressedButton {
	LEFT,
	RIGHT,
};


class Arkanoid {
 private:
  GameField game_field;
  Ball ball;
  Board board;

  bool in_game;
  char state;
  double dt;
  bool ready_to_exit;

  void Init();

 public:
  Arkanoid();
  ~Arkanoid();

  void Run();
  void Draw(gdi::Graphics& canvas);
  void UpdateWorld(double dt);


  // TODO(kk): Process user input.
  void ProcessUserInput(PressedButton state);

  bool ReadyToExit();
};
