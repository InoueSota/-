#pragma once
#include "Player.h"

/*�@�萔�̐ݒ�@*/
const int PARTICLE_MAX = 500;				//�p�[�e�B�N���̍ő吔
const int PARTICLE_LIFE = 250;				//�p�[�e�B�N���̎���

class Particle
{
public:

	Vec2 pos[PARTICLE_MAX];
	int frame;
	int life[PARTICLE_MAX];
	float radius[PARTICLE_MAX];
	int decreaseSize[PARTICLE_MAX];		//�p�[�e�B�N���̌�����
	float alphat[PARTICLE_MAX];
	unsigned int color[PARTICLE_MAX];

	virtual void ParticleInit() {};							//�@������
	virtual void ParticleMake() {};							//�@����
	virtual void ParticleMove() {};							//�@�ړ�
	virtual void ParticleProcess() {};						//�@����
	virtual void DrawParticle() {};							//�@�`��
};

class PlayerP : public Particle {
public:
	void ParticleInit();
	void ParticleMake(Player& players, Screen& screen);
	void ParticleMove();
	void ParticleProcess(Player& players, Screen& screen);
	void DrawParticle(Screen& screen);
};

class GclearP : public Particle {
public:
	GclearP() {
		ParticleInit();
		SRAND();
	}
	void ParticleInit();
	void ParticleMake();
	void ParticleMove();
	void ParticleProcess();
	void DrawParticle();
};