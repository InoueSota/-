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

private:
	virtual void ParticleInit(){};							//　初期化
	virtual void ParticleMake() {};							//　生成
	virtual void ParticleMove() {};							//　移動
	virtual void ParticleProcess() {};						//　処理
	virtual void DrawParticle() {};							//　描画
};

class PlayerP : public Particle {
public:
	void ParticleInit() {};
	void ParticleMake(Player& players) {};
	void ParticleMove() {};
	void ParticleProcess() {};
	void DrawParticle() {};
};