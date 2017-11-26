#include "Arkanoid.h"


Shape Wall::Create_Shape() {
	Shape res;
	res.push_back({ GetID() });
	return res;
}


void GameField::AddBlock(int x, int y, Block* block) {
	AllBlocks[block->GetID()] = block;
	Shape res = block->Create_Shape();
	for (int i = 0; i < res.size(); i++) {
		for (int j = 0; j < res[i].size(); j++) {
			if (res[i][j])
				Field[x + i][y + j] = res[i][j];
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

void Arkanoid::SetCondition(bool cond) {
	ready_to_exit = cond;
}
bool Arkanoid::ReadyToExit() {
	return ready_to_exit;
}

void Arkanoid::ChangePosition() {
	std::cin >> state;
	switch (state) {
		case 'd' :


		
		case 'a' :

		
		case ' ' :
			if (!in_game)
				platform.ThrowBall();
			else 
				//pause


		default :

	}
}

void GameField::Set_W_H(int w, int h) {
	Field.resize(w);
	for (auto& it : Field) {
		it.resize(h);
	}
}

void Arkanoid::Init(int w, int h) {

	int uniq_id = 1;
	game_field.Set_W_H(w, h);

	//Borders Inition
	std::vector<Wall*> border_blocks;

	auto* wall_block = new Wall;
	wall_block->SetID(uniq_id);
	
	for (int x = 0; x < w; x++) {
		game_field.AddBlock(x, 0, wall_block);
	}
	for (int y = 0; y < h; ++y) {
		game_field.AddBlock(0, y, wall_block);
		game_field.AddBlock(w - 1, y, wall_block);
	}
}	


void Arkanoid::Run() {
	Init(100,100);
	while (ReadyToExit()) {
		Draw();
		ChangePosition();
		UpdateWorld(dt);
	}

};