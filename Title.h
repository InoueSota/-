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

	static constexpr int kBackCircleRadius = 5000;
	static constexpr int kTitleWidth = 1410;
	static constexpr int kTitleHeight = 286;
	static constexpr int kSpaceWidth = 1170;
	static constexpr int kSpaceHeight = 168;
	static constexpr int kArrowWidth = 75;
	static constexpr int kArrowHeight = 100;
	static constexpr int kLetsWidth = 1000;
	static constexpr int kLetsHeight = 120;
	static constexpr int kTargetRadius = 20;

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

	float alphat;
	unsigned int color;
	bool isDrainClear;
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

class Change
{
public:

	Change() {
		Init();
	}

	int frame;
	float alphat;
	unsigned int color;
	bool isChangeClear;

	void Init();
	void Process();
	void Draw(Screen& screen);

};
