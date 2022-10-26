#include "Particle.h"

void TitleP::ParticleInit() {
    for (int i = 0; i < PARTICLE_MAX; i++) {
        radius[i] = 30;
        life[i] = 0;
    }
}
void TitleP::ParticleMake(Player& players, Screen& screen) {
    for (int i = 0; i < PARTICLE_MAX; i++) {
        if (life[i] <= 0 && frame % 6 == 0) {
            pos[i].x = RAND((screen.Scroll.x - SCREEN_WIDTH / screen.Zoom.x / 2), (screen.Scroll.x + SCREEN_WIDTH / screen.Zoom.x / 2));
            pos[i].y = RAND((screen.Scroll.y - SCREEN_HEIGHT / screen.Zoom.y / 2), (screen.Scroll.y + SCREEN_HEIGHT / screen.Zoom.y / 2));
            life[i] = PARTICLE_LIFE;
            radius[i] = RAND(20, 80);
            decreaseSize[i] = radius[i] / 10;
            alphat[i] = 0.0f;
            color[i] = 0xE5C210FF;
            break;
        }
    }
}
void TitleP::ParticleMove() {
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
void TitleP::ParticleProcess(Player& players, Screen& screen) {
    frame++;
    ParticleMake(players, screen);
    ParticleMove();
}
void TitleP::DrawParticle(Screen& screen) {
    for (int i = 0; i < PARTICLE_MAX; i++) {
        if (life[i] > 0) {
            screen.DrawEllipse(pos[i].x, pos[i].y, radius[i], radius[i], 0.0f, color[i], kFillModeSolid);
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