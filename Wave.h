#pragma once
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
	int stage;
	bool stage_1_set_flag;
	bool stage_2_set_flag;
	bool boss_set_flag;
	bool stage_1_draw_flag;
	bool stage_2_draw_flag;
	bool boss_draw_flag;
};

