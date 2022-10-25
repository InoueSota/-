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
	theta_1=0;
	flame_zan = 0;


	pattern_1=false;
	dekaku = false;;

	bakuha = false;
	pattern_2=false;
	pattern_3=false;
	keep = true;
	blade = { 0,0,0,0,0,0,0,0 };
	flame_2 = 0;
	radius_f = 0;
	bakuha=0;
	bakuha_back=0;

	bakuha_T=0;
	bakuha_Tback=0;

	for (int i = 0; i < MAX_BULLET; i++) {

	bullet_pos[i] = { 0,0 };

	bullet_rad[i]=250;
	EaseT_bullet[i]=0;
	Ease_t_rad[i] = 0;
	Ease_t_radback[i] = 0;

	bullet_flag[i] = false;
	color[i] = 0xFFFF0000;
	lifetime[i] = 0;

	}
	for (int i = 0; i < MAX_BULLET_t; i++) {
		bullet_t_pos[i] = { 0,0 };
		bullet_t_flag[i] = false;

	}
}
void Boss::Init()
{

	flag = false;


	pattern_1 = false;
	pattern_2 = false;
	pattern_3 = false;
	flame_2 = 0;
	for (int i = 0; i < MAX_BULLET; i++) {

		bullet_pos[i] = { 0,0 };
		bullet_rad[i] = 250;
		EaseT_bullet[i] = 0;
		Ease_t_rad[i] = 0;
		Ease_t_radback[i] = 0;

		bullet_flag[i] = false;
		color[i] = 0xFFFF0000;
		lifetime[i] = 0;
	}
	for (int i = 0; i < MAX_BULLET_t; i++) {
		bullet_t_pos[i] = { 0,0 };
		bullet_t_flag[i] = false;

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
		Init();
		int time = 0;
		/*rand_num = RAND(0,2);*/
		rand_num = rand;
		cooltime -= 1;
		cooltime = Clamp(cooltime,0,300);

		if (cooltime == 0) {
			if (rand_num == 1) {
				pattern_1 = true;
				flag = true;
				cooltime = time;
			}
			if (rand_num == 2) {
				pattern_2 = true;
				flag = true;
				cooltime = time;

			}
			if (rand_num == 3) {
				pattern_3 = true;
				flag = true;
				cooltime = time;

			}
		}
	}
	
}

void Boss::Result(Player& player,Screen& screen,int rand)
{
	//攻撃パターンの設定
	if (InScreen(player, position, screen) == true) {
		Rand_Move(rand);

	}
	Novice::ScreenPrintf(1000, 0, "rand:%d", rand_num);
	Novice::ScreenPrintf(1000, 20, "cooltime:%d",cooltime);


		if (pattern_1 == true) {
			//ホットプレートの完成
			if (dekaku == false) {
				dekaku_t = Clamp(dekaku_t,0,1.0f);
				if (dekaku_tback == false) {
					dekaku_t += 0.02f;
					dekaku_t = Clamp(dekaku_t, 0, 1.0f);
					radius_f = easing(Easing::easeInBounce(dekaku_t), 0, 200);
				}
					if (dekaku_t == 1.0f||radius_f==200) {
						dekaku_tback = true;
						dekaku_t = 0;
					}
				
				if (dekaku_tback == true) {
					dekaku_t += 0.03f;
					dekaku_t = Clamp(dekaku_t, 0, 1.0f);

					radius_f = easing(Easing::easeInBack(dekaku_t), 200, 0);


				}
			
				if (dekaku_tback == true&&(radius_f==500||dekaku_t==1.0f)) {
					dekaku = true;
				}
			}
			if (dekaku == true) {


				for (int i = 0; i < MAX_BULLET_t; i++) {
					if (bullet_t_flag[i] == false) {
						bullet_t_pos[i] = position;
						EaseT_bullet[i] = 0;
						bullet_t_flag[i] = true;
					}
					if (bullet_t_flag[i] == true && bakuha == false) {
						EaseT_bullet[i] += 0.01f;

						bullet_t_pos[0].x += 10;
						bullet_t_pos[1].x -= 10;
						bullet_t_pos[2].y += 10;
						bullet_t_pos[3].y -= 10;

						//bullet_rad[i] = RAND(200, 250);
						if (EaseT_bullet[i] >= 0.9f) {
							bakuha = true;
						}
					}
					if (bakuha == true && bakuha_back == false) {
						bakuha_T += 0.01f;
						bakuha_T = Clamp(bakuha_T, 0, 1.0f);
						bullet_rad[i] = easing(Easing::easeInBounce(bakuha_T), 250, 600);
						if (bullet_rad[i] == 600) {
							bakuha_back = true;
						}
					}
					if (bakuha_back == true) {
						bakuha_Tback += 0.01f;
						bakuha_Tback = Clamp(bakuha_Tback, 0, 1.0f);
						bullet_rad[i] = easing(Easing::easeOutBounce(bakuha_Tback), 600, 0);


					}
					if (bakuha_Tback == 1.0f) {
						EaseT_bullet[i] = 0;
						bullet_t_pos[i] = position;
						bakuha_T = 0;
						bakuha_Tback = 0;
						theta_1 = 1 / 1.4;
						bullet_t_flag[i] = false;
						pattern_1 = false;
						flag = false;
						bakuha = false;
						bakuha_back = false;
						dekaku = false; 
						dekaku_t = 0.01;
						dekaku_tback = false;
						radius_f = 0;

					}

				}
				if (bakuha_Tback == 1.0f) {
					for (int i = 0; i < MAX_ZAN; i++) {
						zan_flag[i] = false;
						zanpos[i] = {};
					}
				}
			}

			////残像
			flame_zan += 1;
			if (flame_zan == 105) {
				flame_zan = 0;
			}
			for (int i = 0; i < 5; i++) {
				
				if (flame_zan % 10 == 0 && zan_flag[i] == false&&bullet_t_flag[0]==true) {
					zanpos[i] = bullet_t_pos[0];
					zanrad[i] = 200;
					zan_time[i] = 120;
					zan_flag[i] = true;
					break;
				}
				

				if (zan_flag[i] == true) {
					zan_time[i] -= 1;
					zanrad[i] -= 5;
					zanrad[i] = Clamp(zanrad[i], 0, 200);

					if (zanrad[i] == 0) {
						zan_flag[i] = false;
					}
				}


			}
			for (int i = 5; i < 10; i++) {

				if (flame_zan % 10 == 0 && zan_flag[i] == false && bullet_t_flag[1] == true) {
					zanpos[i] = bullet_t_pos[1]/*+Vec2(0, RAND(-5, 5))*/;
					zanrad[i] = 200;
					zan_time[i] = 120;
					zan_flag[i] = true;
					break;
				}


				if (zan_flag[i] == true) {
					zan_time[i] -= 1;
					zanrad[i] -= 5;
					zanrad[i] = Clamp(zanrad[i], 0, 200);

					if (zanrad[i] == 0) {
						zan_flag[i] = false;
					}
				}


			}
			for (int i = 10; i < 15; i++) {

				if (flame_zan % 10 == 0 && zan_flag[i] == false && bullet_t_flag[2] == true) {
					zanpos[i] = bullet_t_pos[2]/*+Vec2(0, RAND(-5, 5))*/;
					zanrad[i] = 200;
					zan_time[i] = 120;
					zan_flag[i] = true;
					break;
				}


				if (zan_flag[i] == true) {
					zan_time[i] -= 1;
					zanrad[i] -= 5;
					zanrad[i] = Clamp(zanrad[i], 0, 200);

					if (zanrad[i] == 0) {
						zan_flag[i] = false;
					}
				}


			}
			for (int i = 15; i < 20; i++) {

				if (flame_zan % 10 == 0 && zan_flag[i] == false && bullet_t_flag[3] == true) {
					zanpos[i] = bullet_t_pos[3]/*+Vec2(0, RAND(-5, 5))*/;
					zanrad[i] = 200;
					zan_time[i] = 120;
					zan_flag[i] = true;
					break;
				}


				if (zan_flag[i] == true) {
					zan_time[i] -= 1;
					zanrad[i] -= 5;
					zanrad[i] = Clamp(zanrad[i], 0, 200);

					if (zanrad[i] == 0) {
						zan_flag[i] = false;
					}
				}


			}
			

		


		}
		if (pattern_2 == true) {
			flame_2 += 1;
			flame_2 = Clamp(flame_2, 0, 30 * MAX_BULLET);
			for (int i = 0; i < MAX_BULLET; i++) {
				if (bullet_flag[i] == false && flame_2 % 30 == 0&&bullet_flag[7]==false) {
					bullet_pos[i].x = player.pos.x + RAND(-1000, 1000);
					bullet_pos[i].y = player.pos.y + RAND(-1000, 1000);
					color[i] = 0x000000FF;
					lifetime[i] = 0;
					Ease_t_radback[i] = 0;
					Ease_t_rad[i] = 0.0f;
					bullet_rad[i] = 250;
					bullet_flag[i] = true;
					break;
				}


				if (bullet_flag[i] == true) {
					lifetime[i] += 0.005f;
					//	color[i]=0x00000000 | static_cast<int>((1.0f - lifetime[i]) * 0x00 + lifetime[i] * 0xFF);
					if (lifetime[i] >= 1.10f) {

						Ease_t_radback[i] += 0.02f;
						bullet_rad[i] = easing(Easing::easeOutCubic(Ease_t_radback[i]), 250, 0);




						if (bullet_rad[i] <= 0) {
							bullet_flag[i] = false;

						}

					}
					else if (lifetime[i] >= 0.8f) {

						Ease_t_rad[i] += 0.05f;
						bullet_rad[i] = easing(Easing::easeOutBack(Ease_t_rad[i]), 0, 250);
						bullet_rad[i] = Clamp(bullet_rad[i], 0, 280);

					}

				}

				

			}
			if (bullet_rad[MAX_BULLET - 1] <= 0) {
				

				flag = false;
				pattern_2 = false;
				flame_2 = 0;
			}
			
		}
	
		if (pattern_3 == true) {
			Novice::ScreenPrintf(0, 120, "blade.ttheaa::%f", blade.theta);

			float a = position.x - player.center.x;
			float b = position.y - player.center.y;
			float c = sqrtf(a * a + b * b);

			if (keep == true) {
				//プレイヤーについていく関数使わないかもしれない
				Vec2 vel = (player.center - position).Normalized();
				position += (vel*20);

			}
			if (c <= player.Length+radian ) {
				keep = false;
			}
			if (keep == false) {
				blade.t += 0.0125f;
				blade.t = Clamp(blade.t, 0, 1);
				blade.theta = Lerp(Easing::easeInQuart(blade.t), 6);
				blade.theta = Clamp(blade.theta, 0, 360);
				Matrix2x2 mat = MakeRotateMatrix(blade.theta);
				///torbox
				Vector2 top_left = { 0,100 };
				Vector2 top_right = { 450 + radian ,100 };
				Vector2 bottom_left = { 0 ,-100 };
				Vector2 bottom_right = { 750 + radian ,-100 };

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

				if (blade.t == 1) {
					blade.theta = 0;
					blade.t = 0;
					flag = false;
					keep = true;
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
		for (int i = 0; i < MAX_BULLET_t; i++) {
			if (bullet_t_flag[i] == true) {
				if (dekaku == true) {
				screen.DrawEllipse(bullet_t_pos[i].x, bullet_t_pos[i].y, bullet_rad[i]+RAND(-50,50), bullet_rad[i] + RAND(-50, 50), 0, 0xFFFF00FF, kFillModeSolid);

				}

			}

		}
		////残像
		for (int i = 0; i < MAX_ZAN; i++) {
			if ( bakuha == false) {
				if (zan_flag[i] == true && bakuha_back == false) {
					if (dekaku == true) {
						screen.DrawEllipse(zanpos[i].x, zanpos[i].y, zanrad[i], zanrad[i], 0, 0xFFFF00aa, kFillModeSolid);
					}
				}
			}
		}
	}
	if (pattern_2 == true) {
		for (int i = 0; i < MAX_BULLET; i++) {
			if (bullet_flag[i] == true) {

				if (lifetime[i] <= 0.8f) {
					screen.DrawEllipse(bullet_pos[i].x, bullet_pos[i].y, bullet_rad[i], bullet_rad[i], 0, color[i], kFillModeWireFrame);

				}
				if (lifetime[i] >= 0.8f) {
					screen.DrawEllipse(bullet_pos[i].x, bullet_pos[i].y, bullet_rad[i], bullet_rad[i], 0, color[i], kFillModeSolid);

				}

			}

		}
	}
	if (pattern_3 == true) {
		if (keep == true) {
			screen.DrawEllipse(position.x, position.y, 950, 950, 0, 0xFF000088, kFillModeSolid);
		}
		if (keep == false) {
			screen.DrawQuad(blade.top_left.x, blade.top_left.y, blade.top_right.x, blade.top_right.y, blade.bottom_left.x, blade.bottom_left.y, blade.bottom_right.x, blade.bottom_right.y, 0, 0, 0, 0, 0, BLACK);

		}

	}
	screen.DrawEllipse(position.x, position.y, radian+radius_f, radian+radius_f, 0.0f, BLACK, kFillModeSolid);

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


