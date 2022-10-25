#include "Particle.h"

void PlayerP::ParticleInit() {
    for (int i = 0; i < PARTICLE_MAX; i++) {
        life[i] = 0;
    }
}

void PlayerP::ParticleMake(Player& players, Screen& screen) {
    for (int i = 0; i < PARTICLE_MAX; i++) {
        if (life[i] <= 0 && frame % 3 == 0) {
            pos[i] = players.pos;
            radius[i] = players.radius;
            life[i] = PARTICLE_LIFE;
            decreaseSize[i] = players.radius / 10;
            alphat[i] = 0.0f;
            color[i] = 0xE5C210FF;
            break;
        }
    }
}

void PlayerP::ParticleMove() {
    for (int i = 0; i < PARTICLE_MAX; i++) {
        if (life[i] > 0) {
            life[i]--;
            alphat[i] += 0.01f;
            color[i] = 0xE5C21000 | static_cast<int>((1.0f - alphat[i]) * 0xFF + alphat[i] * 0x00);
            if (life[i] % 5 == 0) {
                radius[i] -= decreaseSize[i];
            }
            if (radius[i] < 0 || color[i] <= 0xE5C21000) {
                life[i] = 0;
            }
        }
    }
}

void PlayerP::ParticleProcess(Player& players, Screen& screen) {
    frame++;
    ParticleMake(players, screen);
    ParticleMove();
}

void PlayerP::DrawParticle(Screen& screen) {
    for (int i = 0; i < PARTICLE_MAX; i++) {
        if (life[i] > 0) {
            screen.DrawEllipse(pos[i].x, pos[i].y, radius[i], radius[i], 0.0f, color[i], kFillModeSolid);
        }
    }
}