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

	const int kBackCircleRadius = 5000;
	const int kTitleWidth = 1410;
	const int kTitleHeight = 286;
	const int kSpaceWidth = 1170;
	const int kSpaceHeight = 168;
	const int kArrowWidth = 75;
	const int kArrowHeight = 100;
	const int kLetsWidth = 1000;
	const int kLetsHeight = 120;
	const int kTargetRadius = 20;

	Vec2 BackCirclepos;
	Vec2 Titlepos;
	Vec2 Spacepos;
	float theta;

	Vec2 Arrowpos;
	Vec2 Letspos;
	Vec2 Targetpos;
	Vec2 TargetRipplespos;
	bool isExist;			//îgñ‰ÉtÉâÉO
	float Rradius;			//îgñ‰radius
	float Existtime;		//îgñ‰ë∂ç›time
	unsigned int Rcolor;	//îgñ‰color

	bool isTitleClear;

	bool isLoadTexture;
	int titlebackground;
	int title;
	int space;
	int lets;

	void Init();
	void Process(char prekeys, char keys);
	void Draw(Screen& screen, Title& title);

};
