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
	radius = 8 / screen.Zoom.x;
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
	spd = 8.0f;
	SlashMax = 1;
		shotframe = 0;
		isOccur = false;
	isPressSpace = false;
	isLoadTexture = false;
}
void Slash::Make(Player& players, Screen& screen) {
	Matrix33 mat;
	mat = Matrix33::Identity();
	mat *= Matrix33::MakeScaling(kSlashSizeMax / screen.Zoom.x, kSlashSizeMax / screen.Zoom.y);
	mat *= Matrix33::MakeRotation(Degree(players.deg));
	mat *= Matrix33::MakeTranslation(players.pos);
	direvelo = players.pos - players.center;
	velo = direvelo.Normalized() * (spd / screen.Zoom.x);
	pos.LeftTop = op.LeftTop * mat;
	pos.RightTop = op.RightTop * mat;
	pos.LeftBottom = op.LeftBottom * mat;
	pos.RightBottom = op.RightBottom * mat;
	shotframe = 0;
	isOccur = true;
}
void Slash::Move() {
	if (isOccur == true) {
		shotframe++;
		pos.LeftTop += velo;
		pos.RightTop += velo;
		pos.LeftBottom += velo;
		pos.RightBottom += velo;
		if (shotframe >= kSlashTimeMax) {
			isOccur = false;
	}
	}
}
void Slash::Process(Player& players, Screen& screen, char prekeys, char keys) {
	if (isLoadTexture == false){
		slashImage = Novice::LoadTexture("./resource/Slash.png");
		isLoadTexture = true;
	}
	if ((prekeys != 0 && keys == 0) && isOccur == false){
		spd = Clamp(spd, 2.0f, 10.0f);
		Make(players, screen);
	}
	else if (isOccur == true){
		Move();
	}
	Vec2 tmptoppos = { pos.RightBottom - pos.RightTop};
	Toppos = tmptoppos.Normalized() * (125 / screen.Zoom.y);
}
void Slash::Draw(Screen& screen) {
		if (isOccur == true) {
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
	lineop = {
		{ -0.01f,0 },
		{  0.01f,0 },
		{ -0.01f,3 },
		{  0.01f,3 }
	};
	frame = 0;
	shotframe = 0;
	Lefttop1 = 0;
	Lefttop2 = 0;
	isOccur = false;
	isLoadTexture = false;
	for (int i = 0; i < kLineMax; i++) {
		life[i] = 0;
	}
}
void Beam::Make(Player& players, Screen& screen) {
	Matrix33 mat1, mat2;
	mat1 = Matrix33::Identity();
	mat1 *= Matrix33::MakeScaling(kBeamSizeMax / screen.Zoom.x, kBeamSizeMax / screen.Zoom.y);
	mat1 *= Matrix33::MakeRotation(Degree(90));
	mat1 *= Matrix33::MakeTranslation(players.center);
	mat2 = Matrix33::Identity();
	mat2 *= Matrix33::MakeScaling(kBeamSizeMax / screen.Zoom.x, kBeamSizeMax / screen.Zoom.y);
	mat2 *= Matrix33::MakeRotation(Degree(270));
	mat2 *= Matrix33::MakeTranslation(players.center);
	pos1.LeftTop = op.LeftTop * mat1;
	pos1.RightTop = op.RightTop * mat1;
	pos1.LeftBottom = op.LeftBottom * mat1;
	pos1.RightBottom = op.RightBottom * mat1;
	pos2.LeftTop = op.LeftTop * mat2;
	pos2.RightTop = op.RightTop * mat2;
	pos2.LeftBottom = op.LeftBottom * mat2;
	pos2.RightBottom = op.RightBottom * mat2;
	Leftpos = { players.center.x - ((SCREEN_WIDTH / 2) / screen.Zoom.x), players.center.y };
	Rightpos = { players.center.x + ((SCREEN_WIDTH / 2) / screen.Zoom.x), players.center.y };
	spd = 30 / screen.Zoom.x;
	tmpdeg = players.deg;
	tmpcenter = players.center;
	direvelo1 = { pos1.LeftBottom - pos1.LeftTop };
	direvelo2 = { pos2.LeftBottom - pos2.LeftTop };
	velo1 = direvelo1.Normalized() * spd;
	velo2 = direvelo2.Normalized() * spd;
	for (int i = 0; i < kLineMax; i++) {
		life[i] = 0;
	}
}
void Beam::Move(Player& players, Screen& screen) {
	shotframe++;
	if (shotframe >= kBeamTimeMax) {
		isOccur = false;
	}
}
void Beam::MoveLine(Player& players, Screen& screen) {
	lineframe++;
	linemat1 = Matrix33::Identity();
	linemat1 *= Matrix33::MakeScaling(kBeamSizeMax / screen.Zoom.x, kBeamSizeMax / screen.Zoom.y);
	linemat1 *= Matrix33::MakeRotation(Degree(90));
	linemat1 *= Matrix33::MakeTranslation(tmpcenter.x + RAND(-80 / screen.Zoom.x, 80 / screen.Zoom.x), tmpcenter.y + RAND(-100 / screen.Zoom.y, 100 / screen.Zoom.y));
	linemat2 = Matrix33::Identity();
	linemat2 *= Matrix33::MakeScaling(kBeamSizeMax / screen.Zoom.x, kBeamSizeMax / screen.Zoom.y);
	linemat2 *= Matrix33::MakeRotation(Degree(270));
	linemat2 *= Matrix33::MakeTranslation(tmpcenter.x + RAND(-80 / screen.Zoom.x, 80 / screen.Zoom.x), tmpcenter.y + RAND(-100 / screen.Zoom.y, 100 / screen.Zoom.y));
	for (int i = 0; i < kLineMax; i++) {
		if (life[i] <= 0 && lineframe % 10 == 0) {
			linepos1[i].LeftTop = lineop.LeftTop * linemat1;
			linepos1[i].RightTop = lineop.RightTop * linemat1;
			linepos1[i].LeftBottom = lineop.LeftBottom * linemat1;
			linepos1[i].RightBottom = lineop.RightBottom * linemat1;
			linepos2[i].LeftTop = lineop.LeftTop * linemat2;
			linepos2[i].RightTop = lineop.RightTop * linemat2;
			linepos2[i].LeftBottom = lineop.LeftBottom * linemat2;
			linepos2[i].RightBottom = lineop.RightBottom * linemat2;
			life[i] = kLineLife;
			break;
		}
	}
	for (int i = 0; i < kLineMax; i++) {
		if (life[i] > 0) {
			life[i]--;
			linepos1[i].LeftTop += velo1;
			linepos1[i].RightTop += velo1;
			linepos1[i].LeftBottom += velo1;
			linepos1[i].RightBottom += velo1;
			linepos2[i].LeftTop += velo2;
			linepos2[i].RightTop += velo2;
			linepos2[i].LeftBottom += velo2;
			linepos2[i].RightBottom += velo2;
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
		Lefttop1 = 0;
		Lefttop2 = 0;
		lineframe = 0;
		Make(players, screen);
		isOccur = true;
	}
	if (isOccur == true){
		Move(players, screen);
		MoveLine(players, screen);
	}
}
void Beam::Draw(Screen& screen) {
	if (isOccur == true) {
		screen.DrawQuad2Renban(pos1, Lefttop1, 0, 420, 2940, 10, kBeamTimeMax / 10, shotframe, beamImage, 0xFFFFFFAA);
		screen.DrawQuad2Renban(pos2, Lefttop2, 0, 420, 2940, 10, kBeamTimeMax / 10, shotframe, beamImage, 0xFFFFFFAA);
		for (int i = 0; i < kLineMax; i++){
			if (life[i] > 0) {
				screen.DrawQuad2(linepos1[i], 0, 0, 0, 0, 0, 0xF44336FF);
				screen.DrawQuad2(linepos2[i], 0, 0, 0, 0, 0, 0xF44336FF);
			}
		}
	}
}