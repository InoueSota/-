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
	radius = 50;
	Reverse = 1;
	Length = 300;
	isScroll = false;
	tmpCenpos = { 0,0 };
	tmpMovepos = { 0,0 };
	easingt = 0.0f;
	incT = 0.04;
}

/*�@main.cpp�ō��W�����悤���邽�߂Ɏ擾����֐��@*/
void Player::SetPlayers(Player& players) {
	players.pos = player->pos;
	players.center = player->center;
}

/*�@�Y�[���̒l��ݒ肷��֐��@*/
void Player::SetZoom(Screen& screen, Player& players) {
	Vec2 tmp(1.0f, 1.0f);
	tmp.x /= players.radius / 50;
	tmp.y /= players.radius / 50;
	screen.Zoom = tmp;
}

/*�@�~�^���̊֐��@*/
void CircleA::CircleProcess(Player& players) {
	incDeg = 2 * players.Reverse;
	circleA.deg += incDeg;
	circleA.add.x = cosf(Degree(circleA.deg));
	circleA.add.y = sinf(Degree(circleA.deg));
	circleA.pos = circleA.center + circleA.add * players.Length;
	circleB.center = circleA.pos;
	player->pos = circleA.pos;
	player->center = circleA.center;
}
void CircleB::CircleProcess(Player& players) {
	incDeg = 2 * players.Reverse;
	circleB.deg -= incDeg;
	circleB.add.x = cosf(Degree(circleB.deg));
	circleB.add.y = sinf(Degree(circleB.deg));
	circleB.pos = circleB.center + circleB.add * players.Length;
	circleA.center = circleB.pos;
	player->pos = circleB.pos;
	player->center = circleB.center;
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
	screen.DrawLine(circleA.pos.x, circleA.pos.y, circleB.pos.x, circleB.pos.y, BLACK);
	screen.DrawEllipse(circleA.pos.x, circleA.pos.y, players.radius, players.radius, 0.0f, BLACK, kFillModeSolid);
	screen.DrawEllipse(circleB.pos.x, circleB.pos.y, players.radius, players.radius, 0.0f, BLACK, kFillModeSolid);
}
