#include "game_field.h"

GameField::GameField(int w, int h) : width(w), height(h) {
  Field.resize(width);
  for (auto& it : Field) {
    it.resize(height);
  }
}

GameField::~GameField() {
  // TODO(kk): implement it.
}

void GameField::AddBlock(int x, int y, Block* block) {
  AllBlocks[block->GetID()] = block;
  Shape res = block->CreateShape();

  for (int i = 0; i < res.size(); i++) {
    for (int j = 0; j < res[i].size(); j++) {
      if (res[i][j])
        if (x + i < width && y + i < height) {
          Field[x + i][y + j] = res[i][j];
        }
    }
  }
}

Block* GameField::GetBlock(int x, int y) {
  if (x < 0 || x >= width)
    return nullptr;
  if (y < 0 || y >= height)
    return nullptr;
  if (!Field[x][y])
    return nullptr;
  return AllBlocks[Field[x][y]];
}

void GameField::DeleteCell(int x, int y) {
  if (auto* block = GetBlock(x, y)) {
    if (block->IsDeletable()) {
      Field[x][y] = 0;
    }
  }
}
