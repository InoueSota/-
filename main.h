#pragma once
#include <Novice.h>
#include <time.h>
#include "Screen.h"
#include "Map.h"
#include "Title.h"
#include "Player.h"
#include "Particle.h"
#include "Ability.h"
#include "Figure.h"
#include "drain.h"
#include "Item.h"
#include "Boss.h"

enum Scene
{
	TITLE,
	INGAME
};
Scene scene = TITLE;

//インスタンス化
Screen screen;
Map stage_1;
Title title;
Player players;
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
//Enemy enemy[3];