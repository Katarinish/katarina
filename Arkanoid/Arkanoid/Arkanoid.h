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
	Shape shape;

public:
	virtual ~Block() {};
	void SetID(int id);
	int GetID();
	void SetW(int width);
	void SetH(int height);
	virtual Shape Create_Shape() = 0;

};

class Brick : public Block {

	public:
	std::vector<std::vector<int>> Create_Shape() override;
};

class Wall : public Block {

	public:
    Shape Create_Shape() override;

};

class Ball : public Block {
	int vx;
	int vy;

public:
	Shape Create_Shape() override;

};

class Platform : public Block {
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
	void Set_W_H(int w, int h);
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
	Platform platform;

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