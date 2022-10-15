#include "Player.h"

CircleA circleA;
CircleB circleB;
Player* player = &circleA;


Player::Player()
{
	Player::Init();
	SRAND();
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
	radius = 30;
	Reverse = 1;
	Length = 300;
	incDeg = 2.0f;
	isScroll = false;
	tmpCenpos = { 0,0 };
	tmpMovepos = { 0,0 };
	Scrolleasingt = 0.0f;
	ScrollincT = 0.05;
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
	tmp.x /= players.radius / 30;
	tmp.y /= players.radius / 30;
	screen.Zoom = tmp;
}

/*　円運動の関数　*/
void CircleA::CircleProcess(Player& players) {
	
	circleA.deg += incDeg;
	circleA.deg += players.incDeg * players.Reverse;
	circleA.add.x = cosf(Degree(circleA.deg));
	circleA.add.y = sinf(Degree(circleA.deg));
	circleA.pos = circleA.center + circleA.add * players.Length;
	circleB.center = circleA.pos;
	player->pos = circleA.pos;
	player->center = circleA.center;
	player->deg = circleA.deg;
}
void CircleB::CircleProcess(Player& players) {
	
	circleB.deg -= incDeg;
	circleB.deg -= players.incDeg * players.Reverse;
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
		Scrolleasingt += ScrollincT;
		Clamp(Scrolleasingt, 0.0f, 1.0f);
		screen.Scroll.x = Lerp(Easing::easeOutQuint(Scrolleasingt), players.tmpMovepos.x) + players.tmpCenpos.x;
		screen.Scroll.y = Lerp(Easing::easeOutQuint(Scrolleasingt), players.tmpMovepos.y) + players.tmpCenpos.y;
		if (Scrolleasingt >= 1.0f){
			isScroll = false;
			Scrolleasingt = 0.0f;
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
	Quad tmp, outtmp, op{
		{ 0, -players.radius},
		{ static_cast<float>(players.Length), -players.radius},
		{ 0,  players.radius},
		{ static_cast<float>(players.Length), players.radius}
	}, outop{
		{ 0, -players.radius - 5 / screen.Zoom.x},
		{ static_cast<float>(players.Length), -players.radius - 5 / screen.Zoom.x},
		{ 0,  players.radius + 5 / screen.Zoom.x},
		{ static_cast<float>(players.Length), players.radius + 5 / screen.Zoom.x}
	};
	Matrix33 mat;
	mat = Matrix33::Identity();
	mat = Matrix33::MakeScaling(screen.Zoom);
	mat = Matrix33::MakeRotation(Degree(players.deg));
	mat *= Matrix33::MakeTranslation(players.center);
	tmp.LeftTop = op.LeftTop * mat;
	tmp.RightTop = op.RightTop * mat;
	tmp.LeftBottom = op.LeftBottom * mat;
	tmp.RightBottom = op.RightBottom * mat;
	outtmp.LeftTop = outop.LeftTop * mat;
	outtmp.RightTop = outop.RightTop * mat;
	outtmp.LeftBottom = outop.LeftBottom * mat;
	outtmp.RightBottom = outop.RightBottom * mat;

	//スペースキーを押したときに波紋を出す
	for (int i = 0; i < RIPPLES_MAX; i++){
		if (isExist[i] == true){
			screen.DrawEllipse(Rpos[i].x, Rpos[i].y, Rradius[i], Rradius[i], 0.0f, Rcolor[i], kFillModeSolid);
		}
	}
	//アウトライン
	screen.DrawEllipse(circleA.pos.x, circleA.pos.y, players.radius + 5 / screen.Zoom.x, players.radius + 5 / screen.Zoom.x, 0.0f, BLACK, kFillModeSolid);
	screen.DrawEllipse(circleB.pos.x, circleB.pos.y, players.radius + 5 / screen.Zoom.x, players.radius + 5 / screen.Zoom.x, 0.0f, BLACK, kFillModeSolid);
	screen.DrawQuad2(outtmp, 0, 0, 0, 0, 0, BLACK);
	//本体（オレンジ色）
	screen.DrawEllipse(circleA.pos.x, circleA.pos.y, players.radius, players.radius, 0.0f, 0xFF6E00FF, kFillModeSolid);
	screen.DrawEllipse(circleB.pos.x, circleB.pos.y, players.radius, players.radius, 0.0f, 0xFF6E00FF, kFillModeSolid);
	screen.DrawQuad2(tmp, 0, 0, 0, 0, 0, 0xFF6E00FF);
}

void Player::Draw_Rand_Skin(Screen& screen)
{
	int once = 0;
	int gra = 0;
	int aisu_atari = Novice::LoadTexture("./resource/aisu_atari.png");
	int aisu_hazure = Novice::LoadTexture("./resource/aisu_hazuret.png");
	/*if (once == 0) {
		int aisu_atari = Novice::LoadTexture("./resource/aisu_atari.png");
		int aisu_hazure = Novice::LoadTexture("./resource/aisu_hazuret.png");
		once = 1;
	}*/
	Quad tmp, outtmp, op{
		{ 0, -radius},
		{ static_cast<float>(Length), -radius},
		{ 0,  radius},
		{ static_cast<float>(Length), radius}
	}, outop{
		{ 0, -radius - 5 / screen.Zoom.x},
		{ static_cast<float>(Length), -radius - 5 / screen.Zoom.x},
		{ 0, radius + 5 / screen.Zoom.x},
		{ static_cast<float>(Length), radius + 5 / screen.Zoom.x}
	};
	Matrix33 mat;
	mat = Matrix33::Identity();
	mat = Matrix33::MakeScaling(screen.Zoom);
	mat = Matrix33::MakeRotation(Degree(deg));
	mat *= Matrix33::MakeTranslation(center);
	tmp.LeftTop = op.LeftTop * mat;
	tmp.RightTop = op.RightTop * mat;
	tmp.LeftBottom = op.LeftBottom * mat;
	tmp.RightBottom = op.RightBottom * mat;
	outtmp.LeftTop = outop.LeftTop * mat;
	outtmp.RightTop = outop.RightTop * mat;
	outtmp.LeftBottom = outop.LeftBottom * mat;
	outtmp.RightBottom = outop.RightBottom * mat;


	//screen.DrawQuad2(tmp, 0, 0, 90, 70, aisu_atari, WHITE);
	screen.DrawQuad( tmp.RightTop.x, tmp.RightTop.y, tmp.RightBottom.x, tmp.RightBottom.y, tmp.LeftTop.x, tmp.LeftTop.y, tmp.LeftBottom.x, tmp.LeftBottom.y, 0, 0, 90, 700, aisu_hazure, WHITE);
	//screen.DrawQuad(tmp.LeftTop.x, tmp.LeftTop.y, tmp.RightTop.x, tmp.RightTop.y, tmp.LeftBottom.x, tmp.LeftBottom.y, tmp.RightBottom.x, tmp.RightBottom.y, 0, 0, 90, 700, aisu_atari, WHITE);
	//screen.DrawSprite(tmp.LeftTop.x, tmp.LeftTop.y, aisu_atari, 1, 1, 0, WHITE);
}

void Player::Ripples(Screen& screen, Player& players, char prekeys, char keys) {
	for (int i = 0; i < RIPPLES_MAX; i++) {
		if (prekeys == 0 && keys && isExist[i] == false && isScroll == false) {
			Rpos[i] = players.center;
			Rradius[i] = players.radius;
			Rcolor[i] = 0x000000FF;
			Existtime[i] = 0.0f;
			isExist[i] = true;
			break;
		}
		if (isExist[i] == true) {
			Rradius[i] += 5 / screen.Zoom.x;
			Existtime[i] += 0.01f;
			Rcolor[i] = 0x00000000 | static_cast<int>((1.0f - Existtime[i]) * 0xFF + Existtime[i] * 0x00);
			if (Rcolor[i] == 0x00000000) {
				isExist[i] = false;
			}
		}
	}
}
