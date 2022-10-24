#pragma once
#include "Map.h"
class WAVE
{
public:
	WAVE();
	enum Wave {
		stage_1_only,
		stage_2,
		boss_stage,
		rest,
	};
	float MapChenge(Map map);
	int stage;
	bool stage_1_set_flag;
	bool stage_2_set_flag;
	bool boss_set_flag;
	bool stage_1_draw_flag;
	bool stage_2_draw_flag;
	bool boss_draw_flag;
};

