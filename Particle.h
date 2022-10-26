#pragma once
#include "Player.h"

/*　定数の設定　*/
const int PARTICLE_MAX = 500;				//パーティクルの最大数
const int PARTICLE_LIFE = 250;				//パーティクルの寿命

class Particle
{
public:

	Vec2 pos[PARTICLE_MAX];
	int frame;
	int life[PARTICLE_MAX];
	float radius[PARTICLE_MAX];
	int decreaseSize[PARTICLE_MAX];		//パーティクルの減少量
	float alphat[PARTICLE_MAX];
	unsigned int color[PARTICLE_MAX];

	virtual void ParticleInit() {};							//　初期化
	virtual void ParticleMake() {};							//　生成
	virtual void ParticleMove() {};							//　移動
	virtual void ParticleProcess() {};						//　処理
	virtual void DrawParticle() {};							//　描画
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