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

/*�@����������֐��@*/
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

/*�@main.cpp�ō��W�����悤���邽�߂Ɏ擾����֐��@*/
void Player::SetPlayers(Player& players) {
	players.pos = player->pos;
	players.center = player->center;
	players.deg = player->deg;
}

/*�@�Y�[���̒l��ݒ肷��֐��@*/
void Player::SetZoom(Screen& screen, Player& players) {
	Vec2 tmp(1.0f, 1.0f);
	tmp.x /= players.radius / 30;
	tmp.y /= players.radius / 30;
	screen.Zoom = tmp;
}

/*�@�~�^���̊֐��@*/
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


/*�@�~�^������~��ύX����ۂ̓x���̐ݒ肷��֐��@*/
//CircleB��Degree�����߂�֐�
void CircleA::SetDegree() {

	circleA.tmppos = circleA.add;
	circleB.tmppos = {-1,0};

	float dp = circleA.tmppos.Dot(circleB.tmppos);
	float cp = circleA.tmppos.Cross(circleB.tmppos);
	float angleAB = Radian(atan2(cp, dp));

	circleB.deg = -angleAB;

}
//CircleA��Degree�����߂�֐�
void CircleB::SetDegree() {

	circleA.tmppos = {1,0};
	circleB.tmppos = circleB.add;

	float dp = circleA.tmppos.Dot(circleB.tmppos);
	float cp = circleA.tmppos.Cross(circleB.tmppos);
	float angleAB = Radian(atan2(cp, dp));

	circleA.deg = angleAB + 180;
}



/*�@�X�N���[�����W��ݒ肷��֐��@*/
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



/*�@�֐����܂Ƃ߂�֐��@*/
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

/*�@�`��֐��@*/
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

	//�A�E�g���C��
	screen.DrawEllipse(circleA.pos.x, circleA.pos.y, players.radius + 5 / screen.Zoom.x, players.radius + 5 / screen.Zoom.x, 0.0f, BLACK, kFillModeSolid);
	screen.DrawEllipse(circleB.pos.x, circleB.pos.y, players.radius + 5 / screen.Zoom.x, players.radius + 5 / screen.Zoom.x, 0.0f, BLACK, kFillModeSolid);
	screen.DrawQuad2(outtmp, 0, 0, 0, 0, 0, BLACK);
	//�{�́i�I�����W�F�j
	screen.DrawEllipse(circleA.pos.x, circleA.pos.y, players.radius, players.radius, 0.0f, 0xFF6E00FF, kFillModeSolid);
	screen.DrawEllipse(circleB.pos.x, circleB.pos.y, players.radius, players.radius, 0.0f, 0xFF6E00FF, kFillModeSolid);
	screen.DrawQuad2(tmp, 0, 0, 0, 0, 0, 0xFF6E00FF);
	//���S�_
	screen.DrawEllipse(players.center.x, players.center.y, players.radius - 20 / screen.Zoom.x, players.radius - 20 / screen.Zoom.y, 0.0f, 0xFFFF00FF, kFillModeSolid);
}
