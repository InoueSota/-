#pragma once
#include "Title.h"
#include "easing.h"
#include "Matrix33.h"

const int RIPPLES_MAX = 20;

class Player
{
public:

	Player() {
		Init();
		SRAND();
	};

	/*　変数　*/
	Vec2 pos;							//これはただのposition
	Vec2 center;						//回転の中心
	Vec2 add;							//回転した値
	Vec2 tmppos;						//円運動する円を変更した際の度数の計算に使う
	float deg;							//度数
	float radius;						//半径

	int Reverse;						//反転用
	int Longpressframe;					//長押しフレーム
	bool isLongpress;					//長押ししたか

	int Length;							//円と円の間の長さ

	float incDeg = 0.0f;				//結果回転速度
	const float initVelo = 4.5f;		//初速度

	bool isScroll;						//スクロールフラグ
	Vec2 tmpCenpos;						//スクロール初期座標
	Vec2 tmpMovepos;					//スクロール目標座標
	float Scrolleasingt;				//これはただのｔ
	float ScrollincT;					//easingtの増加量

	Vec2 Rpos[RIPPLES_MAX];				//波紋pos
	bool isExist[RIPPLES_MAX];			//波紋フラグ
	float Rradius[RIPPLES_MAX];			//波紋radius
	float Existtime[RIPPLES_MAX];		//波紋存在time
	unsigned int Rcolor[RIPPLES_MAX];	//波紋color

	float theta;
	bool isPressSpace;
	bool isTitleClear;

	/*　関数　*/
	void Init();																						//初期化する関数
	void SetPlayers(Player& players);																	//main.cppで座標を使用するために取得する関数
	virtual void CircleProcess(Player& players) {};														//円運動の関数
	virtual void SetDegree() {};																		//円運動する円を変更する際の度数の設定する関数
	void IncDegProcess(Player& players, char prekeys, char keys);										//incDegの速度を変化させる処理関数
	void SetScrollPos(Screen& screen, Player& players, char prekeys, char keys);						//スクロール座標を設定する関数
	void SetZoom(Screen& screen, Player& players);														//ズームの値を設定する関数
	void SizeIncrease(Player& players);																	//敵に当たった時に使用する関数（半径が長くなる）
	void SizeDecrease(Player& players);																	//敵に当たった時に使用する関数（半径が短くなる）
	void Process(Player& players, char prekeys, char keys, char predik_d, char dik_d, Title& title);	//関数をまとめてmain.cppで一行にする関数
	void Draw(Screen& screen, Player& players);															//描画関数
	void Ripples(Screen& screen, Player& players, char prekeys, char keys);								//波紋の関数

	//void Draw_Rand_Skin(Screen& screen, char prekeys, char keys);
private:

};

class CircleA : public Player {
public:
	void CircleProcess(Player& players);
	void SetDegree();
};

class CircleB : public Player {
public:
	void CircleProcess(Player& players);
	void SetDegree();
};
