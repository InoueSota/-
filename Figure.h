#pragma once
#include "Function.h"
#include <Novice.h>
#include "Screen.h"
#include "Player.h"
#include "Map.h"
#include "easing.h"
#include "Quad.h"
#include "Wave.h"


class Figure
{
public:
	Figure();
	//調整/////////////////////////////////////////
	static const int FigureMax = 25;
	float Area(Player& player ,Screen screen,Map map);
	float RadianMin(Player& player);
	float RadianMax(Player& player);
	///////////////////////////////////////////////

	virtual void draw(){};
	virtual void set() {};
	virtual void respon() {};
	virtual void Update() {};
	virtual bool IsInStage() { return 0; };
	bool cheakdraw(Player player, Vec2 Position,Screen screen, bool Flag);
	//画面内かチェック
	bool InScreen(Player player, Vec2 Position, Screen screen);
	float IsRespon(Map map);
	void reset();

	Vec2 position;
	float radian;
	unsigned int color;
	bool flag;
	int cooltime;
	float colortime;
	bool responflag;

	//消
	float stage(Map map);
private:
	
};

class llipse:public Figure
{
public:
	llipse();
	void draw(Screen& screen, Player& players);
	void set(Player& player,Screen screen,Map map,WAVE wave);
	void respon(Player player, Screen screen,Map map, WAVE wave);
	
	bool IsInStage(float stage);
	void Update(Player player,  Screen screen, Map map, WAVE wave);
	bool Player_Ellipse(Player player);
	int count;
	bool easingflag = false;
	bool easingset = false;
	Vec2 start;
	Vec2 end;
	float t;
	int count_state;
	int count_end;
private:

};



class Seed :public Figure
{
public:
	Seed();
	void draw(Screen& screen);
	void set(Player& player, Screen screen, Map map, Vec2 pos, int seed);
	void Update(Player player, Screen screen, Map map);
	void respon(Player player, Screen screen, Vec2 pos, Map map);
	bool Player_Seed(Player player, Vec2 position);

	bool UpdateFlag = false;
	static const int SeedMax = 3;
	int seedcount;
	Vec2 position[SeedMax];
	Vec2 vec[SeedMax];
	float t;
	bool setFlag = false;
private:

};

class Triangle:public Figure
{
public:
	Triangle();
	void draw(Screen& screen);
	void set(Player& player,Screen screen,Map map, WAVE wave);
	void respon(Player player, Screen screen, Map map, WAVE wave);
	bool IsInStage(float stage);
	void Update(Player player, Screen screen, Map map, Seed seed);
	bool Player_Triangle(Player player);
	
	Vec2 top_position;
	Vec2 right_position;
	Vec2 left_position;
	float theta;
	float theta_left;
	float theta_right;

	bool triangle_death;
	int seedcount;
private:

};



class Quadrangle:public Figure
{
public:
	Quadrangle();
	void draw(Screen& screen);
	void breaddraw(Screen& screen);
	void Update(Player& player, Screen screen, Map map, WAVE wave);
	void set(Player& player, Screen screen,Map map);
	void respon(Player player, Screen screen, Map map);
	bool IsInStage(float stage);
	bool Player_Quadrangle(Player player);
	bool Player_Update(Player player);

	bool UpdatesetFlag;
	bool BreadOpenFlag;
	bool BreadCloseFlag;
	bool drawflag;
	float theta_plus;
	float t;
	int cooltime;
	Vec2 vel;
	Vec2 End_position;
	Vec2 top_left_position;
	Vec2 top_right_position;
	Vec2 bottom_left_position;
	Vec2 bottom_right_position;

	//
	Vec2 bread_1_top_left_position;
	Vec2 bread_1_top_right_position;
	Vec2 bread_1_bottom_left_position;
	Vec2 bread_1_bottom_right_position;

	Vec2 bread_1_top_left_position_state;
	Vec2 bread_1_top_right_position_state;
	Vec2 bread_1_bottom_left_position_state;
	Vec2 bread_1_bottom_right_position_state;

	Vec2 bread_1_top_left_position_end;
	Vec2 bread_1_top_right_position_end;
	Vec2 bread_1_bottom_left_position_end;
	Vec2 bread_1_bottom_right_position_end;
	//
	Vec2 bread_2_top_left_position;
	Vec2 bread_2_top_right_position;
	Vec2 bread_2_bottom_left_position;
	Vec2 bread_2_bottom_right_position;
	//ブレード2

	Vec2 bread_2_top_left_position_state;
	Vec2 bread_2_top_right_position_state;
	Vec2 bread_2_bottom_left_position_state;
	Vec2 bread_2_bottom_right_position_state;

	Vec2 bread_2_top_left_position_end;
	Vec2 bread_2_top_right_position_end;
	Vec2 bread_2_bottom_left_position_end;
	Vec2 bread_2_bottom_right_position_end;

	
	
	float theta;
	float checkroll(float Theta);
	float top_right = 0.0f;
	float bottom_left = 0.0f;
	float bottom_right = 0.0f;
};

