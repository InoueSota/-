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
	//半径
	radian = Radian;
	//色
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
	//座標代入
	position.x = x;
	position.y = y;
	//半径
	radian = Radian;
	//頂点
	top_position.x = position.x;
	top_position.y = position.y + radian;
	//左
	left_position.x = position.x - radian;
	left_position.y = position.y - radian;
	//右
	right_position.x = position.x + radian;
	right_position.y = position.y - radian;
	//色
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
	//座標代入
	position.x = x;
	position.y = y;
	//半径
	radian = Radian;
	//左上
	top_left_position.x = position.x - radian;
	top_left_position.y = position.y + radian;
	//右上
	top_right_position.x = position.x + radian;
	top_right_position.y = position.y + radian;
	//左下
	bottom_left_position.x = position.x - radian;
	bottom_left_position.y = position.y - radian;
	//右下
	bottom_right_position.x = position.x + radian;
	bottom_right_position.y = position.y - radian;
	//色
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