#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <thread>
#include <stdio.h>
#include "utility.h"

using Shape = std::vector<std::vector<int>>;
typedef enum ShapeType {
	WALL,
	BALL,
	BOARD,
	REGULAR,
	H_LETTER,
	CROSS,
	T_LETTER,
	P_LETTER,

} shape_type;


class Block {
	Vector pos;
	int id;
	int width;
	int height;

protected:

	void ResizeShape(Shape& shape, int w, int h);
	shape_type block_shape;

public:
	void SetID(int id);
	int GetID() {
		return id;
	}
	void SetW(int width);
	void SetH(int height);
	Vector GetPos() {
		return pos;
	}
	shape_type GetBlockShape() {
		return block_shape;
	}
	virtual Shape Create_Shape() = 0;
	Block(const shape_type& SHAPE);
	virtual ~Block() {};
	

};

class Brick : public Block {

	

	public:
	Shape Create_Shape() override;
};

class Wall : public Block {

	public:
	Wall() : Block(WALL) {}
    Shape Create_Shape() override;

};

class Ball : public Block {
	Vector vel;
	double acceleration; //добавляем ускорение 

public:
	Ball() : Block(BALL) {}
	Shape Create_Shape() override;
	Vector GetVel() {
		return vel;
	}
	double GetAcc() {
		return acceleration;
	}
	void SetVel(const Vector& v) {
		vel = v;
	}

};

class Board : public Block {
	int vx;
	int dir;
	int size;
	int pos_x;

public:
	Board() : Block(BOARD) {}
	Shape Create_Shape() override;
	void SetV(int v) {
		vx = v;
	}
	int GetV() {
		return vx;
	}

	void ThrowBall();

};

class GameField {

	int width;
	int height;
	Shape Field;
	std::map <int, Block*> AllBlocks;

public:

	void AddBlock(int x, int y, Block* Block_to_add);
	void DeleteBlock(int x, int y, Block* Block_to_delete); //описать
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
	void ChangePosition(double dt); //put inside of an updateworld func
	void UpdateWorld(double dt);
	
	void SetCondition(bool condition);
	bool ReadyToExit();

};