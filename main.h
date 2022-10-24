#pragma once
#include <Novice.h>
#include <time.h>
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


int radius;


//インスタンス化
Screen screen;
Map stage_1;
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
Seed seed[Figure::FigureMax];
WAVE wave;
//Enemy enemy[3];