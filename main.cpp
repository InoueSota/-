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
	int background = Novice::LoadTexture("./resource./Background.png");
	int drain = Novice::LoadAudio("./resource./ponyo.wav");
	//
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
		//プレイヤー本体
		slash.Process(players, screen, preKeys[DIK_SPACE], keys[DIK_SPACE]);
		players.Process(players, preKeys[DIK_SPACE], keys[DIK_SPACE], preKeys[DIK_D], keys[DIK_D]);
		players.SetPlayers(players);
		players.Ripples(screen, players, preKeys[DIK_SPACE], keys[DIK_SPACE]);
		players.SetScrollPos(screen, players, preKeys[DIK_SPACE], keys[DIK_SPACE]);
		//パーティクル処理
		Pparticle.ParticleProcess(players, screen);
		switch (scene)
		{
		case TITLE:
			title.Process(preKeys[DIK_SPACE], keys[DIK_SPACE]);
			if (Drain_InTitle(players, title.Targetpos, title.kTargetRadius) == true) {
				title.isTitleClear = true;
			}
			if (title.isTitleClear == true) {
				scene = INGAME;
			}
			break;
		case INGAME:
			////セット
			players.SetZoom(screen, players);
			//アビリティ
			slash.Process(players, screen, preKeys[DIK_SPACE], keys[DIK_SPACE]);
			beam.Process(players, screen);
			switch (wave.stage) {
			case wave.stage_1_only:
				if (!wave.stage_1_set_flag) {
					stage_1.Set_Map(0, 0, 2000, RED);
					for (int i = 0; i < Figure::FigureMax; i++) {
						ellipse[i].set(players, screen, stage_1,wave);
					}
					wave.stage_1_set_flag = true;
					wave.boss_set_flag = false;
				}
				else {
					for (int i = 0; i < Figure::FigureMax; i++) {
						if (ellipse[i].responflag == true) {
							ellipse[i].reset();
						}
						if (Drain_Check_Ellipse(players, ellipse[i])) {
							if (Drain_Center_Circle(players, ellipse[i]) == true && ellipse[i].flag == true && ellipse[i].responflag==false) {
								Novice::PlayAudio(drain, 0, 0.5);
								players.radius += (ellipse[i].radian / 100);
								players.Length += (ellipse[i].radian / 15);
								ellipse[i].flag = false;
							}
						}
					}

					for (int i = 0; i < Figure::FigureMax; i++) {
						if (ellipse[i].flag == false) {
							ellipse[i].cooltime++;
							if (ellipse[i].cooltime % 30 == 0) {
								ellipse[i].respon(players, screen, stage_1,wave);
							}
						}
					}

					if (players.radius >= wave.MapChenge(stage_1)) {
						wave.stage = wave.stage_2;
					}
					wave.stage_1_draw_flag = true;
				}
				break;
			case wave.stage_2:

				if (!wave.stage_2_set_flag) {
					stage_2.Set_Map(0, 0, 5000, RED);
					//
					/*boss.set(Vec2(RAND(1000, 1500), RAND(1000, 1500)));*/

					for (int i = 0; i < Figure::FigureMax; i++) {
						ellipse[i].set(players, screen, stage_2,wave);
						triangle[i].set(players, screen, stage_2);
						quadrangle[i].set(players, screen, stage_2);
						seed[i].set(players, screen, stage_2, triangle[i].position, 3);
					}
					wave.stage_2_set_flag = true;

				}
				else {

					/*ボス関係*/
					/*boss.Keep_Up(players);*/

					item.Set_Item(RAND(0, 1000), RAND(0, 1000), players, RAND(0, 0));

					if (item.Item_collision(players, screen) == true) {

						item.Randam_Item();

					}

					item.Result(players, screen);



					

					for (int i = 0; i < Figure::FigureMax; i++) {
						if (ellipse[i].responflag == true) {
							ellipse[i].reset();
						}
						if (triangle[i].responflag == true) {
							triangle[i].reset();
						}
						if (quadrangle[i].responflag == true) {
							quadrangle[i].reset();
						}

						/*if (ellipse[i].InScreen(players, ellipse[i].position, screen)) {
							ellipse[i].count++;
							if (ellipse[i].count >= ellipse[i].count_state && ellipse[i].count <= ellipse[i].count_end) {
								ellipse[i].Update(players);
							}
						}*/

						if (triangle[i].InScreen(players, triangle[i].position, screen) && triangle[i].responflag == false) {
							triangle[i].Update(players, screen, stage_2, seed[i]);
							if (triangle[i].triangle_death && seed[i].UpdateFlag) {
								seed[i].Update(players, screen, stage_2);
							}
							/*if (!seed[i].setFlag && !seed[i].UpdateFlag) {
								seed[i].respon(players, screen, triangle[i].position, stage_1);
							}*/

						}

						if (quadrangle[i].InScreen(players, quadrangle[i].position, screen) && quadrangle[i].responflag == false) {
							quadrangle[i].Update(players, screen, stage_2);
						}


						if (Drain_Check_Ellipse(players, ellipse[i])) {
							if (Drain_Center_Circle(players, ellipse[i]) == true && ellipse[i].flag == true && ellipse[i].responflag == false) {
								Novice::PlayAudio(drain, 0, 0.5);
								players.radius += (ellipse[i].radian / 100);
								players.Length += (ellipse[i].radian / 15);
								ellipse[i].flag = false;
							}
						}
						if (Drain_Check_Triangle(players, triangle[i])) {
							if (Drain_Center_Triangle(players, triangle[i]) == true && triangle[i].flag == true && triangle[i].responflag == false) {
								Novice::PlayAudio(drain, 0, 0.5);
								players.radius += (triangle[i].radian / 100);
								players.Length += (triangle[i].radian / 15);
								triangle[i].flag = false;
								seed[i].UpdateFlag = false;
							}
						}
						if (Drain_Check_Quadrangle(players, quadrangle[i])) {
							if (Drain_Center_Quad(players, quadrangle[i]) == true && quadrangle[i].flag == true && quadrangle[i].responflag == false) {
								Novice::PlayAudio(drain, 0, 0.5);
								players.radius += (quadrangle[i].radian / 100);
								players.Length += (quadrangle[i].radian / 15);
								quadrangle[i].flag = false;
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


					stage_2.Map_Collision(players);
					for (int i = 0; i < Figure::FigureMax; i++) {

						if (ellipse[i].flag == false) {
							ellipse[i].cooltime++;
							if (ellipse[i].cooltime % 30 == 0) {
								ellipse[i].respon(players, screen, stage_2,wave);
							}
						}
						if (triangle[i].flag == false && !seed[i].UpdateFlag && !triangle[i].triangle_death) {
							triangle[i].cooltime++;
							if (triangle[i].cooltime % 30 == 0) {
								triangle[i].respon(players, screen, stage_2);
								seed[i].respon(players, screen, triangle[i].position, stage_2);
							}
						}
						if (quadrangle[i].flag == false) {
							quadrangle[i].cooltime++;
							if (quadrangle[i].cooltime % 30 == 0) {
								quadrangle[i].respon(players, screen, stage_2);
							}
						}

					}
					if (players.radius >= wave.MapChenge(stage_2)) {
						wave.stage = wave.boss_stage;
					}
					wave.stage_2_draw_flag = true;
				}


				break;
			case wave.boss_stage:

				/*ボス関係*/
				/*boss.Keep_Up(players);*/

				item.Set_Item(RAND(0, 1000), RAND(0, 1000), players, RAND(0, 0));

				if (item.Item_collision(players, screen) == true) {

					item.Randam_Item();

				}

				item.Result(players, screen);
				if (!wave.boss_set_flag) {
					wave.stage_2_set_flag = false;
					///一回だけのやつ
					boss.set(Vec2(RAND(1000, 1500), RAND(1000, 1500)));

					wave.boss_set_flag = true;
				}
				//処理書いてね
				/*ボス関係*/
				boss.Keep_Up(players);
				boss.Result(players, screen, RAND(0, 1));
				if (Slash_Boss(slash, boss) == true){
					boss.radian-=0.5f;
				}
				break;
			case wave.rest:

				break;
			}
			/*stage_1.Set_Map(0, 0, 2000,RED);*/
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
			//Novice::DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0x160036FF, kFillModeSolid);
			Novice::DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0x2B1247FF, kFillModeSolid);
			for (int y = -4; y < 5; y++) {
				for (int x = -4; x < 5; x++) {
					int width = 4000;
					int height = 3000;
					screen.DrawQuad(x * width, y * height, x * width + width, y * height, x * width, y * height + height, x * width + width, y * height + height, 0, 0, 2000, 1500, background, BLACK);
				}
			}
			title.Draw(screen, title);
			Pparticle.DrawParticle(screen);
			players.Draw(screen, players);
			slash.Draw(screen);
			break;
		case INGAME:
			//背景描画
			Novice::DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0x160036FF, kFillModeSolid);
			Novice::DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0x2B1247FF, kFillModeSolid);
			for (int y = -4; y < 5; y++) {
				for (int x = -4; x < 5; x++) {
					int width = 4000;
					int height = 3000;
					screen.DrawQuad(x * width, y * height, x * width + width, y * height, x * width, y * height + height, x * width + width, y * height + height, 0, 0, 2000, 1500, background, BLACK);
				}
			}
			switch (wave.stage) {
			case wave.stage_1_only:
				if (wave.stage_1_set_flag && wave.stage_1_draw_flag) {
					stage_1.DrawMap(screen);
					for (int i = 0; i < Figure::FigureMax; i++) {
						if (ellipse[i].cheakdraw(players, ellipse[i].position, screen, ellipse[i].flag)) {
							ellipse[i].draw(screen, players);
						}
					}

					Pparticle.DrawParticle(screen);
					slash.Draw(screen);
					beam.Draw(screen);
					players.Draw(screen, players);

					item.Draw(screen, players);
				}

				break;
			case wave.stage_2:
				if (wave.stage_2_set_flag && wave.stage_2_draw_flag) {
					stage_2.DrawMap(screen);
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
							quadrangle[i].breaddraw(screen);
							quadrangle[i].draw(screen);

						}


					}



					Pparticle.DrawParticle(screen);
					slash.Draw(screen);
					beam.Draw(screen);
					players.Draw(screen, players);

					item.Draw(screen, players);
				}
				break;
			case wave.boss_stage:
				Pparticle.DrawParticle(screen);
				slash.Draw(screen);
				beam.Draw(screen);
				players.Draw(screen, players);

				item.Draw(screen, players);
				boss.draw(screen);
				break;
			case wave.rest:

				break;
			}


			//players.Draw_Rand_Skin(screen,preKeys[DIK_SPACE],keys[DIK_SPACE]);
			//Novice::ScreenPrintf(0, 20,"zoomed_prad= %f", players.radius*screen.Zoom.x);
			//Novice::ScreenPrintf(0, 0, "%d", boss.count);
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
