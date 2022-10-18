#include "Boss.h"


Boss::Boss()
{
	position = { 0,0 };
	radian = 0;
	SRAND();
	rand_num=0;
	shild = 3;
	count=0;
	cooltime=300;
}

void Boss::set(Vec2 pos ) {

	//ポジションなど必要な値を引数を用いて代入するでやんす。
	position = pos;
	radian = 500;

}

void Boss::Rand_Move()
{
	//ランダムで何をするか今は三分ただけど確率を操るのもあり（運命の指揮者と名付ける）
	rand_num=RAND(1, 3);

	if (rand_num == 1) {
		pattern_1 = true;
	}
	if (rand_num == 2) {
		pattern_2 = true;
	}
	if (rand_num == 3) {
		pattern_3 = true;
	}
}

void Boss::Result()
{
	//攻撃パターンの設定
	if (pattern_1 == true) {

	}

}

void Boss::Keep_Up(Player& player)
{
	//プレイヤーについていく関数使わないかもしれない
	Vec2 vel = (player.center - position).Normalized();
	position += vel;

}



void Boss::draw(Screen& screen) {
	
	screen.DrawEllipse(position.x, position.y, radian, radian, 0.0f, BLACK, kFillModeSolid);
	if (shild >= 1) {
		screen.DrawEllipse(position.x, position.y, radian/10, radian/10, 0.0f, RED, kFillModeSolid);
		if (shild >= 2) {
			screen.DrawTriangle(position.x, position.y + 100, position.x - 100, position.y - 50, position.x + 100, position.y - 50, GREEN, kFillModeSolid);

		}
		
				
		
	}
	
}


