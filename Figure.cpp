#include "Figure.h"
#include "Function.h"
#include <Novice.h>

llipse::llipse() {
	//���W���
	position.x = RAND(-5000, 5000);
	position.y = RAND(-5000, 5000);
	//���a
	radian.x = 10;
	radian.y = 10;
	//�F
	color = RED;
}

void llipse::draw(Screen& screen) {
	screen.DrawEllipse(position.x, position.y, radian.x, radian.y, 0.0f, color, kFillModeSolid);
}

Triangle::Triangle() {
	//���W���
	position.x = RAND(-5000, 5000);
	position.y = RAND(-5000, 5000);
	//���a
	radian.x = 10;
	radian.y = 10;
	//���_
	top_position.x = position.x;
	top_position.y = position.y + radian.x;
	//��
	left_position.x = position.x - radian.x;
	left_position.y = position.y - radian.y;
	//�E
	right_position.x = position.x - radian.x;
	right_position.y = position.y - radian.y;
	//�F
	color = GREEN;
}

void Triangle::draw(Screen& screen) {
	screen.DrawTriangle(top_position.x, top_position.y, left_position.x, left_position.y, right_position.x, right_position.y, color, kFillModeSolid);
}

Quadrangle::Quadrangle() {
	//���W���
	position.x = RAND(-5000, 5000);
	position.y = RAND(-5000, 5000);
	//���a
	radian.x = 10;
	radian.y = 10;
	//����
	top_left_position.x = position.x - radian.x / 2;
	top_left_position.y = position.y + radian.y / 2;
	//�E��
	top_right_position.x = position.x + radian.x / 2;
	top_right_position.y = position.y + radian.y / 2;
	//����
	bottom_left_position.x = position.x - radian.x / 2;
	bottom_left_position.y = position.y - radian.y / 2;
	//�E��
	bottom_right_position.x = position.x + radian.x / 2;
	bottom_right_position.y = position.y - radian.y / 2;
	//�F
	color = BLUE;
}

void Quadrangle::draw(Screen& screen) {
	screen.DrawQuad(top_left_position.x, top_left_position.y, top_right_position.x, top_right_position.y, bottom_left_position.x, bottom_left_position.y, bottom_right_position.x, bottom_right_position.y, 0.0f, 0.0f, radian.x, radian.y, 0, color);
}