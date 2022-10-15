#include "Player.h"

CircleA circleA;
CircleB circleB;
Player* player = &circleA;


Player::Player()
{
	Player::Init();
}

Player::~Player()
{
}

/*　初期化する関数　*/
void Player::Init() {
	pos = { 0,0 };
	center = { pos.x,pos.y };
	add = { 0,0 };
	tmppos = { 0,0 };
	deg = 0;
	radius = 50;
	Reverse = 1;
	Length = 300;
	isScroll = false;
	tmpCenpos = { 0,0 };
	tmpMovepos = { 0,0 };
	easingt = 0.0f;
	incT = 0.05;
}

/*　main.cppで座標をしようするために取得する関数　*/
void Player::SetPlayers(Player& players) {
	players.pos = player->pos;
	players.center = player->center;
	players.deg = player->deg;
}

/*　ズームの値を設定する関数　*/
void Player::SetZoom(Screen& screen, Player& players) {
	Vec2 tmp(1.0f, 1.0f);
	tmp.x /= players.radius / 50;
	tmp.y /= players.radius / 50;
	screen.Zoom = tmp;
}

/*　円運動の関数　*/
void CircleA::CircleProcess(Player& players) {
	incDeg = 5 * players.Reverse;
	circleA.deg += incDeg;
	circleA.add.x = cosf(Degree(circleA.deg));
	circleA.add.y = sinf(Degree(circleA.deg));
	circleA.pos = circleA.center + circleA.add * players.Length;
	circleB.center = circleA.pos;
	player->pos = circleA.pos;
	player->center = circleA.center;
	player->deg = circleA.deg;
}
void CircleB::CircleProcess(Player& players) {
	incDeg = 5 * players.Reverse;
	circleB.deg -= incDeg;
	circleB.add.x = cosf(Degree(circleB.deg));
	circleB.add.y = sinf(Degree(circleB.deg));
	circleB.pos = circleB.center + circleB.add * players.Length;
	circleA.center = circleB.pos;
	player->pos = circleB.pos;
	player->center = circleB.center;
	player->deg = circleB.deg;
}


/*　円運動する円を変更する際の度数の設定する関数　*/
//CircleBのDegreeを求める関数
void CircleA::SetDegree() {

	circleA.tmppos = circleA.add;
	circleB.tmppos = {-1,0};

	float dp = circleA.tmppos.Dot(circleB.tmppos);
	float cp = circleA.tmppos.Cross(circleB.tmppos);
	float angleAB = Radian(atan2(cp, dp));

	circleB.deg = -angleAB;

}
//CircleAのDegreeを求める関数
void CircleB::SetDegree() {

	circleA.tmppos = {1,0};
	circleB.tmppos = circleB.add;

	float dp = circleA.tmppos.Dot(circleB.tmppos);
	float cp = circleA.tmppos.Cross(circleB.tmppos);
	float angleAB = Radian(atan2(cp, dp));

	circleA.deg = angleAB + 180;
}



/*　スクロール座標を設定する関数　*/
void Player::SetScrollPos(Screen& screen, Player& players, char prekeys, char keys) {
	if (prekeys == 0 && keys && isScroll == false){
		isScroll = true;
	}
	if (isScroll == true){
		easingt += incT;
		Clamp(easingt, 0.0f, 1.0f);
		screen.Scroll.x = Lerp(Easing::easeOutQuint(easingt), players.tmpMovepos.x) + players.tmpCenpos.x;
		screen.Scroll.y = Lerp(Easing::easeOutQuint(easingt), players.tmpMovepos.y) + players.tmpCenpos.y;
		if (easingt >= 1.0f){
			isScroll = false;
			easingt = 0.0f;
		}
	}
}



/*　関数をまとめる関数　*/
void Player::Process(Player& players, char prekeys, char keys, char predik_d, char dik_d) {
	if (predik_d == 0 && dik_d){
		players.Reverse *= -1;
	}
	if (prekeys == 0 && keys && isScroll == false) {
		player->SetDegree();
		if (player == &circleA){
			players.tmpCenpos = circleB.pos;
			players.tmpMovepos = circleA.pos - players.tmpCenpos;
			player = nullptr;
			player = &circleB;
		}
		else if (player == &circleB) {
			players.tmpCenpos = circleA.pos;
			players.tmpMovepos = circleB.pos - players.tmpCenpos;
			player = nullptr;
			player = &circleA;
		}
	}
	player->CircleProcess(players);
}

/*　描画関数　*/
void Player::Draw(Screen& screen, Player& players) {
	Quad op{
		{ 0, -players.radius},
		{ static_cast<float>(players.Length), -players.radius},
		{ 0,  players.radius},
		{ static_cast<float>(players.Length), players.radius}
	};	
	Quad tmp;
	Matrix33 mat;
	mat = Matrix33::Identity();
	mat = Matrix33::MakeScaling(screen.Zoom);
	mat = Matrix33::MakeRotation(Degree(players.deg));
	mat *= Matrix33::MakeTranslation(players.center);
	tmp.LeftTop = op.LeftTop * mat;
	tmp.RightTop = op.RightTop * mat;
	tmp.LeftBottom = op.LeftBottom * mat;
	tmp.RightBottom = op.RightBottom * mat;

	screen.DrawLine(circleA.pos.x, circleA.pos.y, circleB.pos.x, circleB.pos.y, BLACK);
	screen.DrawEllipse(circleA.pos.x, circleA.pos.y, players.radius, players.radius, 0.0f, BLACK, kFillModeSolid);
	screen.DrawEllipse(circleB.pos.x, circleB.pos.y, players.radius, players.radius, 0.0f, BLACK, kFillModeSolid);
	screen.DrawQuad2(tmp, 0, 0, 0, 0, 0, BLACK);
}
