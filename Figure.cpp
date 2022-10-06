#include "Figure.h"
#include "Function.h"
#include <Novice.h>


bool Figure::cheakdraw(Screen screen, Vec2 Position,bool Flag) {
	if (screen.Scroll.x + SCREEN_WIDTH / 2 + 100 > Position.x && screen.Scroll.x - SCREEN_WIDTH / 2 - 100 < Position.x && screen.Scroll.y + SCREEN_HEIGHT / 2 + 100 > Position.y && screen.Scroll.y - SCREEN_HEIGHT / 2 - 100 < Position.y && Flag == true) {
		return true;
	}
	else {
		return false;
	}
}

bool Figure::InScreen(Screen screen, Vec2 Position) {
	if (screen.Scroll.x + SCREEN_WIDTH / 2 + 100 > Position.x && screen.Scroll.x - SCREEN_WIDTH / 2 - 100 < Position.x && screen.Scroll.y + SCREEN_HEIGHT / 2 + 100 > Position.y && screen.Scroll.y - SCREEN_HEIGHT / 2 - 100 < Position.y) {
		return true;
	}
	else {
		return false;
	}
}

llipse::llipse() {

}
void llipse::set(int x,int y,int Radian) {
	position.x = x;
	position.y = y;
	//���a
	radian = Radian;
	//�F
	color = RED;
	flag = true;
}

//bool llipse::cheakdraw(Screen screen, Vec2 Position, int width, int height,bool Flag) {
//	if (screen.Scroll.x + width / 2 + 100 > Position.x && screen.Scroll.x - width / 2 - 100 < Position.x && screen.Scroll.y + height / 2 + 100 > Position.y && screen.Scroll.y - height / 2 - 100 < Position.y && Flag == true) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}

void llipse::draw(Screen& screen) {
	screen.DrawEllipse(position.x, position.y, radian, radian, 0.0f, color, kFillModeSolid);
}

Triangle::Triangle() {
	
}

void Triangle::set(int x,int y,int Radian) {
	//���W���
	position.x = x;
	position.y = y;
	//���a
	radian = Radian;
	//���_
	top_position.x = position.x;
	top_position.y = position.y + radian;
	//��
	left_position.x = position.x - radian;
	left_position.y = position.y - radian;
	//�E
	right_position.x = position.x + radian;
	right_position.y = position.y - radian;
	//�F
	color = GREEN;
	flag = true;

}

//bool Triangle::cheakdraw(Screen screen, Vec2 Position, int width, int height, bool Flag) {
//	if (screen.Scroll.x + width / 2 + 100 > Position.x && screen.Scroll.x - width / 2 - 100 < Position.x && screen.Scroll.y + height / 2 + 100 > Position.y && screen.Scroll.y - height / 2 - 100 < Position.y && Flag == true) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}

void Triangle::draw(Screen& screen) {
	screen.DrawTriangle(top_position.x, top_position.y, left_position.x, left_position.y, right_position.x, right_position.y, color, kFillModeSolid);
}

Quadrangle::Quadrangle() {
	
}

void Quadrangle::set(int x, int y,int Radian) {
	//���W���
	position.x = x;
	position.y = y;
	//���a
	radian = Radian;
	//����
	top_left_position.x = position.x - radian;
	top_left_position.y = position.y + radian;
	//�E��
	top_right_position.x = position.x + radian;
	top_right_position.y = position.y + radian;
	//����
	bottom_left_position.x = position.x - radian;
	bottom_left_position.y = position.y - radian;
	//�E��
	bottom_right_position.x = position.x + radian;
	bottom_right_position.y = position.y - radian;
	//�F
	color = BLUE;
	flag = true;

}

//bool Quadrangle::cheakdraw(Screen screen, Vec2 Position, int width, int height, bool Flag) {
//	if (screen.Scroll.x + width / 2 + 100 > Position.x && screen.Scroll.x - width / 2 - 100 < Position.x && screen.Scroll.y + height / 2 + 100 > Position.y && screen.Scroll.y - height / 2 - 100 < Position.y && Flag == true) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}

void Quadrangle::draw(Screen& screen) {
	screen.DrawQuad(top_left_position.x, top_left_position.y, top_right_position.x, top_right_position.y, bottom_left_position.x, bottom_left_position.y, bottom_right_position.x, bottom_right_position.y, 0.0f, 0.0f, radian, radian, 0, color);
}