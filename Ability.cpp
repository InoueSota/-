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
		if (Longpressframe % kBubbleInterval == 0 && isOccur[i] == false){
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
