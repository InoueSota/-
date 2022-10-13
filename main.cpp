#include "main.h"

const char kWindowTitle[] = "キューイン";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, SCREEN_WIDTH, SCREEN_HEIGHT);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	

	for (int i = 0; i < Figure::FigureMax; i++) {
		ellipse[i].set(players);
		triangle[i].set(players);
		quadrangle[i].set(players);
		
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
		stage_1.Set_Map(0, 0, 10000,RED);
		players.SetPlayers(players);

		players.Process(players, preKeys[DIK_SPACE], keys[DIK_SPACE], preKeys[DIK_D], keys[DIK_D]);

		players.SetScrollPos(screen, players, preKeys[DIK_SPACE], keys[DIK_SPACE]);

		players.SetZoom(screen, players);

		for (int i = 0; i < Figure::FigureMax; i++) {		

			if (Drain_Circle(players.pos.x, players.pos.y, players.radius*screen.Zoom.x, ellipse[i])==true && ellipse[i].flag == true) {

				players.radius += (ellipse[i].radian / 25);
				players.Length += (ellipse[i].radian / 5);
				ellipse[i].flag = false;
				
			}
						
			else if (Drain_Triangle(players.pos.x, players.pos.y, players.radius, triangle[i]) == true && triangle[i].flag == true) {
				players.radius += (triangle[i].radian / 25);
				players.Length += (triangle[i].radian / 5);
				triangle[i].flag = false;
			}
			
			else if (Drain_Quadrangl(players.pos.x, players.pos.y, players.radius, quadrangle[i]) == true && quadrangle[i].flag == true) {
				players.radius += (quadrangle[i].radian / 25);
				players.Length += (quadrangle[i].radian / 5);
				quadrangle[i].flag = false;
			}

			
			
			else if (Drain_Center_Circle(players, ellipse[i]) == true && ellipse[i].flag == true) {

				players.radius += (ellipse[i].radian / 100);
				players.Length += (ellipse[i].radian / 25);
				ellipse[i].flag = false;
			}

			else if (Drain_Center_Triangle(players, triangle[i]) == true && triangle[i].flag == true) {

				players.radius += (triangle[i].radian / 100);
				players.Length += (triangle[i].radian / 25);
				triangle[i].flag = false;
			}

			else if (Drain_Center_Quad(players, quadrangle[i]) == true && quadrangle[i].flag == true) {

				players.radius += (quadrangle[i].radian / 100);
				players.Length += (quadrangle[i].radian / 25);
				quadrangle[i].flag = false;
			}
			else if (IsHit_Drain(players.pos.x, players.pos.y, players.radius, ellipse[i], triangle[i], quadrangle[i]) == true && ellipse[i].flag == true) {

				players.radius -= (ellipse[i].radian / 100);
				players.Length -= (ellipse[i].radian / 100);
			}

		}
		if (players.radius < 10) {
			players.radius = 10;
		}
		
		stage_1.Map_Collision(players);
		for (int i = 0; i < Figure::FigureMax; i++) {
			ellipse[i].cooltime++;
			triangle[i].cooltime++;
			quadrangle[i].cooltime++;

			if (ellipse[i].cooltime % 20 == 0 && ellipse[i].flag==false) {
					ellipse[i].respon(players, screen);
			}
			if (triangle[i].cooltime % 20 == 0 && triangle[i].flag == false) {
				triangle[i].respon(players, screen);
			}
			if (quadrangle[i].cooltime % 20 == 0 && quadrangle[i].flag == false) {
				quadrangle[i].respon(players, screen);
			}
		}
		
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		

		if (preKeys[DIK_Z] == 0 && keys[DIK_Z] != 0) {
			screen.Zoom.x = 0.7f;
			screen.Zoom.y = 0.7f;
		}

		//背景描画
		Novice::DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0xABFFBAFF, kFillModeSolid);
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
		players.Draw(screen,players);
		Novice::ScreenPrintf(0, 20,"zoomed_prad= %f", players.radius*screen.Zoom.x);
		Novice::ScreenPrintf(0, 0, "prad= %f", players.radius);


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
