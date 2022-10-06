#pragma once
#include "Vec2.h"
#include "Screen.h"

class Figure
{
public:

	//Т▓Ро/////////////////////////////////////////
	static const int FigureMax = 2000;
	static const int Area = 5000;
	static const int RadianMin = 5;
	static const int RadianMax = 50;
	///////////////////////////////////////////////

	virtual void draw(){};
	virtual void set() {};
	bool cheakdraw(Screen screen, Vec2 Position, int width, int height, bool Flag);

	Vec2 position;
	float radian;
	unsigned int color;
	bool flag;
private:
	
};

class llipse:public Figure
{
public:
	llipse();
	void draw(Screen& screen);
	void set(int x,int y,int Radian);
	/*bool cheakdraw(Screen screen, Vec2 Position, int width, int height, bool Flag);*/
private:

};

class Triangle:public Figure
{
public:
	Triangle();
	void draw(Screen& screen);
	void set(int x, int y, int Radian);
	/*bool cheakdraw(Screen screen, Vec2 Position, int width, int height, bool Flag);*/

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
	/*bool cheakdraw(Screen screen, Vec2 Position, int width, int height, bool Flag);*/

	Vec2 top_left_position;
	Vec2 top_right_position;
	Vec2 bottom_left_position;
	Vec2 bottom_right_position;
private:

};

