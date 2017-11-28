#include "Arkanoid.h"


//Block methods
void Block::SetID(int id) {
	this->id = id;
}
void Block::SetW(int width) {
	this->width = width;
}
void Block::SetH(int height) {
	this->height = height;
}
void Block::SetShape(Shape& shape) {
	this->shape = shape;
}
void Block::ResizeShape(Shape& shape, int w, int h) {
	shape.resize(h);
	for (auto& it : shape) {
		it.resize(w);
	}
}

//Wall methods
Shape Wall::Create_Shape() {
	Shape res;
	res.push_back({ GetID() });
	return res;
}

//Brick methods
Shape Brick::Create_Shape() {
	int br_type;
	Shape res; // сразу же set_shape? тогда в ресайз не передаем ссылку на шейп

	br_type = rand() % 5 + 1; //1..5
	switch (br_type) {
		case 1:
			ResizeShape(res, 4, 1); //через GetW & GetH? or put SetWH inside of case or constructor?
			int i = 0;
			while (i < 4) {
				res[0][i++] = GetID();
			}
			break;
		case 2:
			ResizeShape(res, 3, 3);
			int i = 0;
			while (i < 3) {
				res[i][0] = GetID();// id?
				res[i][2] = GetID();
				i++;
			}
			res[1][1] = GetID();
			break;
		case 3:
			ResizeShape(res, 3, 3);
			int i = 0;
			while (i < 3) {
				res[i][1] = GetID();
				res[1][i] = GetID();
				i++;
			}
			break;
		case 4:
			ResizeShape(res, 2, 3);
			int i = 0;
			while (i < 3) {
				res[0][i++] = GetID();
			}
			res[1][1];
			break;
		case 5:
			ResizeShape(res, 2, 3);
			int i = 0;
			while (i < 3) {
				res[0][i] = GetID();
				res[i][0] = GetID();
				res[i][2] = GetID();
			}
			break;
		default:
			break;
	}

	return res;

}


//Board methods

//Ball methods

//GameField methods

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
void GameField::Set_WH(int w, int h) {
	Field.resize(h);
	for (auto& it : Field) {
		it.resize(w);
	}
}

//Arkanoid methods
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
				board.ThrowBall();
			else 
				//pause


		default :

	}
}
void Arkanoid::Init(int w, int h) {

	int uniq_id = 1;
	game_field.Set_WH(w, h);

	//Borders Inition
	std::vector<Wall*> border_blocks;

	auto* wall_block = new Wall;
	wall_block->SetID(uniq_id);
	wall_block->SetW(1);
	wall_block->SetH(1);
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