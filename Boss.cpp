#include "Boss.h"



void Boss::set(Player& player, Screen screen, Map map) {
	position.y = screen.Worldcenter.y + 1000;
	position.x = 0;
	radian = 500;
}

void Boss::Update(Enemy enemy,Player& player, Screen screen, Map map) {
	if (!enemy.easingflag) {
		count = 0;
		radian += 50;
	}
}

void Boss::draw(Screen& screen) {
	screen.DrawEllipse(position.x, position.y, radian, radian, 0.0f, BLACK, kFillModeSolid);
}


bool Enemy::IsInStage(float stage) {
	stage;//ステージの半径
	if (sqrt((powf(position.x, 2) + powf(position.y, 2)) + radian) < stage - radian) {
		return false;
	}
	return true;
}

float Enemy::set(Boss boss,Player& player, Screen screen, Map map) {
	
	radian = 250;
	do {
		position.x = RAND(-Area(player, screen, map), Area(player, screen, map));
		position.y = RAND(-Area(player, screen, map), Area(player, screen, map));
	} while (IsInStage(stage(map))&& sqrt(powf(boss.position.x - position.x, 2) + powf(boss.position.y - position.y, 2)) + boss.radian >= radian);

	color = BLACK;
	setflag = true;
	return -50;
}

void Enemy::Update(Boss boss) {
	if (!easingset) {
			start = position;
			end = boss.position;
			easingset = true;
			easingflag = true;
			t = 0.0f;
	}
	if (easingflag) {
		t += 0.002;
		Easing::easeInSine(t);
		position.x = (1.0f - t) * start.x + t * end.x;
		position.y = (1.0f - t) * start.y + t * end.y;
		if (t >= 1) {
			easingflag = false;
			easingset = false;
			count = 0;
			t = 0.0f;
			setflag = false;
		}
	}
	
}

void Enemy::draw(Screen& screen) {
	screen.DrawEllipse(position.x, position.y, radian, radian, 0.0f, BLACK, kFillModeSolid);
}