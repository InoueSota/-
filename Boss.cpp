#include "Boss.h"


Boss::Boss()
{
	position = { 0,0 };
	radian = 0;
	SRAND();
	rand_num=0;

	count=0;
	cooltime=300;
}

void Boss::set(Player& player, Screen screen, Map map) {

	//ポジションなど必要な値を引数を用いて代入するでやんす。
	position.y = screen.Worldcenter.y + 1000;
	position.x = 0;
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


}



void Boss::draw(Screen& screen) {
	screen.DrawEllipse(position.x, position.y, radian, radian, 0.0f, BLACK, kFillModeSolid);
}


