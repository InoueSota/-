#pragma once
#include <Novice.h>
#include <time.h>
#include "Player.h"
#include "Figure.h"
#include "drain.h"
#include "Screen.h"
#include "Map.h"
#include "Item.h"
#include "Boss.h"





//インスタンス化
Screen screen;
Map stage_1;
Player players;
llipse ellipse[Figure::FigureMax];
Triangle triangle[Figure::FigureMax];
Quadrangle quadrangle[Figure::FigureMax];
clock_t oldTime;
Item item;
Seed seed[Figure::FigureMax];
//Boss boss;
//Enemy enemy[3];