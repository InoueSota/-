#include "main.h"

const char kWindowTitle[] = "キューイン";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, SCREEN_WIDTH, SCREEN_HEIGHT);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	SRAND();

	for (int i = 0; i < Figure::FigureMax; i++) {
		ellipse[i].set(RAND(-Figure::Area, Figure::Area), RAND(-Figure::Area, Figure::Area), RAND(Figure::RadianMin, Figure::RadianMax));
		//triangle[i].set(RAND(-Figure::Area, Figure::Area), RAND(-Figure::Area, Figure::Area), RAND(Figure::RadianMin, Figure::RadianMax),Degree(RAND(0,360)));
		//quadrangle[i].set(RAND(-Figure::Area, Figure::Area), RAND(-Figure::Area, Figure::Area), RAND(Figure::RadianMin, Figure::RadianMax), Degree(RAND(0, 360)));
		
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

		players.SetPlayers(players);

		players.Process(players, preKeys[DIK_SPACE], keys[DIK_SPACE], preKeys[DIK_D], keys[DIK_D]);

		players.SetScrollPos(screen, players, preKeys[DIK_SPACE], keys[DIK_SPACE]);

		for (int i = 0; i < Figure::FigureMax; i++) {		

			/*if (Drain_Circle(players.pos.x, players.pos.y, players.radius, ellipse[i])==true && ellipse[i].flag == true) {

				players.radius += (ellipse[i].radian / 25);
				players.Length += (ellipse[i].radian / 5);
				ellipse[i].flag = false;
				
			}*/
			/*else
			if (Drain_Circle(players.pos.x, players.pos.y, players.radius, ellipse[i])==false && ellipse[i].flag == true) {

				players.radius -= (ellipse[i].radian / 100);
				
			}*/
						
			/*if (Drain_Triangle(players.pos.x, players.pos.y, players.radius, triangle[i]) == true && triangle[i].flag == true) {
				players.radius += (triangle[i].radian / 25);
				players.Length += (triangle[i].radian / 5);
				triangle[i].flag = false;
			}*/
			
			/*if (Drain_Quadrangl(players.pos.x, players.pos.y, players.radius, quadrangle[i]) == true && quadrangle[i].flag == true) {
				players.radius += (quadrangle[i].radian / 25);
				players.Length += (quadrangle[i].radian / 5);
				quadrangle[i].flag = false;
			}*/

			//if (Drain_Line_Center_Triangle(players.pos.x, players.pos.y, players.center.x, players.center.y, triangle[i]) == true && triangle[i].flag == true) {
			//	players.radius += (triangle[i].radian / 25);
			//	players.Length += (triangle[i].radian / 5);
			//	//triangle[i].flag = false;
			//}

			if (Drain_Line_Center_Circle(players.pos.x, players.pos.y, players.center.x, players.center.y, ellipse[i]) == true && ellipse[i].flag == true) {
				players.radius += (ellipse[i].radian / 25);
				players.Length += (ellipse[i].radian / 5);
				//ellipse[i].flag = false;
			}
			


		}
		if (players.radius < 10) {
			players.radius = 10;
		}
		

		
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		Novice::ScreenPrintf(players.pos.x, players.pos.y, "player1");
		Novice::ScreenPrintf(players.center.x, players.center.y, "player2");

		//背景描画
		Novice::DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, BLUE, kFillModeSolid);
		for (int i = 0; i < Figure::FigureMax; i++) {
			if (ellipse[i].cheakdraw(screen,ellipse[i].position,ellipse[i].flag)) {
				ellipse[i].draw(screen);
			}
			if (triangle[i].cheakdraw(screen, triangle[i].position,triangle[i].flag)) {
				triangle[i].draw(screen);
			}
			if (quadrangle[i].cheakdraw(screen, quadrangle[i].position, quadrangle[i].flag)) {
				quadrangle[i].draw(screen);
			}
		}
		players.Draw(screen);

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
