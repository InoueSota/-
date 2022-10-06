#include "Figure.h"
#include "Function.h"
#include <Novice.h>

llipse::llipse() {

}
void llipse::set(int x,int y,int Radian) {
	position.x = x;
	position.y = y;
	//���a
	radian = Radian;
	//�F
	color = RED;
}
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
}

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
}
void Quadrangle::draw(Screen& screen) {
	screen.DrawQuad(top_left_position.x, top_left_position.y, top_right_position.x, top_right_position.y, bottom_left_position.x, bottom_left_position.y, bottom_right_position.x, bottom_right_position.y, 0.0f, 0.0f, radian, radian, 0, color);
}