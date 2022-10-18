#pragma once
#include <Novice.h>
#include "Vec2.h"
#include "Screen.h"
#include "easing.h"
#include "Matrix33.h"

const int RIPPLES_MAX = 20;

class Player
{
public:

	Player();
	~Player();

	/*�@�ϐ��@*/
	Vec2 pos;							//����͂�����position
	Vec2 center;						//��]�̒��S
	Vec2 add;							//��]�����l
	Vec2 tmppos;						//�~�^������~��ύX�����ۂ̓x���̌v�Z�Ɏg��
	float deg;							//�x��
	float radius;						//���a

	int Reverse;						//���]�p
	int Longpressframe;					//�������t���[��
	bool isLongpress;					//������������

	int Length;							//�~�Ɖ~�̊Ԃ̒���
	float incDeg;						//��]���x

	Vec2 Rpos[RIPPLES_MAX];				//�g��pos
	bool isExist[RIPPLES_MAX];			//�g��t���O
	float Rradius[RIPPLES_MAX];			//�g��radius
	float Existtime[RIPPLES_MAX];		//�g�䑶��time
	unsigned int Rcolor[RIPPLES_MAX];	//�g��color

	bool isHit;

	bool isScroll;						//�X�N���[���t���O
	Vec2 tmpCenpos;						//�X�N���[���������W
	Vec2 tmpMovepos;					//�X�N���[���ڕW���W
	float Scrolleasingt;				//����͂����̂�
	float ScrollincT;					//easingt�̑�����

	/*�@�֐��@*/
	void Init();																		//����������֐�
	void SetPlayers(Player& players);													//main.cpp�ō��W���g�p���邽�߂Ɏ擾����֐�
	virtual void CircleProcess(Player& players) {};										//�~�^���̊֐�
	virtual void SetDegree() {};														//�~�^������~��ύX����ۂ̓x���̐ݒ肷��֐�
	void SetScrollPos(Screen& screen, Player& players, char prekeys, char keys);		//�X�N���[�����W��ݒ肷��֐�
	void SetZoom(Screen& screen, Player& players);										//�Y�[���̒l��ݒ肷��֐�
	void Process(Player& players, char prekeys, char keys, char predik_d, char dik_d);	//�֐����܂Ƃ߂�main.cpp�ň�s�ɂ���֐�
	void Draw(Screen& screen, Player& players);											//�`��֐�
	void Ripples(Screen& screen, Player& players, char prekeys, char keys);				//�g��̊֐�

	void Draw_Rand_Skin(Screen& screen, char prekeys, char keys);
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
