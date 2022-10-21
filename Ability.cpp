#include "Ability.h"





void Bubble::Init() {
	for (int i = 0; i < kBubbleMax; i++){
		isOccur[i] = false;
		isRelease[i] = true;
		Shotframe[i] = 0;
	}
	Longpressframe = 0;
}
void Bubble::Make(Player& players, Screen& screen) {
	radius = 20 / screen.Zoom.x;
	for (int i = 0; i < kBubbleMax; i++){
		if (Longpressframe >= 20 && Longpressframe % kBubbleInterval == 0 && isOccur[i] == false){
			pos[i].x = players.center.x + cosf(Degree(players.deg)) * (players.Length + kBubbleDistance / screen.Zoom.x);
			pos[i].y = players.center.y + sinf(Degree(players.deg)) * (players.Length + kBubbleDistance / screen.Zoom.y);
			direvelo[i] = pos[i] - players.center;
			velo[i] = direvelo[i].Normalized() * (spd / screen.Zoom.x);
			Shotframe[i] = 0;
			isRelease[i] = false;
			isOccur[i] = true;
			break;
		}
	}
}
void Bubble::Move(char keys) {
	for (int i = 0; i < kBubbleMax; i++){
		if (isOccur[i] == true){
			if (keys == 0){
				isRelease[i] = true;
			}
			if (isRelease[i] == true){
				Shotframe[i]++;
				pos[i] += velo[i];
				if (Shotframe[i] >= kBubbleTimeMax) {
					isOccur[i] = false;
				}
			}
		}
	}
}
void Bubble::Process(Player& players, Screen& screen, char keys) {
	if (keys != 0){
		Longpressframe++;
		Make(players, screen);
	}
	Move(keys);
	if (keys == 0){
		Longpressframe = 0;
	}
}
void Bubble::Draw(Screen& screen) {
	for (int i = 0; i < kBubbleMax; i++) {
		if (isOccur[i] == true) {
			screen.DrawEllipse(pos[i].x, pos[i].y, radius, radius, 0.0f, color, kFillModeSolid);
		}
	}
}





void Slash::Init() {
	op = {
		{-1,-2.5},
		{ 1,-2.5},
		{-1, 2.5},
		{ 1, 2.5}
	};
	spd = 3.0f;
	delayframe = 0;
	shotframe = 0;
	isOccur = false;
	isLoadTexture = false;
}
void Slash::Make(Player& players, Screen& screen) {
	if (isTrigger == true){
		delayframe++;
	}
	if (delayframe >= 10 && isOccur == false){
		Matrix33 mat;
		mat = Matrix33::Identity();
		mat *= Matrix33::MakeScaling(kSlashSizeMax / screen.Zoom.x, kSlashSizeMax / screen.Zoom.y);
		mat *= Matrix33::MakeRotation(Degree(players.deg));
		mat *= Matrix33::MakeTranslation(players.pos);
		pos.LeftTop = op.LeftTop * mat;
		pos.RightTop = op.RightTop * mat;
		pos.LeftBottom = op.LeftBottom * mat;
		pos.RightBottom = op.RightBottom * mat;
		direvelo = players.pos - players.center;
		velo = direvelo.Normalized() * (spd / screen.Zoom.x);
		shotframe = 0;
		isOccur = true;
	}
}
void Slash::Move() {
	if (isOccur == true){
		shotframe++;
		pos.LeftTop += velo;
		pos.RightTop += velo;
		pos.LeftBottom += velo;
		pos.RightBottom += velo;
		if (shotframe >= kSlashTimeMax){
			delayframe = 0;
			isTrigger = false;
			isOccur = false;
		}
	}
}
void Slash::Process(Player& players, Screen& screen, char prekeys, char keys) {
	if (isLoadTexture == false){
		slashImage = Novice::LoadTexture("./resource/Slash.png");
		isLoadTexture = true;
	}
	if ((prekeys != 0 && keys == 0) && isTrigger == false) {
		isTrigger = true;
	}

	Make(players, screen);
	Move();
}
void Slash::Draw(Screen& screen) {
	if (isOccur == true){
		screen.DrawQuad2(pos, 0, 0, 480, 2260, slashImage, WHITE);
	}
}





void Beam::Init() {
	op = {
		{ -0.5,0 },
		{  0.5,0 },
		{ -0.5,10 },
		{  0.5,10 }
	};
	frame = 0;
	shotframe = 0;
	isOccur = false;
	isLoadTexture = false;
}
void Beam::Make(Player& players, Screen& screen) {
	if (isOccur == false) {
		Matrix33 mat1, mat2;
		mat1 = Matrix33::Identity();
		mat1 *= Matrix33::MakeScaling(kBeamSizeMax / screen.Zoom.x, kBeamSizeMax / screen.Zoom.y);
		mat1 *= Matrix33::MakeRotation(Degree(players.deg + 180));
		mat1 *= Matrix33::MakeTranslation(players.center);
		mat2 = Matrix33::Identity();
		mat2 *= Matrix33::MakeScaling(kBeamSizeMax / screen.Zoom.x, kBeamSizeMax / screen.Zoom.y);
		mat2 *= Matrix33::MakeRotation(Degree(players.deg));
		mat2 *= Matrix33::MakeTranslation(players.center);
		pos1.LeftTop = op.LeftTop * mat1;
		pos1.RightTop = op.RightTop * mat1;
		pos1.LeftBottom = op.LeftBottom * mat1;
		pos1.RightBottom = op.RightBottom * mat1;
		pos2.LeftTop = op.LeftTop * mat2;
		pos2.RightTop = op.RightTop * mat2;
		pos2.LeftBottom = op.LeftBottom * mat2;
		pos2.RightBottom = op.RightBottom * mat2;
	}
}
void Beam::Move(Player& players, Screen& screen) {
	if (isOccur == true) {
		shotframe++;
		if (shotframe >= kBeamTimeMax) {
			isOccur = false;
		}
	}
}
void Beam::Process(Player& players, Screen& screen) {
	if (isLoadTexture == false) {
		beamImage = Novice::LoadTexture("./resource/Beam.png");
		isLoadTexture = true;
	}
	frame++;
	if (frame % kBeamInterval == 0){
		shotframe = 0;
		isOccur = true;
	}
	Make(players, screen);
	Move(players, screen);
}
void Beam::Draw(Screen& screen) {
	if (isOccur == true) {
		screen.DrawQuad2(pos1, 0, 0, 420, 2940, beamImage, WHITE);
		screen.DrawQuad2(pos2, 0, 0, 420, 2940, beamImage, WHITE);
	}
}