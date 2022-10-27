#pragma once
#include "Map.h"
#include "easing.h"
class WAVE
{
public:
	WAVE();
	enum Wave {
		stage_1_only,
		stage_2,
		stage_3,
		boss_stage,
		rest,
	};
	float MapChenge(Map map);
	int stage;

	bool stage_1_set_flag;
	bool stage_2_set_flag;
	bool stage_3_set_flag;
	bool boss_set_flag;

	bool stage_1_draw_flag;
	bool stage_2_draw_flag;
	bool stage_3_draw_flag;
	bool boss_draw_flag;

	void WaveStart();
	void WaveDraw();
	void Init();

	bool isStart_stage_1;
	bool isStart_stage_2;
	bool isStart_stage_3;
	bool isStart_boss_stage;

	static constexpr int kWaveMax = 4;

	int frame[kWaveMax];
	Vec2 pos[kWaveMax];
	Quad poss[kWaveMax];
	float Feasingt[kWaveMax];
	float Eeasingt[kWaveMax];
	bool isDisplay[kWaveMax];

	bool isLoadTexture;
	int wave;
};

