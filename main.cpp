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
		triangle[i].set(RAND(-Figure::Area, Figure::Area), RAND(-Figure::Area, Figure::Area), RAND(Figure::RadianMin, Figure::RadianMax));
		quadrangle[i].set(RAND(-Figure::Area, Figure::Area), RAND(-Figure::Area, Figure::Area), RAND(Figure::RadianMin, Figure::RadianMax));
		
	}

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		players.SetPosition(players);

		players.Process(preKeys[DIK_SPACE], keys[DIK_SPACE], preKeys[DIK_D], keys[DIK_D]);

		for (int i = 0; i < Figure::FigureMax; i++) {

			//Drain_Circle(players.pos.x, players.pos.y, players.radius, ellipse[i].position.x, ellipse[i].position.y, ellipse[i].radian);
			//Drain_Circle(players.pos.x, players.pos.y, players.radius, ellipse[i]);

			if (sqrtf((players.pos.x - ellipse[i].position.x) * (players.pos.x - ellipse[i].position.x) + (players.pos.y - ellipse[i].position.y) * (players.pos.y - ellipse[i].position.y)) <= (players.radius + ellipse[i].radian)&&ellipse[i].flag==true) {
				if (players.radius >= ellipse[i].radian) {
					players.radius += (ellipse[i].radian / 10);

					ellipse[i].flag = false;
				}
				
			}
			
		}
		
		//players.radius += 1;
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//背景描画
		Novice::DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, WHITE, kFillModeSolid);
		for (int i = 0; i < Figure::FigureMax; i++) {
			if (0 + SCREEN_WIDTH / 2 + 100 > ellipse[i].position.x && 0 - SCREEN_WIDTH / 2 - 100 < ellipse[i].position.x && 0 + SCREEN_HEIGHT / 2 + 100 > ellipse[i].position.y && 0 - SCREEN_HEIGHT / 2 - 100 < ellipse[i].position.y && ellipse[i].flag == true) {
				ellipse[i].draw(screen);
			}
			if (0 + SCREEN_WIDTH / 2 + 100 > triangle[i].position.x && 0 - SCREEN_WIDTH / 2 - 100 < triangle[i].position.x && 0 + SCREEN_HEIGHT / 2 + 100 > triangle[i].position.y && 0 - SCREEN_HEIGHT / 2 - 100 < triangle[i].position.y && triangle[i].flag == true) {
				triangle[i].draw(screen);
			}
			if (0 + SCREEN_WIDTH / 2 + 100 > quadrangle[i].position.x && 0 - SCREEN_WIDTH / 2 - 100 < quadrangle[i].position.x && 0 + SCREEN_HEIGHT / 2 + 100 > quadrangle[i].position.y && 0 - SCREEN_HEIGHT / 2 - 100 < quadrangle[i].position.y && quadrangle[i].flag == true) {
				quadrangle[i].draw(screen);
			}
		}
		players.Draw(screen);
		/*for (int i = 0; i < 50; i++) {
			ellipse[i].draw(screen);
			triangle[i].draw(screen);
			quadrangle[i].draw(screen);
		}*/
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
