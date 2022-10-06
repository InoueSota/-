#include "Figure.h"
#include "Function.h"
#include <Novice.h>

llipse::llipse() {
	//座標代入
	position.x = RAND(-5000, 5000);
	position.y = RAND(-5000, 5000);
	//半径
	radian.x = 10;
	radian.y = 10;
	//色
	color = RED;
}

void llipse::draw(Screen& screen) {
	screen.DrawEllipse(position.x, position.y, radian.x, radian.y, 0.0f, color, kFillModeSolid);
}

Triangle::Triangle() {
	//座標代入
	position.x = RAND(-5000, 5000);
	position.y = RAND(-5000, 5000);
	//半径
	radian.x = 10;
	radian.y = 10;
	//頂点
	top_position.x = position.x;
	top_position.y = position.y + radian.x;
	//左
	left_position.x = position.x - radian.x;
	left_position.y = position.y - radian.y;
	//右
	right_position.x = position.x - radian.x;
	right_position.y = position.y - radian.y;
	//色
	color = GREEN;
}

void Triangle::draw(Screen& screen) {
	screen.DrawTriangle(top_position.x, top_position.y, left_position.x, left_position.y, right_position.x, right_position.y, color, kFillModeSolid);
}

Quadrangle::Quadrangle() {
	//座標代入
	position.x = RAND(-5000, 5000);
	position.y = RAND(-5000, 5000);
	//半径
	radian.x = 10;
	radian.y = 10;
	//左上
	top_left_position.x = position.x - radian.x / 2;
	top_left_position.y = position.y + radian.y / 2;
	//右上
	top_right_position.x = position.x + radian.x / 2;
	top_right_position.y = position.y + radian.y / 2;
	//左下
	bottom_left_position.x = position.x - radian.x / 2;
	bottom_left_position.y = position.y - radian.y / 2;
	//右下
	bottom_right_position.x = position.x + radian.x / 2;
	bottom_right_position.y = position.y - radian.y / 2;
	//色
	color = BLUE;
}

void Quadrangle::draw(Screen& screen) {
	screen.DrawQuad(top_left_position.x, top_left_position.y, top_right_position.x, top_right_position.y, bottom_left_position.x, bottom_left_position.y, bottom_right_position.x, bottom_right_position.y, 0.0f, 0.0f, radian.x, radian.y, 0, color);
}