#include "Particle.h"

PlayerP Pparticle;

//void PlayerP::ParticleInit() {
//    for (int i = 0; i < PARTICLE_MAX; i++) {
//        Pparticle.life[i] = 0;
//    }
//}
//
//void PlayerP::ParticleMake(Player& players) {
//    for (int i = 0; i < PARTICLE_MAX; i++) {
//        if (Pparticle.life[i] <= 0 && Pparticle.frame % 12 == 0) {
//            Pparticle.pos[i] = players.pos;
//            Pparticle.radius[i] = players.radius;
//            Pparticle.life[i] = PARTICLE_LIFE;
//            break;
//        }
//    }
//}
