#pragma once
#include <Novice.h>
#include <time.h>
#include "Title.h"
#include "GameClear.h"
#include "Player.h"
#include "Particle.h"
#include "Ability.h"
#include "Figure.h"
#include "drain.h"
#include "Screen.h"
#include "Map.h"
#include "Item.h"
#include "Boss.h"
#include "Wave.h"
#include "Bar.h"
#include "Sound.h"


enum Scene
{
	TITLE,
	CHANGE,
	INGAME,
	GAMECLEAR
};
Scene scene = TITLE;


//インスタンス化
Screen screen;
Map stage_1,stage_2,stage_3,boss_stage;
Title title;
Change change;
GameClear Gclear;
GclearP gp;
Player players;
CircleA circlea;
CircleB circleb;
PlayerP Pparticle;
Bubble bubble;
Slash slash;
Beam beam;
llipse ellipse[Figure::FigureMax];
Triangle triangle[Figure::FigureMax];
Quadrangle quadrangle[Figure::FigureMax];
clock_t oldTime;
Item item;
Boss boss;
Boss tboss;
Seed seed[Figure::FigureMax];
WAVE wave;
Bar bar;
Sound sound;
//Enemy enemy[3];