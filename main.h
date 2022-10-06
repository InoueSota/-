#pragma once
#include <Novice.h>
#include <time.h>
#include "Player.h"
#include "Figure.h"
#include "drain.h"
#include "Screen.h"



//インスタンス化
Screen screen;
Player players;
llipse ellipse[Figure::FigureMax];
Triangle triangle[Figure::FigureMax];
Quadrangle quadrangle[Figure::FigureMax];
clock_t oldTime;