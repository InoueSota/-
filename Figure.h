#pragma once
#include "Vec2.h"
#include "Screen.h"

class Figure
{
public:
	virtual void draw(){};
	virtual void set() {};


	static const int FigureMax = 50;

	Vec2 position;
	float radian;
	unsigned int color;
private:
	
};

class llipse:public Figure
{
public:
	llipse();
	void draw(Screen& screen);
	void set(int x,int y,int Radian);
private:

};

class Triangle:public Figure
{
public:
	Triangle();
	void draw(Screen& screen);
	void set(int x, int y, int Radian);

	Vec2 top_position;
	Vec2 right_position;
	Vec2 left_position;
private:

};

class Quadrangle:public Figure
{
public:
	Quadrangle();
	void draw(Screen& screen);
	void set(int x, int y,int Radian);

	Vec2 top_left_position;
	Vec2 top_right_position;
	Vec2 bottom_left_position;
	Vec2 bottom_right_position;
private:

};

