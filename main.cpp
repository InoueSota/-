#include "main.h"

const char kWindowTitle[] = "キューイン";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, SCREEN_WIDTH, SCREEN_HEIGHT);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	//
	int drain = Novice::LoadAudio("./resource./ponyo.wav");
	//
	stage_1.Set_Map(0, 0, 2000, RED);
	//
	boss.set(Vec2(RAND(1000, 1500), RAND(1000, 1500)));


	for (int i = 0; i < Figure::FigureMax; i++) {
		ellipse[i].set(players,screen,stage_1);
		triangle[i].set(players, screen, stage_1);
		quadrangle[i].set(players, screen, stage_1);
		
	}

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
		////セット
		
		/*stage_1.Set_Map(0, 0, 2000,RED);*/
		
		/*　プレイヤー関係の関数（それぞれの意味はPlayer.hに記述）　*/
		//プレイヤー本体
		players.Process(players, preKeys[DIK_SPACE], keys[DIK_SPACE], preKeys[DIK_D], keys[DIK_D]);
		players.SetPlayers(players);
		players.Ripples(screen, players, preKeys[DIK_SPACE], keys[DIK_SPACE]);
		players.SetScrollPos(screen, players, preKeys[DIK_SPACE], keys[DIK_SPACE]);
		players.SetZoom(screen, players);

		//アビリティ
		bubble.Process(players, screen, keys[DIK_SPACE]);

		//パーティクル処理
		Pparticle.ParticleProcess(players, screen);

		/*ボス関係*/
		boss.Keep_Up(players);
		boss.Rand_Move(RAND(3,3));
		boss.Result(players, screen);
		/*　パーティクル処理　*/
		Pparticle.ParticleProcess(players, screen);

		item.Set_Item(RAND(0, 1000), RAND(0, 1000), players,RAND(0,0));

		if (item.Item_collision(players, screen) == true) {
			
			item.Randam_Item();
			
		}

		item.Result(players,screen);

		if (keys[DIK_O]) {
			screen.Zoom -= {0.5f,0.5f};
		}

		//Novice::ScreenPrintf(0, 60, "%f", players.incDeg);

		for (int i = 0; i < Figure::FigureMax; i++) {	
			
			if (ellipse[i].InScreen(players, ellipse[i].position, screen)) {
				ellipse[i].count++;
				if (ellipse[i].count >= ellipse[i].count_state && ellipse[i].count <= ellipse[i].count_end) {
					ellipse[i].Update(players);
				}
			}
			if (triangle[i].InScreen(players, triangle[i].position,screen)) {
				triangle[i].Update(players);
			}

						
			
			if (Drain_Check_Ellipse(players,ellipse[i])) {
				if (Drain_Center_Circle(players, ellipse[i]) == true && ellipse[i].flag == true) {
					Novice::PlayAudio(drain, 0, 0.5);
					players.radius += (ellipse[i].radian / 100);
					players.Length += (ellipse[i].radian / 15);
					ellipse[i].flag = false;
				}
			}
			if (Drain_Check_Triangle(players,triangle[i])) {
				if (Drain_Center_Triangle(players, triangle[i]) == true && triangle[i].flag == true) {
					Novice::PlayAudio(drain, 0, 0.5);
					players.radius += (triangle[i].radian / 100);
					players.Length += (triangle[i].radian / 15);
					triangle[i].flag = false;
				}
			}
			if (Drain_Check_Quadrangle(players, quadrangle[i])) {
				if (Drain_Center_Quad(players, quadrangle[i]) == true && quadrangle[i].flag == true) {
					Novice::PlayAudio(drain, 0, 0.5);
					players.radius += (quadrangle[i].radian / 100);
					players.Length += (quadrangle[i].radian / 15);
					quadrangle[i].flag = false;
				}
			}
			/*if (IsHit_Drain(players.pos.x, players.pos.y, players.radius, ellipse[i], triangle[i], quadrangle[i], screen.Zoom.x) == true && ellipse[i].flag == true) {

				players.radius -= (ellipse[i].radian / 100);
				players.Length -= (ellipse[i].radian / 100);
			}*/

		}
		if (players.radius < 10) {
			players.radius = 10;
		}
		
		stage_1.Map_Collision(players);
		for (int i = 0; i < Figure::FigureMax; i++) {
			
			if (ellipse[i].flag == false) {
				ellipse[i].cooltime++;
				if (ellipse[i].cooltime % 30 == 0) {
					ellipse[i].respon(players, screen, stage_1);
				}
			}
			if (triangle[i].flag == false) {
				triangle[i].cooltime++;
				if (triangle[i].cooltime % 30 == 0) {
					triangle[i].respon(players, screen, stage_1);
				}
			}
			if (quadrangle[i].flag == false) {
				quadrangle[i].cooltime++;
				if (quadrangle[i].cooltime % 30 == 0) {
					quadrangle[i].respon(players, screen, stage_1);
				}
			}
			
		}
		
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		

		if (keys[DIK_Z] != 0) {
			players.radius += 10;
		}

		//背景描画
		Novice::DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0x999999FF, kFillModeSolid);
		stage_1.DrawMap(screen);
		for (int i = 0; i < Figure::FigureMax; i++) {
			if (ellipse[i].cheakdraw(players,ellipse[i].position,screen,ellipse[i].flag)) {
				ellipse[i].draw(screen, players);
			}
			if (triangle[i].cheakdraw(players, triangle[i].position, screen, triangle[i].flag)) {
				triangle[i].draw(screen);
			}
			if (quadrangle[i].cheakdraw(players, quadrangle[i].position, screen, quadrangle[i].flag)) {
				quadrangle[i].draw(screen);
			}

		
		}

		boss.draw(screen);

		Pparticle.DrawParticle(screen);
		bubble.Draw(screen);
		players.Draw(screen,players);

		item.Draw(screen,players);
		
		//players.Draw_Rand_Skin(screen,preKeys[DIK_SPACE],keys[DIK_SPACE]);

		//Novice::ScreenPrintf(0, 20,"zoomed_prad= %f", players.radius*screen.Zoom.x);
		//Novice::ScreenPrintf(0, 0, "%d", boss.count);


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
