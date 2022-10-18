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
	Longpressframe = 0;
	isLongpress = false;
	Length = 300;
	incDeg = 3.0f;
	isScroll = false;
	tmpCenpos = { 0,0 };
	tmpMovepos = { 0,0 };
	Scrolleasingt = 0.0f;
	ScrollincT = 0.1;
}

/*　main.cppで座標を使用するために取得する関数　*/
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
	if (prekeys != 0 && keys == 0 && isScroll == false && players.isLongpress == false){
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
	if (prekeys != 0 && keys == 0 && isScroll == false && players.isLongpress == false) {
		player->SetDegree();
		if (player == &circleA) {
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
	if (keys) {
		players.Longpressframe++;
		if (players.Longpressframe == 30) {
			players.Reverse *= -1;
			players.isLongpress = true;
		}
	}
	if (prekeys == 0 && keys == 0) {
		players.Longpressframe = 0;
		players.isLongpress = false;
	}
	player->CircleProcess(players);
}

/*　描画関数　*/
void Player::Draw(Screen& screen, Player& players) {
	Quad tmp, outtmp, ReverseGaugetmp, op{
		{ 0, -(players.radius - 10)},
		{ static_cast<float>(players.Length), -(players.radius - 10)},
		{ 0,  (players.radius - 10)},
		{ static_cast<float>(players.Length),(players.radius - 10)}
	}, outop{
		{ 0, -(players.radius - 5)},
		{ static_cast<float>(players.Length), -(players.radius - 5)},
		{ 0,  (players.radius - 5)},
		{ static_cast<float>(players.Length), (players.radius - 5)}
	}, ReverseGaugeop{
		{ 0, -(players.radius - 5)},
		{ static_cast<float>(players.Length) / 30 * players.Longpressframe, -(players.radius - 5)},
		{ 0,  (players.radius - 5)},
		{ static_cast<float>(players.Length) / 30 * players.Longpressframe, (players.radius - 5)}
	};
	Matrix33 mat, mat2;
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
	mat2 = Matrix33::Identity();
	mat2 = Matrix33::MakeScaling(screen.Zoom);
	mat2 = Matrix33::MakeRotation(Degree(90));
	mat2 *= Matrix33::MakeTranslation(players.center.x + 100, players.center.y - players.Length / 2);
	ReverseGaugetmp.LeftTop = ReverseGaugeop.LeftTop * mat2;
	ReverseGaugetmp.RightTop = ReverseGaugeop.RightTop * mat2;
	ReverseGaugetmp.LeftBottom = ReverseGaugeop.LeftBottom * mat2;
	ReverseGaugetmp.RightBottom = ReverseGaugeop.RightBottom * mat2;

	//スペースキーを押したときに波紋を出す
	for (int i = 0; i < RIPPLES_MAX; i++){
		if (isExist[i] == true){
			screen.DrawEllipse(Rpos[i].x, Rpos[i].y, Rradius[i], Rradius[i], 0.0f, Rcolor[i], kFillModeSolid);
		}
	}
	//リバースゲージ
	if (players.isLongpress == false) {
		screen.DrawQuad2(ReverseGaugetmp, 0, 0, 0, 0, 0, 0x555555FF);
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

//void Player::Draw_Rand_Skin(Screen& screen, char prekeys, char keys)
//{
//	
//	int gra = 0;
//	int Rand = 0;
//	bool change = false;
//	int aisu_atari = Novice::LoadTexture("./resource/aisu_atari.png");
//	int aisu_hazure = Novice::LoadTexture("./resource/aisu_hazuret.png");
//	int waribashi= Novice::LoadTexture("./resource/waribashi.png");
//	if (prekeys == 0 && keys&&change==false){
//		change = true;
//
//	}
//	if (change == true) {
//		Rand = RAND(0, 2);
//		change = false;
//	}
//
//	if (Rand == 0) {
//		gra = waribashi;
//	}
//	if (Rand == 1) {
//		gra = aisu_hazure;
//	}
//	if (Rand == 2) {
//		gra = aisu_atari;
//	}
//
//	Quad tmp, outtmp, op{
//		{ 0, -radius},
//		{ static_cast<float>(Length), -(radius - 10)},
//		{ 0,  radius},
//		{ static_cast<float>(Length), (radius - 10)}
//	}, outop{
//		{ 0, -radius - 5 / screen.Zoom.x},
//		{ static_cast<float>(Length), -(radius - 15) / screen.Zoom.x},
//		{ 0, radius + 5 / screen.Zoom.x},
//		{ static_cast<float>(Length), (radius - 15) / screen.Zoom.x}
//	};
//	Matrix33 mat;
//	mat = Matrix33::Identity();
//	mat = Matrix33::MakeScaling(screen.Zoom);
//	mat = Matrix33::MakeRotation(Degree(deg));
//	mat *= Matrix33::MakeTranslation(center);
//	tmp.LeftTop = op.LeftTop * mat;
//	tmp.RightTop = op.RightTop * mat;
//	tmp.LeftBottom = op.LeftBottom * mat;
//	tmp.RightBottom = op.RightBottom * mat;
//	outtmp.LeftTop = outop.LeftTop * mat;
//	outtmp.RightTop = outop.RightTop * mat;
//	outtmp.LeftBottom = outop.LeftBottom * mat;
//	outtmp.RightBottom = outop.RightBottom * mat;
//
//
//	
//	screen.DrawQuad( tmp.RightTop.x, tmp.RightTop.y, tmp.RightBottom.x, tmp.RightBottom.y, tmp.LeftTop.x, tmp.LeftTop.y, tmp.LeftBottom.x, tmp.LeftBottom.y, 0, 0, 90, 700, gra, WHITE);
//	
//}

void Player::Ripples(Screen& screen, Player& players, char prekeys, char keys) {
	for (int i = 0; i < RIPPLES_MAX; i++) {
		if (prekeys != 0 && keys == 0 && isExist[i] == false && isScroll == false && players.isLongpress == false) {
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
