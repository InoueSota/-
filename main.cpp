#include "main.h"

const char kWindowTitle[] = "キューイン";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, SCREEN_WIDTH, SCREEN_HEIGHT);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//
	Gclear.GLoadTexture();
	int background = Novice::LoadTexture("./resource./Background.png");
	int drain = Novice::LoadAudio("./resource./ponyo.wav");

	sound.Title = Novice::LoadAudio("./resource/t_boss.mp3");

	sound.stage_1 = Novice::LoadAudio("./resource/stage.mp3");
	sound.stage_2=Novice::LoadAudio("./resource/t_boss.mp3");
	sound.stage_3 = Novice::LoadAudio("./resource/t_boss.mp3");
	sound.stage_boss= Novice::LoadAudio("./resource/t_boss.mp3");

	sound.Clear= Novice::LoadAudio("./resource/t_boss.mp3");

	int isFull = 1;
	

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		while (!((oldTime + 16) - clock() <= 0));

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		//スクリーン関係
		if (preKeys[DIK_F] == 0 && keys[DIK_F]) {
			isFull *= -1;
		}
		if (isFull == 1) {
			Novice::SetWindowMode(kWindowed);
		}
		if (isFull == -1) {
			Novice::SetWindowMode(kFullscreen);
		}
		/*　プレイヤー関係の関数（それぞれの意味はPlayer.hに記述）　*/
		//アビリティ処理
		slash.Process(players, screen, preKeys[DIK_SPACE], keys[DIK_SPACE]);
		beam.Process(players, screen);
		//プレイヤー本体
		players.Process(players, preKeys[DIK_SPACE], keys[DIK_SPACE], title, Gclear, screen, map);
		players.SetPlayers(players);
		players.Ripples(screen, players, preKeys[DIK_SPACE], keys[DIK_SPACE], map);
		players.SetScrollPos(screen, players, preKeys[DIK_SPACE], keys[DIK_SPACE], map);
		players.SetZoom(screen, players, title);
		//パーティクル処理
		Pparticle.ParticleProcess(players, screen);
		//ウェーブ処理
		wave.WaveStart();
		if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE]) {
			sound.Space_Sound();
		}
		switch (scene)
		{
		case TITLE:

			title.Process(preKeys[DIK_SPACE], keys[DIK_SPACE]);
			if (Drain_InTitle(players, title.Targetpos, title.kTargetRadius) == true) {
				title.isDrainClear = true;
			}
			if (title.isTitleClear == true) {
				players.isTitleClear = true;
				sound.Idou_Sound();
				scene = CHANGE;
			}

			break;
		case CHANGE:
			change.Process(Gclear);
			//セット
			players.SetZoom(screen, players, title);
			if (!wave.stage_1_set_flag) {
				map.Set_Map(0, 0, 2000, RED);
				for (int i = 0; i < Figure::FigureMax; i++) {
					ellipse[i].set(players, screen, map, wave);
				}
				wave.boss_set_flag = false;
				wave.stage_1_set_flag = true;
			}
			if (change.isChangeClear == true) {
				change.color = 0x000000FF;
				change.frame = 0;
				change.alphat = 0.0f;
				wave.stage = wave.stage_1_only;
				scene = INGAME;
			}
			break;
		case INGAME:

			switch (wave.stage) {
			case wave.stage_1_only:
				wave.isStart_stage_1 = true;

				if (wave.stage_1_set_flag == true) {
					for (int i = 0; i < Figure::FigureMax; i++) {
						if (ellipse[i].responflag == true) {
							ellipse[i].reset(players);
						}
						ellipse[i].Update(players, screen, map, wave);
						if (Drain_Check_Ellipse(players, ellipse[i])) {
							if (Drain_Center_Circle(players, ellipse[i]) == true && ellipse[i].flag == true && ellipse[i].responflag == false) {
								Novice::PlayAudio(drain, 0, 0.5);
								players.SizeIncrease(players);
								ellipse[i].flag = false;
							}
						}
						if (ellipse[i].Player_Ellipse(players) == true) {
							players.SizeDecrease(players, wave.stage);
							screen.Shake(0, 10, 0, 10, true);
						}

					}

					for (int i = 0; i < Figure::FigureMax; i++) {
						if (ellipse[i].flag == false) {
							ellipse[i].cooltime++;
							if (ellipse[i].cooltime % 30 == 0) {
								ellipse[i].respon(players, screen, map, wave);
							}
						}
					}

					if (players.radius >= wave.MapChenge(map)) {
						wave.stage = wave.stage_2;
					}
				}
				bar.Update(players, map, wave);
				wave.stage_1_draw_flag = true;
				break;
			case wave.stage_2://中ボス
				wave.isStart_stage_2 = true;
				//中ボス追加
				if (!wave.stage_2_set_flag) {

					wave.stage_1_set_flag = false;

					map.Set_Map(0, 0, 5000, RED);

					tboss.t_set(Vec2(RAND(1000, 1500), RAND(1000, 1500)));

					wave.stage_2_set_flag = true;

					for (int i = 0; i < Figure::FigureMax; i++) {
						ellipse[i].set(players, screen, map, wave);
						triangle[i].set(players, screen, map, wave);
						seed[i].set(players, screen, map, triangle[i].position, 3);
					}

				}
				//処理書いてね
				/*ボス関係*/
				/*ボス関係*/
				if (tboss.shild != 0) {
					tboss.Keep_Up(players);//追いかけ続けるやつ
					tboss.Result(players, screen, RAND(1, 1), sound);//追いかけて着る
				}


				if (slash.isOccur == true && Slash_EX_Boss(slash, tboss) == true) {
					tboss.radian -= 100;
					slash.isOccur = false;//これどうするか阿多ttら消える処理
					tboss.hit = true;
					tboss.damepar = true;
				}
				else {
					tboss.hit = false;
				}
				tboss.Dame_Par();//ダメージ受けた時のパーティクル

				if (tboss.shild != 0) {



					/*if (beam.isOccur == true) {
						if (Beam_Boss(beam, tboss) == true) {
							tboss.radian -= 0.5f;
						}
					}*/

					if (tboss.radian < 500) {
						tboss.shild = 1;
						if (tboss.radian < 400) {
							tboss.shild = 0;

						}
					}
				}


				///プレイヤーに攻撃が当たった時
				if (tboss.Bullet_Player(players) == true) {
					players.SizeDecrease(players, wave.stage);
					screen.Shake(-5, 500, -5, 5, true);

				}
				if (tboss.Bullet_Player_2(players) == true) {

					players.SizeDecrease(players, wave.stage);
				}
				if (tboss.Blade_Player(players) == true) {

					players.SizeDecrease(players, wave.stage);

				}
				screen.Shake(-5, 5, -5, 5, tboss.Blade_Player(players));
				screen.Shake(-5, 5, -5, 5, tboss.Bullet_Player_2(players));

				//ボスのプレイヤーが当たった時

				if (tboss.shild != 0 && tboss.Boss_Player(players) == true && players.Muteki == false) {  //ボスのシールドがある、俺が無敵じゃない、当たる
					players.Muteki = true;
					players.Reverse *= -1;
					players.SizeDecrease(players, wave.stage);

				}
				else if (players.Muteki == true) {
					players.MutekiTime();

				}
				//クリア条件
				if (tboss.shild == 0) {
					tboss.bossgekiha();
					tboss.Rune_Par();
				}

				if (tboss.shild == 0 && tboss.Boss_Player(players) == true) {
					wave.stage = wave.stage_3;
					players.radius = 80;
				}
				screen.Shake(-5, 5, -5, 5, tboss.Boss_Player(players));


				//Update
				for (int i = 0; i < Figure::FigureMax; i++) {
					if (ellipse[i].responflag == true) {
						ellipse[i].reset(players);
					}
					if (triangle[i].responflag == true) {
						triangle[i].reset(players);
					}
					ellipse[i].Update(players, screen, map, wave);
					if (Drain_Check_Ellipse(players, ellipse[i])) {
						if (Drain_Center_Circle(players, ellipse[i]) == true && ellipse[i].flag == true && ellipse[i].responflag == false) {
							Novice::PlayAudio(drain, 0, 0.5);
							players.SizeIncrease(players);
							ellipse[i].flag = false;
						}
					}
					if (triangle[i].InScreen(players, triangle[i].position, screen) && triangle[i].responflag == false) {
						triangle[i].Update(players, screen, map, seed[i]);
						if (triangle[i].triangle_death && seed[i].UpdateFlag) {
							seed[i].Update(players, screen, map);
						}
					}
					if (ellipse[i].Player_Ellipse(players) == true) {
						players.SizeDecrease(players, wave.stage);
						screen.Shake(0, 10, 0, 10, true);
					}
					if (triangle[i].Player_Triangle(players) == true) {
						players.SizeDecrease(players, wave.stage);
						screen.Shake(0, 10, 0, 10, true);
					}
					if (triangle[i].triangle_death && seed[i].UpdateFlag) {
						for (int t = 0; t < 3; t++) {
							if (seed[i].Player_Seed(players, seed[i].position[t])) {
								players.SizeDecrease(players, wave.stage);
								screen.Shake(0, 10, 0, 10, true);
							}
						}
					}
					if (Drain_Check_Triangle(players, triangle[i])) {
						if (Drain_Center_Triangle(players, triangle[i]) == true && triangle[i].flag == true && triangle[i].responflag == false) {
							Novice::PlayAudio(drain, 0, 0.5);
							slash.spd += 0.2f;
							players.SizeIncrease(players);
							triangle[i].flag = false;
							seed[i].UpdateFlag = false;
							seed[i].t = 0;
						}
					}
				}
				//Respon
				for (int i = 0; i < Figure::FigureMax; i++) {

					if (ellipse[i].flag == false) {
						ellipse[i].cooltime++;
						if (ellipse[i].cooltime % 120 == 0) {
							ellipse[i].respon(players, screen, map, wave);
						}
					}
					if (triangle[i].flag == false && !seed[i].UpdateFlag && !triangle[i].triangle_death) {
						triangle[i].cooltime++;
						if (triangle[i].cooltime % 120 == 0) {
							triangle[i].respon(players, screen, map, wave);
							seed[i].respon(players, screen, triangle[i].position, map);
						}
					}
				}
				wave.stage_2_draw_flag = true;
				break;
			case wave.stage_3:
				wave.isStart_stage_3 = true;
				if (!wave.stage_3_set_flag) {

					wave.stage_2_set_flag = false;
					map.Set_Map(0, 0, 6000, RED);
					///一回だけのやつ
					for (int i = 0; i < Figure::FigureMax; i++) {
						ellipse[i].set(players, screen, map, wave);
						triangle[i].set(players, screen, map, wave);
						quadrangle[i].set(players, screen, map);
						seed[i].set(players, screen, map, triangle[i].position, 3);
					}

					wave.stage_3_set_flag = true;
				}




				for (int i = 0; i < Figure::FigureMax; i++) {
					if (ellipse[i].responflag == true) {
						ellipse[i].reset(players);
					}
					if (triangle[i].responflag == true) {
						triangle[i].reset(players);
					}
					if (quadrangle[i].responflag == true) {
						quadrangle[i].reset(players);
					}

					/*if (ellipse[i].InScreen(players, ellipse[i].position, screen)) {
						ellipse[i].count++;
						if (ellipse[i].count >= ellipse[i].count_state && ellipse[i].count <= ellipse[i].count_end) {
							ellipse[i].Update(players);
						}
					}*/

					if (triangle[i].InScreen(players, triangle[i].position, screen) && triangle[i].responflag == false) {
						triangle[i].Update(players, screen, map, seed[i]);
						if (triangle[i].triangle_death && seed[i].UpdateFlag) {
							seed[i].Update(players, screen, map);
						}
					}

					if (quadrangle[i].InScreen(players, quadrangle[i].position, screen) && quadrangle[i].responflag == false && quadrangle[i].flag == true) {
						quadrangle[i].Update(players, screen, map, wave);
					}

					if (ellipse[i].Player_Ellipse(players) == true) {
						players.SizeDecrease(players, wave.stage);
						screen.Shake(0, 10, 0, 10, true);
					}

					if (triangle[i].Player_Triangle(players) == true) {
						players.SizeDecrease(players, wave.stage);
						screen.Shake(0, 10, 0, 10, true);
					}
					if (triangle[i].triangle_death && seed[i].UpdateFlag) {
						for (int t = 0; t < 3; t++) {
							if (seed[i].Player_Seed(players, seed[i].position[t])) {
								players.SizeDecrease(players, wave.stage);
								screen.Shake(0, 10, 0, 10, true);
							}
						}

					}
					if (quadrangle[i].Player_Quadrangle(players) == true) {
						players.SizeDecrease(players, wave.stage);
						screen.Shake(0, 10, 0, 10, true);
					}
					if (quadrangle[i].UpdatesetFlag) {
						if (quadrangle[i].Player_Update(players)) {
							players.SizeDecrease(players, wave.stage);
							screen.Shake(0, 10, 0, 10, true);
						}
					}

					if (Drain_Check_Ellipse(players, ellipse[i])) {
						if (Drain_Center_Circle(players, ellipse[i]) == true && ellipse[i].flag == true && ellipse[i].responflag == false) {
							Novice::PlayAudio(drain, 0, 0.5);
							players.SizeIncrease(players);
							ellipse[i].flag = false;
						}
					}
					if (Drain_Check_Triangle(players, triangle[i])) {
						if (Drain_Center_Triangle(players, triangle[i]) == true && triangle[i].flag == true && triangle[i].responflag == false) {
							Novice::PlayAudio(drain, 0, 0.5);
							slash.spd += 0.2f;
							players.SizeIncrease(players);
							triangle[i].flag = false;
							seed[i].UpdateFlag = false;
							seed[i].t = 0.0f;
						}
					}
					if (Drain_Check_Quadrangle(players, quadrangle[i])) {
						if (Drain_Center_Quad(players, quadrangle[i]) == true && quadrangle[i].flag == true && quadrangle[i].responflag == false && quadrangle[i].UpdatesetFlag == false) {
							Novice::PlayAudio(drain, 0, 0.5);
							players.SizeIncrease(players);
							quadrangle[i].flag = false;
							quadrangle[i].drawflag = false;
							quadrangle[i].t = 0.0f;
							quadrangle[i].count = 0;
							quadrangle[i].BreadOpenFlag = false;
							quadrangle[i].BreadCloseFlag = false;
							quadrangle[i].UpdatesetFlag = false;
							/////ブレード1
							//quadrangle[i].bread_1_top_left_position_end = { -20,-20 };
							//quadrangle[i].bread_1_top_right_position_end = { -20,-20 };
							//quadrangle[i].bread_1_bottom_left_position_end = { -20,-20 };
							//quadrangle[i].bread_1_bottom_right_position_end = { -20,-20 };
							////ブレード2
							//quadrangle[i].bread_2_top_left_position_end = { -20,-20 };
							//quadrangle[i].bread_2_top_right_position_end = { -20,-20 };
							//quadrangle[i].bread_2_bottom_left_position_end = { -20,-20 };
							//quadrangle[i].bread_2_bottom_right_position_end = { -20,-20 };
						}

					}
					//if (IsHit_Drain(players.pos.x, players.pos.y, players.radius, ellipse[i], triangle[i], quadrangle[i], screen.Zoom.x) == true && ellipse[i].flag == true) {
					//	players.radius -= (ellipse[i].radian / 100);
					//	players.Length -= (ellipse[i].radian / 100);
					//}
				}
				if (players.radius < 10) {
					players.radius = 10;
				}


				/*stage_3.Map_Collision(players);*///これボイドじゃないよ
				for (int i = 0; i < Figure::FigureMax; i++) {

					if (ellipse[i].flag == false) {
						ellipse[i].cooltime++;
						if (ellipse[i].cooltime % 120 == 0) {
							ellipse[i].respon(players, screen, map, wave);
						}
					}
					if (triangle[i].flag == false && seed[i].UpdateFlag == false && triangle[i].triangle_death == true) {
						triangle[i].cooltime++;
						if (triangle[i].cooltime % 30 == 0) {
							triangle[i].respon(players, screen, map, wave);
							seed[i].respon(players, screen, triangle[i].position, map);
						}
					}
					if (quadrangle[i].flag == false) {
						quadrangle[i].cooltime++;
						if (quadrangle[i].cooltime % 30 == 0) {
							quadrangle[i].respon(players, screen, map);
						}
					}

				}
				if (players.radius >= wave.MapChenge(map)) {
					wave.stage = wave.boss_stage;
				}
				/*wave.stage_2_draw_flag = true;*/
				bar.Update(players, map, wave);

				break;

			case wave.boss_stage:
				wave.isStart_boss_stage = true;

				/*ボス関係*/
				if (!wave.boss_set_flag) {
					wave.stage_3_set_flag = false;
					///一回だけのやつ
					boss.set(Vec2(RAND(1000, 1500), RAND(1000, 1500)));
					map.Set_Map(0, 0, 10000, RED);
					wave.boss_set_flag = true;
				}
				//処理書いてね
				/*ボス関係*/
				if (boss.shild != 0) {
					boss.Keep_Up(players);
					boss.Result(players, screen, RAND(0, 3), sound);
				}
				if (Slash_EX_Boss(slash, boss) == true) {

					boss.radian -= 100;
					slash.isOccur = false;//これどうするか阿多ttら消える処理
					boss.hit = true;
					boss.damepar = true;
				}
				else {
					boss.hit = false;
				}
				boss.Dame_Par();//ダメージ受けた時のパーティクル



				if (beam.isOccur == true) {
					if (Beam_Boss(beam, boss) == true) {
						boss.radian -= 1.05f;
					}
				}
				if (boss.radian < 1000) {
					boss.shild = 2;
					if (boss.radian < 750) {
						boss.shild = 1;
						if (boss.radian < 500) {
							boss.shild = 0;

						}
					}
				}


				///プレイヤーに攻撃が当たった時
				if (boss.Bullet_Player(players) == true) {
					players.SizeDecrease(players, wave.stage);
					screen.Shake(-5, 5, -5, 5, boss.Bullet_Player(players));

				}
				if (boss.Bullet_Player_2(players) == true) {
					players.radius -= 0.5f;
					screen.Shake(-5, 5, -5, 5, boss.Bullet_Player_2(players));

				}
				if (boss.Blade_Player(players) == true || boss.Blade_Player_2(players) == true) {
					players.radius -= 0.5f;
					screen.Shake(-5, 5, -5, 5, boss.Blade_Player(players));


				}
				//ボスのプレイヤーが当たった時

				if (boss.shild != 0 && boss.Boss_Player(players) == true && players.Muteki == false) {  //ボスのシールドがある、俺が無敵じゃない、当たる
					players.Muteki = true;
					players.Reverse *= -1;
					players.SizeDecrease(players, wave.stage);

				}
				else if (players.Muteki == true) {
					players.MutekiTime();
				}
				if (boss.shild == 0) {
					boss.bossgekiha();
					boss.Rune_Par();
				}
				//クリア条件
				if (boss.shild == 0 && boss.Boss_Player(players) == true) {
					Gclear.isKillBoss = true;
				}
				if (Gclear.isKillBoss == true) {
					Gclear.KillBoss();
				}
				if (Gclear.CircleEasingt[1] == 1.0f) {
					scene = GAMECLEAR;
				}
				if (boss.shild != 0 && boss.Boss_Player(players) == true && players.Muteki == false) {  //ボスのシールドがある、俺が無敵じゃない、当たる
					players.Muteki = true;
					players.Reverse *= -1;
					players.radius -= 1;
				}
				else if (players.Muteki == true) {
					players.MutekiTime();
				}
				//クリア条件
				if (boss.shild == 0 && boss.Boss_Player(players) == true) {
					Gclear.isKillBoss = true;
				}
				if (Gclear.isKillBoss == true) {
					Gclear.KillBoss();
				}
				if (Gclear.CircleEasingt[1] == 1.0f) {
					scene = GAMECLEAR;
				}
				//////////////////
				//養分処理
				for (int i = 0; i < Figure::FigureMax; i++) {
					if (ellipse[i].responflag == true) {
						ellipse[i].reset(players);
					}
					if (triangle[i].responflag == true) {
						triangle[i].reset(players);
					}
					if (quadrangle[i].responflag == true) {
						quadrangle[i].reset(players);
					}

					/*if (ellipse[i].InScreen(players, ellipse[i].position, screen)) {
						ellipse[i].count++;
						if (ellipse[i].count >= ellipse[i].count_state && ellipse[i].count <= ellipse[i].count_end) {
							ellipse[i].Update(players);
						}
					}*/

					if (triangle[i].InScreen(players, triangle[i].position, screen) && triangle[i].responflag == false) {
						triangle[i].Update(players, screen, map, seed[i]);
						if (triangle[i].triangle_death && seed[i].UpdateFlag) {
							seed[i].Update(players, screen, map);
						}
					}

					if (quadrangle[i].InScreen(players, quadrangle[i].position, screen) && quadrangle[i].responflag == false && quadrangle[i].flag == true) {
						quadrangle[i].Update(players, screen, map, wave);
					}

					if (ellipse[i].Player_Ellipse(players) == true) {
						players.SizeDecrease(players, wave.stage);
						screen.Shake(0, 10, 0, 10, true);
					}

					if (triangle[i].Player_Triangle(players) == true) {
						players.SizeDecrease(players, wave.stage);
						screen.Shake(0, 10, 0, 10, true);
					}
					if (triangle[i].triangle_death && seed[i].UpdateFlag) {
						for (int t = 0; t < 3; t++) {
							if (seed[i].Player_Seed(players, seed[i].position[t])) {
								players.SizeDecrease(players, wave.stage);
								screen.Shake(0, 10, 0, 10, true);
							}
						}

					}
					if (quadrangle[i].Player_Quadrangle(players) == true) {
						players.SizeDecrease(players, wave.stage);
						screen.Shake(0, 10, 0, 10, true);
					}
					if (quadrangle[i].UpdatesetFlag) {
						if (quadrangle[i].Player_Update(players)) {
							players.SizeDecrease(players, wave.stage);
							screen.Shake(0, 10, 0, 10, true);
						}
					}

					if (Drain_Check_Ellipse(players, ellipse[i])) {
						if (Drain_Center_Circle(players, ellipse[i]) == true && ellipse[i].flag == true && ellipse[i].responflag == false) {
							Novice::PlayAudio(drain, 0, 0.5);
							players.SizeIncrease(players);
							ellipse[i].flag = false;
						}
					}
					if (Drain_Check_Triangle(players, triangle[i])) {
						if (Drain_Center_Triangle(players, triangle[i]) == true && triangle[i].flag == true && triangle[i].responflag == false) {
							Novice::PlayAudio(drain, 0, 0.5);
							slash.spd += 0.2f;
							players.SizeIncrease(players);
							triangle[i].flag = false;
							seed[i].UpdateFlag = false;
							seed[i].t = 0.0f;
						}
					}
					if (Drain_Check_Quadrangle(players, quadrangle[i])) {
						if (Drain_Center_Quad(players, quadrangle[i]) == true && quadrangle[i].flag == true && quadrangle[i].responflag == false && quadrangle[i].UpdatesetFlag == false) {
							Novice::PlayAudio(drain, 0, 0.5);
							players.SizeIncrease(players);
							quadrangle[i].flag = false;
							quadrangle[i].drawflag = false;
							quadrangle[i].t = 0.0f;
							quadrangle[i].count = 0;
							quadrangle[i].BreadOpenFlag = false;
							quadrangle[i].BreadCloseFlag = false;
							quadrangle[i].UpdatesetFlag = false;
							/////ブレード1
							//quadrangle[i].bread_1_top_left_position_end = { -20,-20 };
							//quadrangle[i].bread_1_top_right_position_end = { -20,-20 };
							//quadrangle[i].bread_1_bottom_left_position_end = { -20,-20 };
							//quadrangle[i].bread_1_bottom_right_position_end = { -20,-20 };
							////ブレード2
							//quadrangle[i].bread_2_top_left_position_end = { -20,-20 };
							//quadrangle[i].bread_2_top_right_position_end = { -20,-20 };
							//quadrangle[i].bread_2_bottom_left_position_end = { -20,-20 };
							//quadrangle[i].bread_2_bottom_right_position_end = { -20,-20 };
						}

					}
					//if (IsHit_Drain(players.pos.x, players.pos.y, players.radius, ellipse[i], triangle[i], quadrangle[i], screen.Zoom.x) == true && ellipse[i].flag == true) {
					//	players.radius -= (ellipse[i].radian / 100);
					//	players.Length -= (ellipse[i].radian / 100);
					//}
				}
				//リスポーン
				for (int i = 0; i < Figure::FigureMax; i++) {

					if (ellipse[i].flag == false) {
						ellipse[i].cooltime++;
						if (ellipse[i].cooltime % 120 == 0) {
							ellipse[i].respon(players, screen, map, wave);
						}
					}
					if (triangle[i].flag == false && seed[i].UpdateFlag == false && triangle[i].triangle_death == true) {
						triangle[i].cooltime++;
						if (triangle[i].cooltime % 30 == 0) {
							triangle[i].respon(players, screen, map, wave);
							seed[i].respon(players, screen, triangle[i].position, map);
						}
					}
					if (quadrangle[i].flag == false) {
						quadrangle[i].cooltime++;
						if (quadrangle[i].cooltime % 30 == 0) {
							quadrangle[i].respon(players, screen, map);
						}
					}

				}
				//////////////////
				break;
			case wave.rest:
				break;
			}
			break;
		case GAMECLEAR:
			Gclear.isGameClear = true;
			gp.ParticleProcess();
			Gclear.Process(screen);
			if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0 && Gclear.isToTitle == false) {
				title.isDrainClear = false;
				change.isChangeClear = false;
				players.isPressSpace = false;
				players.isTitleClear = false;
				Gclear.isKillBoss = false;
				Gclear.isToTitle = true;
				Gclear.isGameClear = true;
			}
			if (Gclear.isToTitle == true) {
				Gclear.ToTitle();
				if (Gclear.TTalphat == 1.0f) {
					title.isTitleClear = false;
					Gclear.isGameClear = false;
					Gclear.alphat = 0.0f;
					Gclear.color = 0xFFFFFF00;
					Gclear.TTcolor = 0x00000000;
					Gclear.TTalphat = 0.0f;
					scene = TITLE;
				}
			}
			break;
		}
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		switch (scene)
		{
		case TITLE:
			//背景描画
			Novice::DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0x2B1247FF, kFillModeSolid);
			for (int y = -4; y < 5; y++) {
				for (int x = -4; x < 5; x++) {
					int width = 4000;
					int height = 3000;
					screen.DrawQuad(x * width, y * height, x * width + width, y * height, x * width, y * height + height, x * width + width, y * height + height, 0, 0, 2000, 1500, background, BLACK);
				}
			}
			Pparticle.DrawParticle(screen);
			players.Draw(screen, players);
			title.Draw(screen, title);

			

			break;
		case CHANGE:
			Novice::DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0x2B1247FF, kFillModeSolid);
			for (int y = -1; y < 1; y++) {
				for (int x = -1; x < 1; x++) {
					int width = 4000;
					int height = 3000;
					screen.DrawQuad(x * width, y * height, x * width + width, y * height, x * width, y * height + height, x * width + width, y * height + height, 0, 0, 2000, 1500, background, BLACK);
				}
			}
			if (wave.stage_1_set_flag/* && wave.stage_1_draw_flag*/) {
				map.DrawMap(screen);
				for (int i = 0; i < Figure::FigureMax; i++) {
					if (ellipse[i].cheakdraw(players, ellipse[i].position, screen, ellipse[i].flag)) {
						ellipse[i].draw(screen, players);
					}
				}
				Pparticle.DrawParticle(screen);
				players.Draw(screen, players);
			}
			change.Draw(screen, Gclear);
			break;
		case INGAME:
			//背景描画
			//Novice::DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0x160036FF, kFillModeSolid);
			Novice::DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0x2B1247FF, kFillModeSolid);
			for (int y = -6; y < 7; y++) {
				for (int x = -6; x < 7; x++) {
					int width = 4000;
					int height = 3000;
					screen.DrawQuad(x * width, y * height, x * width + width, y * height, x * width, y * height + height, x * width + width, y * height + height, 0, 0, 2000, 1500, background, BLACK);
				}
			}
			map.DrawMap(screen);
			switch (wave.stage) {
			case wave.stage_1_only:
				if (wave.stage_1_set_flag/* && wave.stage_1_draw_flag*/) {
					for (int i = 0; i < Figure::FigureMax; i++) {
						if (ellipse[i].cheakdraw(players, ellipse[i].position, screen, ellipse[i].flag)) {
							ellipse[i].draw(screen, players);
						}
					}
					Pparticle.DrawParticle(screen);
					players.Draw(screen, players);

					item.Draw(screen, players);

					bar.beasdraw(screen);
					bar.draw(screen);
				}
				if (Novice::IsPlayingAudio(sound.stage_1_handle) == false || sound.stage_1_handle == -1) {
					sound.stage_1_handle = Novice::PlayAudio(sound.stage_1, 1, 1*music);
				}
				break;
			case wave.stage_2:
				Novice::StopAudio(sound.stage_1_handle);
				for (int i = 0; i < Figure::FigureMax; i++) {
					if (triangle[i].triangle_death && seed[i].UpdateFlag) {
						seed[i].draw(screen);
					}
					if (ellipse[i].cheakdraw(players, ellipse[i].position, screen, ellipse[i].flag)) {
						ellipse[i].draw(screen, players);
					}
					if (triangle[i].cheakdraw(players, triangle[i].position, screen, triangle[i].flag)) {
						triangle[i].draw(screen);
					}
				}
				Pparticle.DrawParticle(screen);
				slash.Draw(screen);
				players.Draw(screen, players);

				item.Draw(screen, players);
				tboss.t_draw(screen);
				if (Novice::IsPlayingAudio(sound.stage_2_handle) == false || sound.stage_2_handle == -1) {
					sound.stage_2_handle = Novice::PlayAudio(sound.stage_2, 1, 1 * music);
				}
				break;
			case wave.stage_3:
				Novice::StopAudio(sound.stage_2_handle);

				//中ボス追加してない
				for (int i = 0; i < Figure::FigureMax; i++) {
					if (triangle[i].triangle_death && seed[i].UpdateFlag) {
						seed[i].draw(screen);
					}
					if (ellipse[i].cheakdraw(players, ellipse[i].position, screen, ellipse[i].flag)) {
						ellipse[i].draw(screen, players);
					}
					if (triangle[i].cheakdraw(players, triangle[i].position, screen, triangle[i].flag)) {
						triangle[i].draw(screen);
					}
					if (quadrangle[i].cheakdraw(players, quadrangle[i].position, screen, quadrangle[i].flag)) {
						if (quadrangle[i].drawflag) {
							quadrangle[i].breaddraw(screen);
						}
						quadrangle[i].draw(screen);
					}
				}
				Pparticle.DrawParticle(screen);
				slash.Draw(screen);
				players.Draw(screen, players);

				item.Draw(screen, players);
				bar.Update(players, map, wave);
				bar.beasdraw(screen);
				bar.draw(screen);
				break;

			case wave.boss_stage:
				//////////////////
				for (int i = 0; i < Figure::FigureMax; i++) {
					if (triangle[i].triangle_death && seed[i].UpdateFlag) {
						seed[i].draw(screen);
					}
					if (ellipse[i].cheakdraw(players, ellipse[i].position, screen, ellipse[i].flag)) {
						ellipse[i].draw(screen, players);
					}
					if (triangle[i].cheakdraw(players, triangle[i].position, screen, triangle[i].flag)) {
						triangle[i].draw(screen);
					}
					if (quadrangle[i].cheakdraw(players, quadrangle[i].position, screen, quadrangle[i].flag)) {
						if (quadrangle[i].drawflag) {
							quadrangle[i].breaddraw(screen);
						}
						quadrangle[i].draw(screen);
					}
				}
				//////////////////
				Pparticle.DrawParticle(screen);
				slash.Draw(screen);
				beam.Draw(screen);

				item.Draw(screen, players);
				boss.draw(screen);
				if (boss.shild == 0/* && boss.Boss_Player(players) == true*/) {
					Gclear.DrawKillBoss();
				}
				players.Draw(screen, players);

				break;
			case wave.rest:

				break;
			}
			wave.WaveDraw();
			break;
		case GAMECLEAR:
			Novice::DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0x2B1247FF, kFillModeSolid);
			gp.DrawParticle();
			Gclear.Draw(screen);
			players.Draw(screen, players);
			Gclear.DrawToTitle();
			break;
		}
		
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		//oldTime = clock();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
