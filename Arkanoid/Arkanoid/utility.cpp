#include "utility.h"

crossed_side Vector::CrossedSide(const Vector& first_line){
	auto second_line = first_line;

	Vector top_right(x + 1, y);
	Vector bottom_left(x, y + 1);
	Vector bottom_right(x + 1, y + 1);

	second_line = Find_line(*this, top_right);
	auto crossed_point = Crossed_point(first_line, second_line);
	if (If_crossed(crossed_point)) { //если пересеклось c верхней границей
		return TOP;
	}

	second_line = Find_line(*this, bottom_left);
	auto crossed_point = Crossed_point(first_line, second_line);
	if (If_crossed(crossed_point)) { //если пересеклось c левой границей
		return LEFT;
	}

	second_line = Find_line(bottom_left, bottom_right);
	auto crossed_point = Crossed_point(first_line, second_line);
	if (If_crossed(crossed_point)) { //если пересеклось c нижней границей
		return BOTTOM;
	}
	
	second_line = Find_line(bottom_right, top_right);
	auto crossed_point = Crossed_point(first_line, second_line);
	if (If_crossed(crossed_point)) { //если пересеклось с правой границей
		return RIGHT;
	}
}