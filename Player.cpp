#include "Player.h"

CircleA circleA;
CircleB circleB;
Player* player = &circleA;


/*�@����������֐��@*/
void Player::Init() {
	deg = 0;
	radius = 25;
	Reverse = 1;
	Length = 300;
	isScroll = false;
	isTitleClear = false;
	Scrolleasingt = 0.0f;
	ScrollincT = 0.1;
	circleA.pos = { -(float)Length / 2, 0 };
	circleB.pos = { (float)Length / 2, 0 };
	circleA.center = { -(float)Length / 2, 0 };
	circleB.center = { (float)Length / 2, 0 };
	outcolor = 0xE5C210FF;
	color = 0x2B1247FF;
}

/*�@main.cpp�ō��W���g�p���邽�߂Ɏ擾����֐��@*/
void Player::SetPlayers(Player& players) {
	players.pos = player->pos;
	players.center = player->center;
	players.deg = player->deg;
	players.Length = players.radius * 12;
}

/*�@�Y�[���̒l��ݒ肷��֐��@*/
void Player::SetZoom(Screen& screen, Player& players, Title& title) {
	if (title.isTitleClear == false){
		screen.Zoom = { 0.7f, 0.7f };
	}
	if (title.isTitleClear == true){
		Vec2 tmp(1.0f, 1.0f);
		tmp.x /= players.radius / 25;
		tmp.y /= players.radius / 25;
		screen.Zoom = tmp;
	}
}

/*�@�~�^���̊֐��@*/
void CircleA::CircleProcess(Player& players) {
	circleA.deg -= players.incDeg * players.Reverse;
	circleA.add.x = cosf(Degree(circleA.deg));
	circleA.add.y = sinf(Degree(circleA.deg));
	circleA.pos = circleA.center + circleA.add * players.Length;
	circleB.center = circleA.pos;
	player->pos = circleA.pos;
	player->center = circleA.center;
	player->deg = circleA.deg;
}
void CircleB::CircleProcess(Player& players) {
	circleB.deg += players.incDeg * players.Reverse;
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

/*�@incDeg�̑��x��ω������鏈���֐��@*/
void Player::IncDegProcess(Player& players, char prekeys, char keys) {
	if (prekeys == 0 && keys != 0){
		players.incDeg = initVelo;
	}
	players.incDeg -= 0.04f;
	players.incDeg = Clamp(players.incDeg, 1.5f, initVelo);
}


/*�@�X�N���[�����W��ݒ肷��֐��@*/
void Player::SetScrollPos(Screen& screen, Player& players, char prekeys, char keys, Map& map) {
	if (prekeys == 0 && keys != 0 && isScroll == false && ((players.isTitleClear == true && players.pos.Length() <= map.radius) || (players.isTitleClear == false && (players.pos.Length() <= 3000))) && isPressSpace == true){
		isScroll = true;
	}
	if (isScroll == true){
		Scrolleasingt += (ScrollincT * kFrameMag);
		Scrolleasingt = Clamp(Scrolleasingt, 0.0f, 1.0f);
		screen.Scroll.x = Lerp(Easing::easeOutQuint(Scrolleasingt), players.tmpMovepos.x) + players.tmpCenpos.x;
		screen.Scroll.y = Lerp(Easing::easeOutQuint(Scrolleasingt), players.tmpMovepos.y) + players.tmpCenpos.y;
		if (Scrolleasingt >= 1.0f){
			isScroll = false;
			Scrolleasingt = 0.0f;
		}
	}
	if (isPressSpace == false){
		screen.Scroll = { 0,0 };
	}
	if (isPressSpace == false && prekeys == 0 && keys != 0) {
		screen.Scroll = { -150,0 };
		isPressSpace = true;
	}
}



void Player::SizeIncrease(Player& players) {
	players.radius += 0.8f;
}
void Player::SizeDecrease(Player& players,int wave) {
	if (wave == 0) {
		if (players.radius >= 25) {
			players.radius -= 0.05f;
		}
		else {
			players.radius = 25;
		}
	}
	else if (wave == 1) {
		if (players.radius >= 80) {
			players.radius -= 10;
		}
		else {
			players.radius = 80;
		}
	}
	else if (wave == 2) {
		if (players.radius >= 80) {
			players.radius -= 0.05f;
		}
		else {
			players.radius = 80;
		}
	}
	else if (wave == 3) {
		if (players.radius >= 80) {
			players.radius -= 10;
		}
		else {
			players.radius = 80;
		}
	}
}
void Player::MutekiTime() {

	//�t���O�ω��͂���
	Muteki_Timer++;
	Muteki_Timer = Clamp(Muteki_Timer, 0, 120);
	if (Muteki_Timer % 20 == 0) {
		isMutekiDisplay = true;
	}
	if (Muteki_Timer % 20 == 10) {
		isMutekiDisplay = false;
	}

	//�F�̕ω��͂���
	if (isMutekiDisplay == false){
		outcolor = 0xFFFFFF08;
		color = 0xFFFFFF08;
	}
	if (isMutekiDisplay == true){
		outcolor = 0xFFFFFF02;
		color = 0xFFFFFF02;
	}
	if (Muteki_Timer == 120) {
		isMutekiDisplay = false;
		outcolor = 0xE5C210FF;
		color = 0x2B1247FF;
		Muteki_Timer = 0;
		Muteki = false;
	}
}



/*�@�֐����܂Ƃ߂�֐��@*/
void Player::Process(Player& players, char prekeys, char keys, Title& title, GameClear& Gcear, Screen& screen, Map& map) {
	if (Gcear.isGameClear == false){
		if (isPressSpace == false) {
			circleA.pos.y = sinf(title.theta) * 20;
			circleB.pos.y = sinf(title.theta) * 20;
			circleA.center.y = sinf(title.theta) * 20;
			circleB.center.y = sinf(title.theta) * 20;
		}
		if (isPressSpace == true) {
			IncDegProcess(players, prekeys, keys);
			if (prekeys == 0 && keys != 0 && isScroll == false && ((players.isTitleClear == true && players.pos.Length() <= map.radius) || (players.isTitleClear == false && (players.pos.Length() <= 3000)))) {
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
			player->CircleProcess(players);
		}
		if (isPressSpace == false && prekeys == 0 && keys != 0) {
			circleB.pos.x = circleA.pos.x;
		}
	}
	if (Gcear.isGameClear == true) {
		player->radius = 25;
		players.radius = player->radius;
		player->Length = radius * 12;
		Gceasingt += (0.01f * kFrameMag);
		Gceasingt = Clamp(Gceasingt, 0.0f, 1.0f);
		circleA.pos = { -Lerp(Easing::easeOutCubic(Gceasingt), 150), 150 };
		player->pos = { -Lerp(Easing::easeOutCubic(Gceasingt), 150), 150 };
		circleB.pos = {  Lerp(Easing::easeOutCubic(Gceasingt), 149), 150 };
		player->center = { -Lerp(Easing::easeOutCubic(Gceasingt), 150), 150 };
		player->deg = 0;
		screen.Scroll = { 0,0 };
	}
}

/*�@�`��֐��@*/
void Player::Draw(Screen& screen, Player& players) {
	Quad tmp, outtmp, ReverseGaugetmp, op{
		{ 0, -players.radius + 15 / screen.Zoom.x},
		{ static_cast<float>(players.Length), -players.radius + 15 / screen.Zoom.x},
		{ 0,  players.radius - 15 / screen.Zoom.x},
		{ static_cast<float>(players.Length),players.radius - 15 / screen.Zoom.x}
	}, outop{
		{ 0, -players.radius + 12 / screen.Zoom.x},
		{ static_cast<float>(players.Length), -players.radius + 12 / screen.Zoom.x},
		{ 0,  players.radius - 12 / screen.Zoom.x},
		{ static_cast<float>(players.Length), players.radius - 12 / screen.Zoom.x}
	};
	Matrix33 mat, mat2;
	mat = Matrix33::Identity();
	mat *= Matrix33::MakeRotation(Degree(players.deg));
	mat *= Matrix33::MakeTranslation(players.center);
	tmp.LeftTop = op.LeftTop * mat;
	tmp.RightTop = op.RightTop * mat;
	tmp.LeftBottom = op.LeftBottom * mat;
	tmp.RightBottom = op.RightBottom * mat;
	outtmp.LeftTop = outop.LeftTop * mat;
	outtmp.RightTop = outop.RightTop * mat;
	outtmp.LeftBottom = outop.LeftBottom * mat;
	outtmp.RightBottom = outop.RightBottom * mat;

	//�X�y�[�X�L�[���������Ƃ��ɔg����o��
	for (int i = 0; i < RIPPLES_MAX; i++){
		if (isExist[i] == true){
			screen.DrawEllipse(Rpos[i].x, Rpos[i].y, Rradius[i], Rradius[i], 0.0f, Rcolor[i], kFillModeSolid);
		}
	}
	//�A�E�g���C��
	screen.DrawEllipse(circleA.pos.x, circleA.pos.y, players.radius + 3 / screen.Zoom.x, players.radius + 3 / screen.Zoom.x, 0.0f, outcolor, kFillModeSolid);
	screen.DrawEllipse(circleB.pos.x, circleB.pos.y, players.radius + 3 / screen.Zoom.x, players.radius + 3 / screen.Zoom.x, 0.0f, outcolor, kFillModeSolid);
	screen.DrawQuad2(outtmp, 0, 0, 0, 0, 0, outcolor);
	//�{�́i�w�i�Ɠ����F�j
	screen.DrawEllipse(circleA.pos.x, circleA.pos.y, players.radius, players.radius, 0.0f, color, kFillModeSolid);
	screen.DrawEllipse(circleB.pos.x, circleB.pos.y, players.radius, players.radius, 0.0f, color, kFillModeSolid);
	screen.DrawQuad2(tmp, 0, 0, 0, 0, 0, color);
}



void Player::Ripples(Screen& screen, Player& players, char prekeys, char keys, Map& map) {
	for (int i = 0; i < RIPPLES_MAX; i++) {
		if (prekeys == 0 && keys != 0 && isExist[i] == false && isScroll == false) {
			Rpos[i] = players.center;
			Rradius[i] = players.radius;
			Rcolor[i] = 0x000000FF;
			Existtime[i] = 0.0f;
			isExist[i] = true;
			break;
		}
		if (isExist[i] == true) {
			Rradius[i] += 3 / screen.Zoom.x;
			Existtime[i] += (0.01f * kFrameMag);
			Rcolor[i] = 0x00000000 | static_cast<int>((1.0f - Existtime[i]) * 0xFF + Existtime[i] * 0x00);
			if (Rcolor[i] == 0x00000000) {
				isExist[i] = false;
			}
		}
	}
}
