#pragma once

#include <map>

#include "block.h"

class GameField {
 private:
  int width;
  int height;
  Shape Field;
  std::map<BlockID, Block*> AllBlocks;

 public:
  GameField(int w, int h);
  ~GameField();

  void AddBlock(int x, int y, Block* Block_to_add);
  void DeleteCell(int x, int y);
  Block* GetBlock(int x, int y);

  int GetWidth() const { return width; }
  int GetHeight() const { return height; }
};
