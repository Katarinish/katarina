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
Block::Block(const shape_type& SHAPE) {
	block_shape = SHAPE;
	switch (SHAPE) {
		case WALL:
			width = 1;
			height = 1;
			break;
		case BALL:
			width = 2;
			height = 2;
			break;
		case BOARD:
			width = 4;
			height = 1;
			break;
		case REGULAR:
			width = 1;
			height = 4;
			break;
		case H_LETTER:
			width = 3;
			height = 3;
			break;
		case CROSS:
			width = 3;
			height = 3;
			break;
		case T_LETTER:
			width = 3;
			height = 2;
			break;
		case P_LETTER:
			width = 3;
			height = 3;
			break;
		default:
			break;
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
	shape_type br_type = GetBlockShape();
	Shape res;

	switch (br_type) {
		case REGULAR:
			ResizeShape(res, 4, 1); //
			int i = 0;
			while (i < 4) {
				res[0][i++] = GetID();
			}
			break;
		case H_LETTER:
			ResizeShape(res, 3, 3);
			int i = 0;
			while (i < 3) {
				res[i][0] = GetID();
				res[i][2] = GetID();
				i++;
			}
			res[1][1] = GetID();
			break;
		case CROSS:
			ResizeShape(res, 3, 3);
			int i = 0;
			while (i < 3) {
				res[i][1] = GetID();
				res[1][i] = GetID();
				i++;
			}
			break;
		case T_LETTER:
			ResizeShape(res, 2, 3);
			int i = 0;
			while (i < 3) {
				res[0][i++] = GetID();
			}
			res[1][1] = GetID();
			break;
		case P_LETTER:
			ResizeShape(res, 3, 3);
			int i = 0;
			while (i < 3) {
				res[0][i] = GetID();
				res[i][0] = GetID();
				res[i][2] = GetID();
				i++;
			}
			break;
		default:
			break;
	}

	return res;

}



//Ball methods
Shape Ball::Create_Shape() {
	Shape res;
	ResizeShape(res, 2, 2); 
	int i = 0;
	while (i < 2) {
		res[0][i] = GetID();
		res[1][i] = GetID();
		i++;
	}
	return res;
}

//Arkanoid methods
void Arkanoid::SetCondition(bool cond) {
	ready_to_exit = cond;
}
bool Arkanoid::ReadyToExit() {
	return ready_to_exit;
}
void Arkanoid::ChangePosition(double dt) {
	std::cin >> state;
	int new_x = 0;
	switch (state) {
		//left
		case 'd' :
			if (board.GetV() < 0)
				board.SetV(board.GetV()*(-1));
			new_x = board.GetX() + board.GetV()*dt;
			game_field.DeleteBlock(board.GetX(), board.GetY(), &board);
			board.SetX(new_x);
			game_field.AddBlock(board.GetX(), board.GetY(), &board);
			break;
		//right
		case 'a' :
			if (board.GetV() > 0)
				board.SetV(board.GetV*(-1));
			new_x = board.GetX() + board.GetV()*dt;
			game_field.DeleteBlock(board.GetX(), board.GetY(), &board);
			board.SetX(new_x);
			game_field.AddBlock(board.GetX(), board.GetY(), &board);
			break;
		case ' ' :
			if (!in_game)
				board.ThrowBall();
			else {
				//pause
			}
			break;
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

	for (int x = 0; x < w; x++) {
		game_field.AddBlock(x, 0, wall_block);
	}
	for (int y = 0; y < h; ++y) {
		game_field.AddBlock(0, y, wall_block);
		game_field.AddBlock(w - 1, y, wall_block);
	}
}	
void Arkanoid::UpdateWorld(double dt) {
	double time = 0;
	Vector bumped_block;
	double acc = ball.GetAcc();
	

	for (time = 0; time <= dt; time += 0.001) {
		auto pos = ball.GetPos();
		auto prev_pos = pos;
		auto vel = ball.GetVel();
		auto ball_vel = vel;
		Vector crossed_point;
		vel *= dt;
		pos += vel;

		auto* b = game_field.GetBlock(pos.X(), pos.Y());
		if (!b) {
			continue;
		}
		auto first_line = Find_line(pos, prev_pos); //ball's line
		auto block_pos = b->GetPos();
		
		crossed_side SIDE = block_pos.CrossedSide(first_line);
		switch (SIDE) {
			case TOP:
				ball.SetVel(Vector(ball_vel.X(), -ball_vel.Y()));

				break;

			case BOTTOM:
				ball.SetVel(Vector(ball_vel.X(), -ball_vel.Y()));

				break;

			case LEFT:
				ball.SetVel(Vector(-ball_vel.X(), ball_vel.Y()));
				break;

			case RIGHT:
				ball.SetVel(Vector(-ball_vel.X(), ball_vel.Y()));
				break;

		default:
			break;
		}


	}
	

}

void Arkanoid::Run() {
	Init(100,100);
	while (ReadyToExit()) {
		Draw();
		ChangePosition(dt);
		UpdateWorld(dt);
	}

};

