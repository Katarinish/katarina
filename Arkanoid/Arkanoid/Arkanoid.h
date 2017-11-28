#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <thread>
#include <stdio.h>

using Shape = std::vector<std::vector<int>>;

class Block {
	int id;
	int width;
	int height;
	Shape shape; // pointer or object?

public:
	void SetID(int id);
	int GetID() {
		return id;
	}
	void SetW(int width);
	void SetH(int height);
	void SetShape(Shape& shape); //Shape& or just Shape? put inside of a createshape func?
	void ResizeShape(Shape& shape, int w, int h);
	virtual Shape Create_Shape() = 0; // return Shape& ?
	virtual ~Block() {};
	

};

class Brick : public Block {

	int brick_type;

	public:
		//определить конструктор по полю brick_type ?
	Shape Create_Shape() override;
};

class Wall : public Block {

	public:
    Shape Create_Shape() override;

};

class Ball : public Block {
	int vx;
	int vy;
	int acceleration;

public:
	Shape Create_Shape() override;

};

class Board : public Block {
	int vx;
	int dir;
	int size;
	int pos_x;

public:
	Shape Create_Shape() override;
	void ThrowBall();

};

class GameField {

	int width;
	int height;
	Shape Field;
	std::map <int, Block*> AllBlocks;

public:

	void AddBlock(int x, int y, Block* Block_to_add);
	Block* GetBlock(int x, int y);
	void Set_WH(int w, int h);
	int GetWidth() const {
		return width;
	}
	int GetHeight() const {
		return height;
	}
};

class Arkanoid {

	GameField game_field;
	Ball ball;
	Board board;

	bool in_game;
	char state;
	double dt;
	bool ready_to_exit;


public:
	void Run();
	void Init(int w, int h);
	void Draw();
	void ChangePosition();
	void UpdateWorld(double dt);
	
	void SetCondition(bool condition);
	bool ReadyToExit();

};