#include "Wave.h"

WAVE::WAVE() {
	stage = boss_stage;
	stage_1_set_flag = false;
	stage_2_set_flag = false;
	stage_3_set_flag = false;
	boss_set_flag = false;
	stage_1_draw_flag = false;
	stage_2_draw_flag = false;
	boss_draw_flag = false;
	isStart_stage_1 = false;
	isStart_stage_2 = false;
	isStart_stage_3 = false;
	isStart_boss_stage = false;
	for (int i = 0; i < kWaveMax; i++){
		frame[i] = 0;
		pos[i] = { -SCREEN_WIDTH, 0 };
		isDisplay[i] = false;
	}
	isLoadTexture = false;
};

float WAVE::MapChenge(Map map) {
	return map.radius * 0.04;
}

void WAVE::WaveStart() {
	if (isLoadTexture == false) {
		wave = Novice::LoadTexture("./resource/Wave/Wave.png");
		isLoadTexture = true;
	}
		if (stage == stage_1_only && isStart_stage_1 == true) {
			isDisplay[0] = true;
			Feasingt[0] += 0.01f;
			Feasingt[0] = Clamp(Feasingt[0], 0.0f, 1.0f);
			pos[0].x = Lerp(Easing::easeOutCubic(Feasingt[0]), SCREEN_WIDTH) - SCREEN_WIDTH;
			if (Feasingt[0] == 1.0f) {
				frame[0]++;
				if (frame[0] >= 120) {
					Eeasingt[0] += 0.01f;
					Eeasingt[0] = Clamp(Eeasingt[0], 0.0f, 1.0f);
					pos[0].x = Lerp(Easing::easeInCubic(Eeasingt[0]), SCREEN_WIDTH);
					if (Eeasingt[0] == 1.0f) {
						isDisplay[0] = false;
					}
				}
			}
		}
		if (stage == stage_2 && isStart_stage_2 == true) {
			isDisplay[1] = true;
			Feasingt[1] += 0.01f;
			Feasingt[1] = Clamp(Feasingt[1], 0.0f, 1.0f);
			pos[1].x = Lerp(Easing::easeOutCubic(Feasingt[1]), SCREEN_WIDTH) - SCREEN_WIDTH;
			if (Feasingt[1] == 1.0f) {
				frame[1]++;
				if (frame[1] >= 120) {
					Eeasingt[1] += 0.01f;
					Eeasingt[1] = Clamp(Eeasingt[1], 0.0f, 1.0f);
					pos[1].x = Lerp(Easing::easeInCubic(Eeasingt[1]), SCREEN_WIDTH);
					if (Eeasingt[1] == 1.0f) {
						isDisplay[1] = false;
					}
				}
			}
		}
		if (stage == stage_3 && isStart_stage_3 == true) {
			isDisplay[2] = true;
			Feasingt[2] += 0.01f;
			Feasingt[2] = Clamp(Feasingt[2], 0.0f, 1.0f);
			pos[2].x = Lerp(Easing::easeOutCubic(Feasingt[2]), SCREEN_WIDTH) - SCREEN_WIDTH;
			if (Feasingt[2] == 1.0f) {
				frame[2]++;
				if (frame[2] >= 120) {
					Eeasingt[2] += 0.01f;
					Eeasingt[2] = Clamp(Eeasingt[2], 0.0f, 1.0f);
					pos[2].x = Lerp(Easing::easeInCubic(Eeasingt[2]), SCREEN_WIDTH);
					if (Eeasingt[2] == 1.0f) {
						isDisplay[2] = false;
					}
				}
			}
		}
		if (stage == boss_stage && isStart_boss_stage == true) {
			isDisplay[3] = true;
			Feasingt[3] += 0.01f;
			Feasingt[3] = Clamp(Feasingt[3], 0.0f, 1.0f);
			pos[3].x = Lerp(Easing::easeOutCubic(Feasingt[3]), SCREEN_WIDTH) - SCREEN_WIDTH;
			if (Feasingt[3] == 1.0f) {
				frame[3]++;
				if (frame[3] >= 120) {
					Eeasingt[3] += 0.01f;
					Eeasingt[3] = Clamp(Eeasingt[3], 0.0f, 1.0f);
					pos[3].x = Lerp(Easing::easeInCubic(Eeasingt[3]), SCREEN_WIDTH);
					if (Eeasingt[3] == 1.0f) {
						isDisplay[3] = false;
					}
				}
			}
		}


}
void WAVE::WaveDraw() {
	for (int i = 0; i < kWaveMax; i++){
		if (isDisplay[i] == true) {
			poss[i] = {
				{pos[i].x, pos[i].y},
				{pos[i].x + SCREEN_WIDTH, pos[i].y},
				{pos[i].x, pos[i].y + SCREEN_HEIGHT},
				{pos[i].x + SCREEN_WIDTH, pos[i].y + SCREEN_HEIGHT}
			};
			Novice::DrawQuad(poss[i].LeftTop.x, poss[i].LeftTop.y, poss[i].RightTop.x, poss[i].RightTop.y, poss[i].LeftBottom.x, poss[i].LeftBottom.y, poss[i].RightBottom.x, poss[i].RightBottom.y, i * SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT, wave, WHITE);
		}
	}
}