#pragma once
#include "Title.h"
#include "GameClear.h"
#include "easing.h"
#include "Matrix33.h"
#include "Map.h"
//#include "Wave.h"

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

	//tuika//muteki
	int Muteki_Timer;					//無敵の時間
	bool isMutekiDisplay;				//被弾時に色が変わるタイミングフラグ
	bool Muteki;						//無敵かどうか
	unsigned int color;					//被弾時に色が変わる
	unsigned int outcolor;				//被弾時に色が変わる（アウトライン）

	int Reverse;						//反転用

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

	bool isPressSpace;
	bool isTitleClear;

	float Gceasingt;

	/*　関数　*/
	void Init();																														//初期化する関数
	void SetPlayers(Player& players);																									//main.cppで座標を使用するために取得する関数
	virtual void CircleProcess(Player& players) {};																						//円運動の関数
	virtual void SetDegree() {};																										//円運動する円を変更する際の度数の設定する関数
	void IncDegProcess(Player& players, char prekeys, char keys);																		//incDegの速度を変化させる処理関数
	void SetScrollPos(Screen& screen, Player& players, char prekeys, char keys, Map& map);														//スクロール座標を設定する関数
	void SetZoom(Screen& screen, Player& players, Title& title);																		//ズームの値を設定する関数
	void SizeIncrease(Player& players);																									//敵に当たった時に使用する関数（半径が長くなる）
	void SizeDecrease(Player& players, int wave);																									//敵に当たった時に使用する関数（半径が短くなる）
	void MutekiTime();																													//無敵時間用関数
	void Process(Player& players, char prekeys, char keys, Title& title, GameClear& Gcear, Screen& screen, Map& map);					//関数をまとめてmain.cppで一行にする関数
	void Draw(Screen& screen, Player& players);																							//描画関数
	void Ripples(Screen& screen, Player& players, char prekeys, char keys, Map& map);																//波紋の関数

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
