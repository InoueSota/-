#include "Particle.h"

void TitleP::ParticleInit() {
    for (int i = 0; i < PARTICLE_MAX; i++) {
        life[i] = 0;
    }
    spd = 5;
}
void TitleP::ParticleMake(Player& players, Screen& screen) {
    for (int i = 0; i < PARTICLE_MAX; i++) {
        if (life[i] <= 0 && frame % 3 == 0) {
            pos[i].x = RAND(screen.Scroll.x - SCREEN_HEIGHT / 2, screen.Scroll.x + SCREEN_HEIGHT / 2);
            pos[i].y = screen.Scroll.y - SCREEN_HEIGHT / 2;
            life[i] = PARTICLE_LIFE;
            color[i] = 0xE5C210FF;
            break;
        }
    }
}
void TitleP::ParticleMove() {
    for (int i = 0; i < PARTICLE_MAX; i++) {
        if (life[i] > 0) {
            life[i]--;
            pos[i].y -= spd;
            if (life[i] <= 0) {
                life[i] = 0;
            }
        }
    }
}
void TitleP::ParticleProcess(Player& players, Screen& screen) {
    frame++;
    ParticleMake(players, screen);
    ParticleMove();
}
void TitleP::DrawParticle(Screen& screen) {
    for (int i = 0; i < PARTICLE_MAX; i++) {
        if (life[i] > 0) {
            poss[i] = {
                {pos[i].x - kLineWidth / 2, pos[i].y + kLineHeight / 2},
                {pos[i].x + kLineWidth / 2, pos[i].y + kLineHeight / 2},
                {pos[i].x - kLineWidth / 2, pos[i].y - kLineHeight / 2},
                {pos[i].x + kLineWidth / 2, pos[i].y - kLineHeight / 2}
            };
            screen.DrawQuad2(poss[i], 0, 0, 0, 0, 0, color[i]);
        }
    }
}



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



void GclearP::ParticleInit() {
    for (int i = 0; i < PARTICLE_MAX; i++) {
        life[i] = 0;
    }
}
void GclearP::ParticleMake() {
    for (int i = 0; i < PARTICLE_MAX; i++) {
        if (life[i] <= 0 && frame % 3 == 0) {
            pos[i] = { (float)RAND(0, SCREEN_WIDTH), (float)RAND(0, SCREEN_WIDTH) };
            radius[i] = RAND(20, 80);
            life[i] = PARTICLE_LIFE;
            decreaseSize[i] = radius[i] / 10;
            alphat[i] = 0.0f;
            color[i] = 0xE5C210FF;
            break;
        }
    }
}
void GclearP::ParticleMove() {
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
void GclearP::ParticleProcess() {
    frame++;
    ParticleMake();
    ParticleMove();
}
void GclearP::DrawParticle() {
    for (int i = 0; i < PARTICLE_MAX; i++) {
        if (life[i] > 0) {
            Novice::DrawEllipse(pos[i].x, pos[i].y, radius[i], radius[i], 0.0f, color[i], kFillModeSolid);
        }
    }
}