#include "Wave.h"

WAVE::WAVE() {
	stage = boss_stage;
	stage_1_set_flag = false;
	stage_2_set_flag = false;
	boss_set_flag = false;
	stage_1_draw_flag = false;
	stage_2_draw_flag = false;
	boss_draw_flag = false;
};

float WAVE::MapChenge(Map map) {
	return map.radius * 0.04;
}