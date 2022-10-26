
#include"Sound.h"


Sound::Sound()
{
	stage_1=0;
	stage_1_handle = -1;
	stage_2 = 0;
	stage_2_handle=-1;
	stage_3=0;
	stage_3_handle=-1;
	stage_boss=0;
	stage_boss_handle=-1;
}

void Sound::Space_Sound()
{
	int sound = Novice::LoadAudio("./resource/space.mp3");
	int handle = -1;
	if (Novice::IsPlayingAudio(handle) == false || handle == -1) {
		handle = Novice::PlayAudio(sound, 0, 1);

	}

}
void Sound::Idou_Sound()
{
	int sound = Novice::LoadAudio("./resource/idou.mp3");
	int handle = -1;
	if (Novice::IsPlayingAudio(handle) == false || handle == -1) {
		handle = Novice::PlayAudio(sound, 0, 1);

	}

}
void Sound::Boss_t_Sound()
{
	int sound = Novice::LoadAudio("./resource/boss_p_1.mp3");
	int handle = -1;
	if (Novice::IsPlayingAudio(handle) == false || handle == -1) {
		handle = Novice::PlayAudio(sound, 0, 5);

	}

}

