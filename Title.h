#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "Screen.h"

class Title
{
public:

	Title() {
		Init();
	}

	const int kTitleWidth = 1410;
	const int kTitleHeight = 286;
	const int kSpaceWidth = 1170;
	const int kSpaceHeight = 168;

	Vec2 Titlepos;
	Vec2 Spacepos;
	float theta;

	bool isLoadTexture;
	int title;
	int space;

	void Init();
	void Process(char prekeys, char keys);
	void Draw(Screen& screen, Title& title);

};
