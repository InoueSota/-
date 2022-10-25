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
		players.Process(players, preKeys[DIK_SPACE], keys[DIK_SPACE], preKeys[DIK_D], keys[DIK_D], title);
		players.SetPlayers(players);
		players.Ripples(screen, players, preKeys[DIK_SPACE], keys[DIK_SPACE]);
		players.SetScrollPos(screen, players, preKeys[DIK_SPACE], keys[DIK_SPACE]);
		//パーティクル処理
		Pparticle.ParticleProcess(players, screen);
		//アビリティ処理
		slash.Process(players, screen, preKeys[DIK_SPACE], keys[DIK_SPACE]);
		beam.Process(players, screen);
		switch (scene)
		{
		case TITLE:
			title.Process(preKeys[DIK_SPACE], keys[DIK_SPACE]);
			if (Drain_InTitle(players, title.Targetpos, title.kTargetRadius) == true) {
				title.isDrainClear = true;
			}
			if (title.isTitleClear == true) {
				players.isTitleClear = true;
				scene = CHANGE;
			}
			break;
		case CHANGE:
			change.Process();
			//セット
			players.SetZoom(screen, players);
			if (!wave.stage_1_set_flag) {
				stage_1.Set_Map(0, 0, 2000, RED);
				for (int i = 0; i < Figure::FigureMax; i++) {
					ellipse[i].set(players, screen, stage_1, wave);
				}
				wave.boss_set_flag = false;
				wave.stage_1_set_flag = true;
			}
			if (change.isChangeClear == true) {
				wave.stage = wave.stage_1_only;
				scene = INGAME;
			}
			break;
		case INGAME:
			//セット
			players.SetZoom(screen, players);
			switch (wave.stage) {
			case wave.stage_1_only:
				if (wave.stage_1_set_flag == true) {
					for (int i = 0; i < Figure::FigureMax; i++) {
						if (ellipse[i].responflag == true) {
							ellipse[i].reset();
						}
						ellipse[i].Update(players,screen,stage_1,wave);
						if (Drain_Check_Ellipse(players, ellipse[i])) {
							if (Drain_Center_Circle(players, ellipse[i]) == true && ellipse[i].flag == true && ellipse[i].responflag == false) {
								Novice::PlayAudio(drain, 0, 0.5);
								players.SizeIncrease(players);
								ellipse[i].flag = false;
							}
						}
						if (ellipse[i].Player_Ellipse(players) == true) {
							players.SizeDecrease(players);
						}
					}

					for (int i = 0; i < Figure::FigureMax; i++) {
						if (ellipse[i].flag == false) {
							ellipse[i].cooltime++;
							if (ellipse[i].cooltime % 30 == 0) {
								ellipse[i].respon(players, screen, stage_1, wave);
							}
						}
					}

					if (players.radius >= wave.MapChenge(stage_1)) {
						wave.stage = wave.stage_2;
					}
				}
				bar.Update(players, stage_1, wave);
				break;
			case wave.stage_2:
				if (!wave.stage_2_set_flag) {
					stage_2.Set_Map(0, 0, 5000, RED);
					/*boss.set(Vec2(RAND(1000, 1500), RAND(1000, 1500)));*/

					for (int i = 0; i < Figure::FigureMax; i++) {
						ellipse[i].set(players, screen, stage_2, wave);
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
						}

						if (quadrangle[i].InScreen(players, quadrangle[i].position, screen) && quadrangle[i].responflag == false) {
							quadrangle[i].Update(players, screen, stage_2, wave);
						}
						
						if (ellipse[i].Player_Ellipse(players) == true) {
							players.SizeDecrease(players);
						}

						if (triangle[i].Player_Triangle(players) == true) {
							players.SizeDecrease(players);
						}
						if (triangle[i].triangle_death && seed[i].UpdateFlag&&seed[i].Player_Seed(players)) {
							players.SizeDecrease(players);
						}
						if (quadrangle[i].Player_Quadrangle(players) == true) {
							players.SizeDecrease(players);
						}
						if (quadrangle[i].UpdatesetFlag) {
							if (quadrangle[i].Player_Update(players)) {
								players.SizeDecrease(players);
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
							}
						}
						if (Drain_Check_Quadrangle(players, quadrangle[i])) {
							if (Drain_Center_Quad(players, quadrangle[i]) == true && quadrangle[i].flag == true && quadrangle[i].responflag == false&& quadrangle[i].UpdatesetFlag==false) {
								Novice::PlayAudio(drain, 0, 0.5);
								players.SizeIncrease(players);
								quadrangle[i].flag = false;
								quadrangle[i].drawflag = false;
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
							if (ellipse[i].cooltime % 120 == 0) {
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

				bar.Update(players,stage_2,wave);
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
					boss_stage.Set_Map(0, 0, 10000, RED);
					wave.boss_set_flag = true;
				}
				//処理書いてね
				/*ボス関係*/
				boss.Keep_Up(players);
				boss.Result(players, screen, RAND(3, 3));
				/*if (Slash_Boss(slash, boss) == true){
					boss.radian-=0.25f;
				}*/
				
				if (beam.isOccur == true){
					if (Beam_Boss(beam, boss) == true) {
						boss.radian -= 0.05f;
					}
				}
				if (boss.radian < 300) {
					boss.shild = 2;
					if (boss.radian < 200) {
						boss.shild = 1;
						if (boss.radian < 100) {
							boss.shild = 0;

						}
					}
				}
				

				///プレイヤーに攻撃が当たった時
				if (boss.Bullet_Player(players) == true) {
					players.radius -= 0.5f;
				}
				if (boss.Bullet_Player_2(players) == true) {
					players.radius -= 0.5f;
				}
				if (boss.Blade_Player(players) == true) {
					players.radius -= 0.5f;

				}
				//ボスのプレイヤーが当たった時
				
				if (boss.shild != 0 && boss.Boss_Player(players) == true&&players.Muteki==false) {  //ボスのシールドがある、俺が無敵じゃない、当たる
					players.Muteki = true;
					players.Reverse *= -1;
					players.radius -= 1;
				}
				else if (players.Muteki == true) {
					players.Muteki_Timer += 0.01f;
					players.Muteki_Timer = Clamp(players.Muteki_Timer,0,1.0f);
					if (players.Muteki_Timer == 1.0f) {
						players.Muteki = false;
						players.Muteki_Timer = 0.0f;
					}

				}
				//クリア条件
				if (boss.shild == 0 && boss.Boss_Player(players) == true) {
					Novice::DrawBox(0, 0, 1000, 1000, 0, GREEN, kFillModeSolid);
				}
				break;
			case wave.rest:
				break;
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
			//Novice::DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0x160036FF, kFillModeSolid);
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
				stage_1.DrawMap(screen);
				for (int i = 0; i < Figure::FigureMax; i++) {
					if (ellipse[i].cheakdraw(players, ellipse[i].position, screen, ellipse[i].flag)) {
						ellipse[i].draw(screen, players);
					}
				}
				Pparticle.DrawParticle(screen);
				players.Draw(screen, players);
			}
			change.Draw(screen);
			break;
		case INGAME:
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
			switch (wave.stage) {
			case wave.stage_1_only:
				if (wave.stage_1_set_flag/* && wave.stage_1_draw_flag*/) {
					stage_1.DrawMap(screen);
					for (int i = 0; i < Figure::FigureMax; i++) {
						if (ellipse[i].cheakdraw(players, ellipse[i].position, screen, ellipse[i].flag)) {
							ellipse[i].draw(screen, players);
						}
					}
					Pparticle.DrawParticle(screen);
					players.Draw(screen, players);

					item.Draw(screen, players);

					bar.beasdraw();
					bar.draw();
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
							if (quadrangle[i].drawflag) {
								quadrangle[i].breaddraw(screen);
							}
							quadrangle[i].draw(screen);
						}
					}
					Pparticle.DrawParticle(screen);
					slash.Draw(screen);
					beam.Draw(screen);
					players.Draw(screen, players);

					item.Draw(screen, players);
					bar.Update(players, stage_2, wave);
					bar.beasdraw();
					bar.draw();
				}
				break;
			case wave.boss_stage:
				Pparticle.DrawParticle(screen);
				slash.Draw(screen);
				beam.Draw(screen);
				if (players.Muteki == false) {
				players.Draw(screen, players);

				}

				item.Draw(screen, players);
				boss.draw(screen);
				if (boss.shild == 0 && boss.Boss_Player(players) == true) {
					Novice::DrawBox(0, 0, 1000, 1000, 0, GREEN, kFillModeSolid);
				}
				break;
			case wave.rest:

				break;
			}
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
