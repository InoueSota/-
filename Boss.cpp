#include "Boss.h"


Boss::Boss()
{
	SRAND();

	Vec2;
	position = { 0,0 };
	flag = false;
	radian = 0;
	rand_num=0;
	shild = 3;
	count=0;
	cooltime=300;
	theta = 0;
	pattern_1=false;
	pattern_2=false;
	pattern_3=false;
	blade = { 0,0,0,0,0,0,0,0 };
	for (int i = 0; i < MAX_BULLET; i++) {

	bullet_pos[i] = { 0,0 };
	bullet_rad[i]=100;
	EaseT_bullet[i]=0;
	bullet_flag[i]=false;
	color[i] = 0xFFFF0000;
	lifetime[i] = 0;

	}
}

void Boss::set(Vec2 pos ) {

	//ポジションなど必要な値を引数を用いて代入するでやんす。
	position = pos;
	radian = 500;

}

void Boss::Rand_Move(int rand)
{
	//ランダムで何をするか今は三分ただけど確率を操るのもあり（運命の指揮者と名付ける）
	if (flag == false&&pattern_1==false&&pattern_2==false&&pattern_3==false) {
		//rand_num = 0;
		rand_num = rand;
		if (rand_num == 1) {
			pattern_1 = true;
			flag = true;
		}
		if (rand_num == 2) {
			pattern_2 = true;
			flag = true;
		}
		if (rand_num == 3) {
			pattern_3 = true;
			flag = true;
		}
	}
	
}

void Boss::Result(Player& player,Screen& screen)
{
	//攻撃パターンの設定
	
	if (InScreen(player, position, screen) == true) {

		if (pattern_1 == true) {
			//ホットプレートの完成

			for (int i = 0; i < MAX_BULLET; i++) {
				if (bullet_flag[i] == false) {
					bullet_pos[i] = position;
					EaseT_bullet[i] = 0;
					//bullet_rad[i] = RAND(200, 250);
					bullet_flag[i] = true;
				}
				if (bullet_flag[i] == true) {
					EaseT_bullet[i] += 0.01f;
					bullet_pos[0].x += Lerp(Easing::easeInOutCirc(EaseT_bullet[0]), 200);
					bullet_pos[1].x -= Lerp(Easing::easeInOutCirc(EaseT_bullet[1]), 200);
					bullet_pos[2].y += Lerp(Easing::easeInOutCirc(EaseT_bullet[2]), 200);
					bullet_pos[3].y -= Lerp(Easing::easeInOutCirc(EaseT_bullet[3]), 200);

					/*bullet_pos[0].x = easing(Easing::easeInOutCirc(EaseT_bullet[0]),position.x, 300);
					bullet_pos[1].x = easing(Easing::easeInOutCirc(EaseT_bullet[1]),position.x, 300);
					bullet_pos[2].y = easing(Easing::easeInOutCirc(EaseT_bullet[2]),position.y, 300);
					bullet_pos[3].y = easing(Easing::easeInOutCirc(EaseT_bullet[3]),position.y, 300);*/

				}

				if (EaseT_bullet[i]>=0.9f) {

					bullet_flag[i] = false;
					pattern_1 = false;
					flag = false;
				}
				
			}
			
			



		}
		if (pattern_2 == true) {
			
			for (int i = 0; i < MAX_BULLET; i++) {
				if (bullet_flag[i] == false) {
					bullet_pos[i].x =position.x+RAND(-1000,1000);
					bullet_pos[i].y= position.y + RAND(-1000, 1000);
					color[i] = 0xFFFF0000;
					lifetime[i] = 0;
					bullet_flag[i] = true;
				}


				if (bullet_flag[i] == true) {
					lifetime[i] += 0.005f;
					color[i]=0x00000000 | static_cast<int>((1.0f - lifetime[i]) * 0x00 + lifetime[i] * 0xFF);
					if (lifetime[i]>=1.0f) {
						//bullet_flag[i] = false;
						flag = false;
						pattern_2 = false;
					}
				}
			}
		}
		if (pattern_3 == true) {
			Novice::ScreenPrintf(0, 120, "blade.ttheaa::%f", blade.theta);
			blade.t += 0.0125f;
			blade.t=Clamp(blade.t,0, 1);
			blade.theta = Lerp(Easing::easeInQuart(blade.t),6);
			blade.theta=Clamp(blade.theta, 0, 360);
			Matrix2x2 mat = MakeRotateMatrix(blade.theta);
			///torbox
			Vector2 top_left = { 0,100 };
			Vector2 top_right = { 750+radian ,100 };
			Vector2 bottom_left = { 0 ,-100 };
			Vector2 bottom_right = { 750+radian ,-100 };

			blade.top_left = Multiply(top_left, mat);
			blade.top_right = Multiply(top_right, mat);
			blade.bottom_left = Multiply(bottom_left, mat);
			blade.bottom_right = Multiply(bottom_right, mat);

			blade.top_left.x += position.x;
			blade.top_left.y += position.y;
			blade.top_right.x += position.x;
			blade.top_right.y += position.y;
			blade.bottom_left.x += position.x;
			blade.bottom_left.y += position.y;
			blade.bottom_right.x += position.x;
			blade.bottom_right.y += position.y;
			
			if (blade.t==1) {
				blade.theta = 0;
				blade.t = 0;
				flag = false;
				pattern_3 = false;
			}

		}

	}
}

void Boss::Keep_Up(Player& player)
{
	//プレイヤーについていく関数使わないかもしれない
	Vec2 vel = (player.center - position).Normalized();
	position += vel;

	///回転させるための処理
	if (theta >= 360) {
		theta = 0;
	}
	theta += 0.05f;

}





void Boss::draw(Screen& screen) {
	
	screen.DrawEllipse(position.x, position.y, radian, radian, 0.0f, BLACK, kFillModeSolid);
	Matrix2x2 mat= MakeRotateMatrix(theta);
	
	//tri
	Vector2 top = { 0,200 };
	Vector2 right = { -200,-100 };
	Vector2 left = { 200,-100};
	///torbox
	Vector2 top_left = { -300,300};
	Vector2 top_right = { 300,300 };
	Vector2 bottom_left = { -300,-300};
	Vector2 bottom_right = { 300,-300 };
	  
	Vector2 rotate_top = Multiply(top,mat);
	Vector2 rotate_right = Multiply(right, mat);
	Vector2 rotate_left = Multiply(left, mat);

	Vector2 rotate_top_left = Multiply(top_left,mat);
	Vector2 rotate_top_right = Multiply(top_right, mat);
	Vector2 rotate_bottom_left = Multiply(bottom_left, mat);
	Vector2 rotate_bottom_right = Multiply(bottom_right, mat);

	rotate_top.x += position.x;
	rotate_top.y += position.y;
	rotate_right.x += position.x;
	rotate_right.y += position.y;
	rotate_left.x += position.x;
	rotate_left.y += position.y;

	rotate_top_left.x += position.x;
	rotate_top_left.y += position.y;
	rotate_top_right.x += position.x;
	rotate_top_right.y += position.y;
	rotate_bottom_right.x += position.x;
	rotate_bottom_right.y += position.y;
	rotate_bottom_left.x += position.x;
	rotate_bottom_left.y += position.y;
	

	if (pattern_1 == true) {
		for (int i = 0; i < MAX_BULLET; i++) {
			if (bullet_flag[i] == true) {
			screen.DrawEllipse(bullet_pos[i].x, bullet_pos[i].y, bullet_rad[i], bullet_rad[i], 0, 0xFFFF00FF,kFillModeSolid);

			}

		}
	}
	if (pattern_2 == true) {
		for (int i = 0; i < MAX_BULLET; i++) {
			if (bullet_flag[i] == true) {
				screen.DrawEllipse(bullet_pos[i].x, bullet_pos[i].y, bullet_rad[i], bullet_rad[i], 0, color[i], kFillModeSolid);

			}

		}
	}
	if (pattern_3 == true) {
		screen.DrawQuad(blade.top_left.x, blade.top_left.y, blade.top_right.x, blade.top_right.y, blade.bottom_left.x, blade.bottom_left.y, blade.bottom_right.x, blade.bottom_right.y, 0, 0, 0, 0, 0, BLACK);

	}

	if (shild >= 1) {
		screen.DrawEllipse(position.x, position.y, radian / 10, radian / 10, 0.0f, RED, kFillModeWireFrame);
		if (shild >= 2) {
			screen.DrawTriangle(rotate_top.x, rotate_top.y, rotate_right.x, rotate_right.y, rotate_left.x, rotate_left.y, GREEN, kFillModeWireFrame);
			if (shild >= 3) {

				screen.DrawLine(rotate_top_left.x, rotate_top_left.y, rotate_top_right.x, rotate_top_right.y, BLUE);
				screen.DrawLine(rotate_top_left.x, rotate_top_left.y, rotate_bottom_left.x, rotate_bottom_left.y, BLUE);
				screen.DrawLine(rotate_top_right.x, rotate_top_right.y, rotate_bottom_right.x, rotate_bottom_right.y, BLUE);
				screen.DrawLine(rotate_bottom_left.x, rotate_bottom_left.y, rotate_bottom_right.x, rotate_bottom_right.y, BLUE);


			}
		}
	}
}


