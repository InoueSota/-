#include "main.h"

const char kWindowTitle[] = "キューイン";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, SCREEN_WIDTH, SCREEN_HEIGHT);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

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

			Drain_Circle(players.pos.x, players.pos.y, players.radius, ellipse[i].position.x, ellipse[i].position.y, ellipse[i].radian);
			
			/*Drain(players.radius, ellipse[i].radian.x);*/
		}
		Novice::ScreenPrintf(0, 20, "%f", players.pos.x);
		Novice::ScreenPrintf(0, 40, "%f", players.pos.y);


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//背景描画
		Novice::DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, GREEN, kFillModeSolid);

		players.Draw(screen);
		for (int i = 0; i < 50; i++) {
			ellipse[i].draw(screen);
			triangle[i].draw(screen);
			quadrangle[i].draw(screen);
		}
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
