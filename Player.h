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

	/*�@�ϐ��@*/
	Vec2 pos;							//����͂�����position
	Vec2 center;						//��]�̒��S
	Vec2 add;							//��]�����l
	Vec2 tmppos;						//�~�^������~��ύX�����ۂ̓x���̌v�Z�Ɏg��
	float deg;							//�x��
	float radius;						//���a

	//tuika//muteki
	int Muteki_Timer;					//���G�̎���
	bool isMutekiDisplay;				//��e���ɐF���ς��^�C�~���O�t���O
	bool Muteki;						//���G���ǂ���
	unsigned int color;					//��e���ɐF���ς��
	unsigned int outcolor;				//��e���ɐF���ς��i�A�E�g���C���j

	int Reverse;						//���]�p

	int Length;							//�~�Ɖ~�̊Ԃ̒���

	float incDeg = 0.0f;				//���ʉ�]���x
	const float initVelo = 4.5f;		//�����x

	bool isScroll;						//�X�N���[���t���O
	Vec2 tmpCenpos;						//�X�N���[���������W
	Vec2 tmpMovepos;					//�X�N���[���ڕW���W
	float Scrolleasingt;				//����͂����̂�
	float ScrollincT;					//easingt�̑�����

	Vec2 Rpos[RIPPLES_MAX];				//�g��pos
	bool isExist[RIPPLES_MAX];			//�g��t���O
	float Rradius[RIPPLES_MAX];			//�g��radius
	float Existtime[RIPPLES_MAX];		//�g�䑶��time
	unsigned int Rcolor[RIPPLES_MAX];	//�g��color

	bool isPressSpace;
	bool isTitleClear;

	float Gceasingt;

	/*�@�֐��@*/
	void Init();																														//����������֐�
	void SetPlayers(Player& players);																									//main.cpp�ō��W���g�p���邽�߂Ɏ擾����֐�
	virtual void CircleProcess(Player& players) {};																						//�~�^���̊֐�
	virtual void SetDegree() {};																										//�~�^������~��ύX����ۂ̓x���̐ݒ肷��֐�
	void IncDegProcess(Player& players, char prekeys, char keys);																		//incDeg�̑��x��ω������鏈���֐�
	void SetScrollPos(Screen& screen, Player& players, char prekeys, char keys, Map& map);														//�X�N���[�����W��ݒ肷��֐�
	void SetZoom(Screen& screen, Player& players, Title& title);																		//�Y�[���̒l��ݒ肷��֐�
	void SizeIncrease(Player& players);																									//�G�ɓ����������Ɏg�p����֐��i���a�������Ȃ�j
	void SizeDecrease(Player& players, int wave);																									//�G�ɓ����������Ɏg�p����֐��i���a���Z���Ȃ�j
	void MutekiTime();																													//���G���ԗp�֐�
	void Process(Player& players, char prekeys, char keys, Title& title, GameClear& Gcear, Screen& screen, Map& map);					//�֐����܂Ƃ߂�main.cpp�ň�s�ɂ���֐�
	void Draw(Screen& screen, Player& players);																							//�`��֐�
	void Ripples(Screen& screen, Player& players, char prekeys, char keys, Map& map);																//�g��̊֐�

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
