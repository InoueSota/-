#pragma once
#include <Novice.h>
#include "Vec2.h"
#include "Screen.h"
#include "easing.h"

class Player
{
public:

	Player();
	~Player();

	/*�@�ϐ��@*/
	Vec2 pos;			//����͂�����position
	Vec2 center;		//��]�̒��S
	Vec2 add;			//��]�����l
	Vec2 tmppos;		//�~�^������~��ύX�����ۂ̓x���̌v�Z�Ɏg��
	float deg;			//�x��
	float radius;		//���a

	int Reverse;		//���]�p
	int incDeg;			//��]���x
	int Length;			//�~�Ɖ~�̊Ԃ̒���

	bool isHit;


	bool isScroll;		//�X�N���[���t���O
	Vec2 tmpCenpos;		//�X�N���[���������W
	Vec2 tmpMovepos;	//�X�N���[���ڕW���W
	float easingt;		//����͂����̂�
	float incT;			//easingt�̑�����

	/*�@�֐��@*/
	void Init();																		//����������֐�
	void SetPlayers(Player& players);													//main.cpp�ō��W�����悤���邽�߂Ɏ擾����֐�
	virtual void CircleProcess(Player& players) {};										//�~�^���̊֐�
	virtual void SetDegree() {};														//�~�^������~��ύX����ۂ̓x���̐ݒ肷��֐�
	void SetScrollPos(Screen& screen, Player& players, char prekeys, char keys);		//�X�N���[�����W��ݒ肷��֐�
	void Process(Player& players, char prekeys, char keys, char predik_d, char dik_d);	//�֐����܂Ƃ߂�֐�
	void Draw(Screen& screen, Player& players);											//�`��֐�
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