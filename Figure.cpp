#include "Figure.h"
#include "Function.h"
#include <Novice.h>

Figure::Figure() {
	SRAND();
}

float Figure::RadianMin(Player& player) {
	return player.radius * 0.4;
}

float Figure::RadianMax(Player& player) {
	return player.radius * 1.5;
}

bool Figure::cheakdraw(Player player, Vec2 Position,bool Flag) {
	if (player.center.x + SCREEN_WIDTH / 2 + 100 > Position.x && player.center.x - SCREEN_WIDTH / 2 - 100 < Position.x && player.center.y + SCREEN_HEIGHT / 2 + 100 > Position.y && player.center.y - SCREEN_HEIGHT / 2 - 100 < Position.y && Flag == true) {
		return true;
	}
	else {
		return false;
	}
}

bool Figure::InScreen(Player player, Vec2 Position) {
	if (player.center.x + SCREEN_WIDTH / 2 + 100 > Position.x && player.center.x - SCREEN_WIDTH / 2 - 100 < Position.x && player.center.y + SCREEN_HEIGHT / 2 + 100 > Position.y && player.center.y - SCREEN_HEIGHT / 2 - 100 < Position.y) {
		return true;
	}
	else {
		return false;
	}
}

llipse::llipse() {

}
void llipse::set(Player& player) {
	position.x = RAND(-Figure::Area, Figure::Area);
	position.y = RAND(-Figure::Area, Figure::Area);
	//半径
	radian = RAND(Figure::RadianMin(player), Figure::RadianMax(player));
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

void llipse::respon(Player player) {
	flag = false;
	do {
		set(player);
	} while (InScreen(player, position));
}

void llipse::draw(Screen& screen) {
	screen.DrawEllipse(position.x, position.y, radian, radian, 0.0f, color, kFillModeSolid);
}

Triangle::Triangle() {
	
}

void Triangle::set(Player& player) {
	position.x = RAND(-Figure::Area, Figure::Area);
	position.y = RAND(-Figure::Area, Figure::Area);
	//半径
	radian = RAND(Figure::RadianMin(player), Figure::RadianMax(player));
	//頂点
	float theta = (float)Degree(RAND(0, 360));
	float left = 0;
	float right = 0;
	if (theta - Degree(120) <= 0.0f) {
		left = theta + Degree(120) - Degree(360);
	}
	else {
		left = theta + Degree(120);
	}

	if (left - Degree(120) <= 0.0f) {
		right = left + Degree(120) - Degree(360);
	}
	else {
		right = left + Degree(120);
	}
	
	//頂点
	top_position.x = position.x + cosf(theta) * radian;
	top_position.y = position.y + sinf(theta) * radian;
	//左
	left_position.x = position.x + cosf(left) * radian;
	left_position.y = position.y + sinf(left) * radian;
	//右
	right_position.x = position.x + cosf(right) * radian;
	right_position.y = position.y + sinf(right) * radian;
	//色
	color = GREEN;
	flag = true;

}

void Triangle::respon(Player player) {
	flag = false;
	do {
		set(player);
	} while (InScreen(player, position));
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

float Quadrangle::checkroll(float Theta) {
	float a = 0.0f;
	if (Theta - Degree(90) <= 0.0f) {
		return a = Theta - Degree(90) - Degree(360);
	}
	else {
		return a = Theta - Degree(90);
	}
}
void Quadrangle::set(Player& player) {
	position.x = RAND(-Figure::Area, Figure::Area);
	position.y = RAND(-Figure::Area, Figure::Area);
	//半径
	radian = RAND(Figure::RadianMin(player), Figure::RadianMax(player));
	//頂点
	float theta = (float)Degree(RAND(0, 360));
	top_right = checkroll(theta);
	bottom_left = checkroll(top_right);
	bottom_right = checkroll(bottom_left);
	//左上
	top_left_position.x = position.x + cosf(theta) * radian;
	top_left_position.y = position.y + sinf(theta) * radian;
	//右上
	top_right_position.x = position.x + cosf(top_right) * radian;
	top_right_position.y = position.y + sinf(top_right) * radian;
	//左下
	bottom_left_position.x = position.x + cosf(bottom_left) * radian;
	bottom_left_position.y = position.y + sinf(bottom_left) * radian;
	//右下
	bottom_right_position.x = position.x + cosf(bottom_right) * radian;
	bottom_right_position.y = position.y + sinf(bottom_right) * radian;
	//色
	color = BLUE;
	flag = true;

}

void Quadrangle::respon(Player player) {
	flag = false;
	do {
		set(player);
	} while (InScreen(player, position));
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
	screen.DrawQuad(top_left_position.x, top_left_position.y, top_right_position.x, top_right_position.y, bottom_right_position.x, bottom_right_position.y, bottom_left_position.x, bottom_left_position.y, 0.0f, 0.0f, radian, radian, 0, color);
}