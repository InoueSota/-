#include "Boss.h"


Boss::Boss()
{
	damepar = true;

	Boss_color = 0x000000FF;
	hit = false;;

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
	pattern_4 = false;

	keep = true;
	blade = { 0,0,0,0,0,0,0,0 };
	flame_2 = 0;
	radius_f = 0;
	bakuha=0;
	bakuha_back=0;

	bakuha_T=0;
	bakuha_Tback=0;

	dekaku_t = 0;
	dekaku_tback = 0;

	for (int i = 0; i < MAX_BULLET; i++) {

	bullet_pos[i] = { 0,0 };

	bullet_rad[i]=250;
	EaseT_bullet[i]=0;
	Ease_t_rad[i] = 0;
	Ease_t_radback[i] = 0;

	bullet_flag[i] = false;
	color[i] = 0xFFFF0000;
	lifetime[i] = 0;
	tyakkaman[i] = false;

	}
	for (int i = 0; i < MAX_BULLET_t; i++) {
		bullet_t_pos[i] = { 0,0 };
		bullet_t_flag[i] = false;
		dasita [i] = false;
	}
	for (int i = 0; i < MAX_ZAN; i++) {
		zan_flag[i] = false;
		zan_time[i] = false;
		zanrad[i] = 0;
	}
	for (int i = 0; i < MAX_DAME; i++) {
		dame.pos[i]={};
		dame.vel[i]={};
		dame.rad[i]={};
		dame.EaseT[i]=0;
		dame.lifetime[i]=0;
		dame.flag[i]=0;
		dame.color[i]=0;
	}
}
void Boss::Init()
{

	flag = false;
	bakuha_T=0;
	bakuha_Tback=0;
	radius_f=0;
	dekaku=0;
	dekaku_t=0;
	dekaku_tback=0;
	pattern_1 = false;
	pattern_2 = false;
	pattern_3 = false;
	pattern_4 = false;
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
		tyakkaman[i];

	}
	for (int i = 0; i < MAX_BULLET_t; i++) {
		bullet_t_pos[i] = { 0,0 };
		bullet_t_flag[i] = false;
		dasita[i] = false;


	}
}
void Boss::bossgekiha()
{
	
	boss_c_t += 0.01f;
	boss_c_t =Clamp(boss_c_t,0,1);

	Boss_color = easing(boss_c_t, 0x000000FF, 0xE80971FF);
	if (boss_c_t ==1) {
		//Boss_color = 0xE80971FF;//最終的にピンクになる	
		boss_c_t = 0;//ずっとカラフル
	}
}
void Boss::Dame_Par()
{
	if (damepar == true) {
		for (int i = 0; i < MAX_DAME; i++) {
			if (dame.flag[i] == false) {

				dame.pos[i] = position;
				dame.rad[i] = radian / 10;
				dame.lifetime[i] = 1.0f;
				dame.vel[i] = Vec2(RAND(-30.0f, 30), RAND(-30, 30));
				dame.EaseT[i] = 0;
				dame.color[i] = 0x000000FF;
				dame.flag[i] = true;
				/*break;*/
			}


			if (dame.flag[i] == true) {
				dame.pos[i] += dame.vel[i];
				dame.lifetime[i] -= 0.01f;
				dame.lifetime[i] = Clamp(dame.lifetime[i], 0, 1.0f);
				dame.color[i]= 0x00000000 | static_cast<int>((1.0f - dame.lifetime[i]) * 0x00 + dame.lifetime[i] * 0xFF);
				if (dame.lifetime[i] == 0) {
					dame.flag[i] = false;
					damepar = false;
				}
			}
		}
	}
}
void Boss::Rune_Par()
{
	rune.Time += 1;
	if (rune.Time == 300) {
		rune.Time =0;
	}
	for (int i = 0; i < MAX_RUNE; i++) {
		if (rune.Time%6==0&&rune.flag[i] == false) {

			rune.pos[i] = position + Vec2(RAND(-(radian / 2), (radian / 2)), RAND(-(radian / 2), (radian / 2)));
			rune.rad[i] = radian / 4;
			rune.lifetime[i] = RAND(0.5f,2.0f);
			rune.vel[i] = Vec2(RAND(-3.0f, 3), RAND(0, 30));
			rune.EaseT[i] = 0;
			rune.color[i] = 0xE80971FF;
				
			rune.flag[i] = true;
			break;
		}


		if (rune.flag[i] == true) {
			rune.pos[i] += rune.vel[i];
			rune.lifetime[i] -= 0.01f;
			rune.lifetime[i] = Clamp(rune.lifetime[i], 0, 3.0f);
			rune.color[i] = 0xE8097100 | static_cast<int>((1.0f - rune.lifetime[i]) * 0x00 + rune.lifetime[i] * 0xFF);
			if (rune.lifetime[i] == 0) {
				rune.flag[i] = false;
				
			}
		}
	}

}
bool Boss::Bullet_Player(Player& player)
{
	Vec2 start_to_center[MAX_BULLET];
	Vec2 start_to_end;
	Vec2 nomalize_stc[MAX_BULLET];
	float t[MAX_BULLET]={};
	Vec2 f[MAX_BULLET];
	float distance[MAX_BULLET]={};
	//center::回っていない
	//pos::回っている
	for (int i = 0; i < MAX_BULLET; i++) {

		 start_to_center[i] = Vec2(bullet_pos[i] - player.center);
		 start_to_end = Vec2(player.pos - player.center);
		 nomalize_stc[i] = start_to_center[i].Normalized();

		/*float dot01 = start_to_center.x * start_to_end.x + start_to_center.y * start_to_end.y;*/

		t[i] = ((start_to_center[i].Dot(nomalize_stc[i])) / start_to_end.Length());
		t[i] = Clamp(t[i], 0, 1);

		f[i] = (1.0f - t[i]) * player.center + t[i] * player.pos;

		distance[i] = (bullet_pos[i] - f[i]).Length();
		

		
	}
	

	if (distance[0] < player.radius + bullet_rad[0]) {
		if (tyakkaman[0] == true&&bullet_flag[0]==true) {
			return true;
		}
	}if (distance[1] < player.radius + bullet_rad[1]) {
		if (tyakkaman[1] == true && bullet_flag[1] == true) {
			return true;
		}
	}if (distance[2] < player.radius + bullet_rad[2]) {
		if (tyakkaman[2] == true && bullet_flag[2] == true) {
			return true;
		}
	}if (distance[3] < player.radius + bullet_rad[3]) {
		if (tyakkaman[3] == true && bullet_flag[3] == true) {
			return true;
		}
	}if (distance[4] < player.radius + bullet_rad[4]) {
		if (tyakkaman[4] == true && bullet_flag[4] == true) {
			return true;
		}
	}if (distance[5] < player.radius + bullet_rad[5]) {
		if (tyakkaman[5] == true && bullet_flag[5] == true) {
			return true;
		}
	}if (distance[6] < player.radius + bullet_rad[6]) {
		if (tyakkaman[6] == true && bullet_flag[6] == true) {
			return true;
		}
	}if(distance[7] < player.radius + bullet_rad[7]) {
		if (tyakkaman[7] == true && bullet_flag[7] == true) {
			return true;
		}
	}
	
	return false;
}
bool Boss::Bullet_Player_2(Player& player)
{

	Vec2 start_to_center[MAX_BULLET_t];
	Vec2 start_to_end;
	Vec2 nomalize_stc[MAX_BULLET_t];
	float t[MAX_BULLET_t] = {};
	Vec2 f[MAX_BULLET_t];
	float distance[MAX_BULLET_t] = {};
	//center::回っていない
	//pos::回っている
	for (int i = 0; i < MAX_BULLET_t; i++) {

		start_to_center[i] = Vec2(bullet_t_pos[i] - player.center);
		start_to_end = Vec2(player.pos - player.center);
		nomalize_stc[i] = start_to_center[i].Normalized();

		/*float dot01 = start_to_center.x * start_to_end.x + start_to_center.y * start_to_end.y;*/

		t[i] = ((start_to_center[i].Dot(nomalize_stc[i])) / start_to_end.Length());
		t[i] = Clamp(t[i], 0, 1);

		f[i] = (1.0f - t[i]) * player.center + t[i] * player.pos;

		distance[i] = (bullet_t_pos[i] - f[i]).Length();

	}
	if (distance[0] < player.radius + bullet_rad[0]) {
		if (bullet_t_flag[0] == true) {
			bullet_t_flag[0] = false;
			return true;

		}
	}
	if (distance[1] < player.radius + bullet_rad[1]) {
		if (bullet_t_flag[1] == true) {
			bullet_t_flag[1] = false;
			return true;
		}
	}
	if (distance[2] < player.radius + bullet_rad[2]) {
		if (bullet_t_flag[2] == true) {
			bullet_t_flag[2] = false;
			return true;
		}
	}
	if (distance[3] < player.radius + bullet_rad[3]) {
		if (bullet_t_flag[3] == true) {
			bullet_t_flag[3] = false;
			return true;
		}
	}
}
bool Boss::Blade_Player(Player& player)
{

	Vec2 start_to_center;
	Vec2 start_to_end;
	Vec2 nomalize_stc;
	Vec2 blade_top = { blade.bottom_left.x,blade.bottom_left.y };
	Vec2 blade_bottom = { blade.bottom_right.x,blade.bottom_right.y };

	float t= {};
	Vec2 f;
	float distance = {};
	//center::回っていない
	//pos::回っている
	

		start_to_center = Vec2(player.center -blade_top );
		start_to_end = Vec2(blade_top - blade_bottom);
		nomalize_stc = start_to_center.Normalized();

		/*float dot01 = start_to_center.x * start_to_end.x + start_to_center.y * start_to_end.y;*/

		t = ((start_to_center.Dot(nomalize_stc)) / start_to_end.Length());
		t = Clamp(t, 0, 1);

		f = (1.0f - t) * player.center + t * player.pos;

		distance = (player.center - f).Length();

	
	if (distance < player.radius +50) {
		if (pattern_3 == true) {
			
			return true;

		}
	}
	return false;
}
bool Boss::Blade_Player_2(Player& player)
{

	Vec2 start_to_center;
	Vec2 start_to_end;
	Vec2 nomalize_stc;
	Vec2 blade_top = { blade.bottom_left.x,blade.bottom_left.y };
	Vec2 blade_bottom = { blade.bottom_right.x,blade.bottom_right.y };

	float t = {};
	Vec2 f;
	float distance = {};
	//center::回っていない
	//pos::回っている


	start_to_center = Vec2(player.pos - blade_top);
	start_to_end = Vec2(blade_top - blade_bottom);
	nomalize_stc = start_to_center.Normalized();

	/*float dot01 = start_to_center.x * start_to_end.x + start_to_center.y * start_to_end.y;*/

	t = ((start_to_center.Dot(nomalize_stc)) / start_to_end.Length());
	t = Clamp(t, 0, 1);

	f = (1.0f - t) * player.center + t * player.pos;

	distance = (player.center - f).Length();


	if (distance < player.radius + 50) {
		if (pattern_3 == true) {

			return true;

		}
	}
	return false;
}
bool Boss::Boss_Player(Player& player)
{

	//center::回っていない
	//pos::回っている

	Vec2 start_to_center = Vec2(position - player.center);
	Vec2 start_to_end = Vec2(player.pos - player.center);
	Vec2 nomalize_stc = start_to_center.Normalized();

	/*float dot01 = start_to_center.x * start_to_end.x + start_to_center.y * start_to_end.y;*/

	float t = ((start_to_center.Dot(nomalize_stc)) / start_to_end.Length());
	t = Clamp(t, 0, 1);

	Vec2 f = (1.0f - t) * player.center + t * player.pos;

	float distance = (position - f).Length();

	if (distance < player.radius / 50 + radian) {
		return true;
	}
	
	return false;
}
void Boss::set(Vec2 pos ) {

	//ポジションなど必要な値を引数を用いて代入するでやんす。
	position = pos;
	radian = 1500;
	shild = 3;
	Boss_color = BLACK;

}
void Boss::t_set(Vec2 pos) {

	//ポジションなど必要な値を引数を用いて代入するでやんす。
	position = pos;
	radian = 750;
	shild = 1;
	Boss_color = BLACK;


}

void Boss::Rand_Move(int rand)
{
	
	//ランダムで何をするか今は三分ただけど確率を操るのもあり（運命の指揮者と名付ける）
	if (flag == false&&pattern_1==false&&pattern_2==false&&pattern_3==false && pattern_4 == false) {
		//rand_num = 0;
		Init();
		int time = 100;
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
			if (rand_num == 4) {
				pattern_4 = true;
				flag = true;
				cooltime = time;

			}
		}
	}
	
}

void Boss::Result(Player& player,Screen& screen,int rand, Sound& sound)
{
	//攻撃パターンの設定
	/*if (InScreen(player, position, screen) == true) {*/
		Rand_Move(rand);


	///*}*/
	//Novice::ScreenPrintf(1000, 0, "rand:%d", rand_num);
	////Novice::ScreenPrintf(1000, 20, "cooltime:%d",cooltime);
	//Novice::ScreenPrintf(1000, 20, "dekaku_tback:%d", dekaku_tback);



		if (pattern_1 == true) {
			//ホットプレートの完成
			if (dekaku == false) {
				
				if (dekaku_tback == false) {
					dekaku_t += 0.02f;
					dekaku_t = Clamp(dekaku_t, 0, 1.0f);
					radius_f = easing(Easing::easeInBounce(dekaku_t), 0, 200);
				}
				if (dekaku_t == 1.0f || radius_f == 200) {
					dekaku_tback = true;
					dekaku_t = 0;
				}

				if (dekaku_tback == true) {
					dekaku_t2 += 0.03f;
					dekaku_t2 = Clamp(dekaku_t2, 0, 1.0f);
					radius_f = easing(Easing::easeInBack(dekaku_t2), 200, 0);
				}

				if (dekaku_tback == true && (radius_f == 500 || dekaku_t2 == 1.0f)) {
					dasita[0] = false;
					dasita[1] = false;
					dasita[2] = false;
					dasita[3] = false;
					dekaku = true;
				}
			}

			if (dekaku == true) {
				

				for (int i = 0; i < MAX_BULLET_t; i++) {
					if (bullet_t_flag[i] == false&&dasita[i] == false) {
						bullet_t_pos[i] = position;
						bullet_rad[i] = radian / 2;
						EaseT_bullet[i] = 0;
						bullet_t_flag[i] = true;
						dasita[i] = true;
					}
					if (bullet_t_flag[i] == true && bakuha == false) {
						/*dasita[i] = true;*/
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
						dekaku_t2 = 0.01;

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
				if (bullet_flag[i] == false && flame_2 % 30 == 0&&bullet_flag[MAX_BULLET-1]==false) {
					bullet_pos[i].x = player.pos.x + RAND(-1000, 1000);
					bullet_pos[i].y = player.pos.y + RAND(-1000, 1000);
					tyakkaman[i] = false;
					color[i] = 0xFFFFFFFF;
					lifetime[i] = 0;
					Ease_t_radback[i] = 0;
					Ease_t_rad[i] = 0.0f;
					bullet_rad[i] = radian/1.5f;
					bullet_rad_f = radian / 1.5f;
					bullet_flag[i] = true;
					break;
				}


				if (bullet_flag[i] == true) {
					lifetime[i] += 0.005f;
					//	color[i]=0x00000000 | static_cast<int>((1.0f - lifetime[i]) * 0x00 + lifetime[i] * 0xFF);
					if (lifetime[i] >= 1.10f&&Ease_t_rad[i]==1) {

						Ease_t_radback[i] += 0.02f;
						bullet_rad[i] = easing(Easing::easeOutCubic(Ease_t_radback[i]), bullet_rad_f, 0);

						if (bullet_rad[i] <= 0) {
							bullet_flag[i] = false;

						}

					}
					else if (lifetime[i] >= 0.8f) {
						tyakkaman[i] = true;
						Ease_t_rad[i] += 0.05f;
						Ease_t_rad[i] = Clamp(Ease_t_rad[i],0,1);

						bullet_rad[i] = easing(Easing::easeOutBack(Ease_t_rad[i]), 0, bullet_rad_f);
						bullet_rad[i] = Clamp(bullet_rad[i], 0, bullet_rad_f+200);

					}

				}

				

			}
			if (bullet_rad[MAX_BULLET - 1] <= 0) {
				
				///*tyakkaman[i] = false;*/
				flag = false;
				pattern_2 = false;
				flame_2 = 0;
			}
			
		}
	
		if (pattern_3 == true) {
			//Novice::ScreenPrintf(0, 120, "blade.ttheaa::%f", blade.theta);

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
				Vector2 top_left = { 0,100 + (radian / 4) };
				Vector2 top_right = { 2*radian ,100+(radian/4) };
				Vector2 bottom_left = { 0 ,-100 - (radian / 4) };
				Vector2 bottom_right = {  (2*radian)+250 ,-100- (radian / 4) };

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
		if (pattern_4 == true) {
			//ホットプレートの完成
			if (dekaku == false) {
				dekaku_t = Clamp(dekaku_t, 0, 1.0f);
				if (dekaku_tback == false) {
					dekaku_t += 0.02f;
					dekaku_t = Clamp(dekaku_t, 0, 1.0f);
					radius_f = easing(Easing::easeInBounce(dekaku_t), 0, 200);
				}
				if (dekaku_t == 1.0f || radius_f == 200) {
					dekaku_tback = true;
					dekaku_t = 0;
				}

				if (dekaku_tback == true) {
					dekaku_t += 0.03f;
					dekaku_t = Clamp(dekaku_t, 0, 1.0f);

					radius_f = easing(Easing::easeInBack(dekaku_t), 200, 0);


				}

				if (dekaku_tback == true && (radius_f == 500 || dekaku_t == 1.0f)) {
					dasita[0] = false;
					dasita[1] = false;
					dasita[2] = false;
					dasita[3] = false;


					dekaku = true;
				}
			}
			if (dekaku == true) {


				for (int i = 0; i < MAX_BULLET_t; i++) {
					if (bullet_t_flag[i] == false && dasita[i] == false) {
						bullet_t_pos[i] = position;
						EaseT_bullet[i] = 0;
						bullet_t_flag[i] = true;
						dasita[i] = true;
					}
					if (bullet_t_flag[i] == true && bakuha == false) {
						/*dasita[i] = true;*/
						EaseT_bullet[i] += 0.01f;

						bullet_t_pos[0].x += 10 / sqrtf(2);
						bullet_t_pos[0].y += 10 / sqrtf(2);
						bullet_t_pos[1].x -= 10 / sqrtf(2);
						bullet_t_pos[1].y -= 10 / sqrtf(2);
						bullet_t_pos[2].x += 10 / sqrtf(2);
						bullet_t_pos[2].y -= 10 / sqrtf(2);
						bullet_t_pos[3].x -= 10 / sqrtf(2);
						bullet_t_pos[3].y += 10 / sqrtf(2);

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

				if (flame_zan % 10 == 0 && zan_flag[i] == false && bullet_t_flag[0] == true) {
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
void Boss::t_draw(Screen& screen) {

	if (shild != 0) {
		if (pattern_1 == true) {
			for (int i = 0; i < MAX_BULLET_t; i++) {
				if (bullet_t_flag[i] == true) {
					if (dekaku == true) {
						screen.DrawEllipse(bullet_t_pos[i].x, bullet_t_pos[i].y, bullet_rad[i] + RAND(-50, 50), bullet_rad[i] + RAND(-50, 50), 0, 0xFFFF00FF, kFillModeSolid);

					}

				}

			}
			////残像
			for (int i = 0; i < MAX_ZAN; i++) {
				if (bakuha == false) {
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
	}
	for (int i = 0; i < MAX_DAME; i++) {
		if (dame.flag[i] == true) {
		screen.DrawEllipse(dame.pos[i].x, dame.pos[i].y, dame.rad[i], dame.rad[i], 0, dame.color[i], kFillModeSolid);

		}
	}
	
	screen.DrawEllipse(position.x, position.y, radian + radius_f, radian + radius_f, 0.0f, Boss_color, kFillModeSolid);
	for (int i = 0; i < MAX_RUNE; i++) {
		if (rune.flag[i] == true) {
			screen.DrawEllipse(rune.pos[i].x, rune.pos[i].y, rune.rad[i], rune.rad[i], 0, rune.color[i], kFillModeSolid);

		}
	}
	if (hit == true) {
		screen.DrawEllipse(position.x, position.y, radian + radius_f, radian + radius_f, 0.0f, 0xFFFFFF33, kFillModeSolid);

	}

	if (shild >= 1) {
		screen.DrawEllipse(position.x, position.y, 300, 300, 0.0f, RED, kFillModeWireFrame);
	}
}
void Boss::draw(Screen& screen) {
	
		Matrix2x2 mat = MakeRotateMatrix(theta);

		//tri
		Vector2 top = { 0,300 * 2 };
		Vector2 right = { -300 * 2,-150 * 2 };
		Vector2 left = { 300 * 2,-150 * 2 };
		///torbox
		Vector2 top_left = { -300 * 2,300 * 2 };
		Vector2 top_right = { 300 * 2,300 * 2 };
		Vector2 bottom_left = { -300 * 2,-300 * 2 };
		Vector2 bottom_right = { 300 * 2,-300 * 2 };

		Vector2 rotate_top = Multiply(top, mat);
		Vector2 rotate_right = Multiply(right, mat);
		Vector2 rotate_left = Multiply(left, mat);

		Vector2 rotate_top_left = Multiply(top_left, mat);
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
		if (shild != 0) {

			if (pattern_1 == true) {
				for (int i = 0; i < MAX_BULLET_t; i++) {
					if (bullet_t_flag[i] == true) {
						if (dekaku == true) {
							screen.DrawEllipse(bullet_t_pos[i].x, bullet_t_pos[i].y, bullet_rad[i] + RAND(-50, 50), bullet_rad[i] + RAND(-50, 50), 0, 0xFFFF00FF, kFillModeSolid);

						}

					}

				}
				////残像
				for (int i = 0; i < MAX_ZAN; i++) {
					if (bakuha == false) {
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
					screen.DrawEllipse(position.x, position.y, radian * 2, radian * 2, 0, 0xFF000088, kFillModeSolid);
				}
				if (keep == false) {
					screen.DrawQuad(blade.top_left.x, blade.top_left.y, blade.top_right.x, blade.top_right.y, blade.bottom_left.x, blade.bottom_left.y, blade.bottom_right.x, blade.bottom_right.y, 0, 0, 0, 0, 0, BLACK);

				}

			}
			if (pattern_4 == true) {
				for (int i = 0; i < MAX_BULLET_t; i++) {
					if (bullet_t_flag[i] == true) {
						if (dekaku == true) {
							screen.DrawEllipse(bullet_t_pos[i].x, bullet_t_pos[i].y, bullet_rad[i] + RAND(-50, 50), bullet_rad[i] + RAND(-50, 50), 0, 0xFFFF00FF, kFillModeSolid);

						}

					}

				}
				////残像
				for (int i = 0; i < MAX_ZAN; i++) {
					if (bakuha == false) {
						if (zan_flag[i] == true && bakuha_back == false) {
							if (dekaku == true) {
								screen.DrawEllipse(zanpos[i].x, zanpos[i].y, zanrad[i], zanrad[i], 0, 0xFFFF00aa, kFillModeSolid);
							}
						}
					}
				}
			}

		}
	for (int i = 0; i < MAX_DAME; i++) {
		if (dame.flag[i] == true) {
			screen.DrawEllipse(dame.pos[i].x, dame.pos[i].y, dame.rad[i], dame.rad[i], 0, dame.color[i], kFillModeSolid);

		}
	}
	for (int i = 0; i < MAX_RUNE; i++) {
		if (rune.flag[i] == true) {
			screen.DrawEllipse(rune.pos[i].x, rune.pos[i].y, rune.rad[i], rune.rad[i], 0, rune.color[i], kFillModeSolid);

		}
	}
	screen.DrawEllipse(position.x, position.y, radian+radius_f, radian+radius_f, 0.0f, Boss_color, kFillModeSolid);
	if (hit == true) {
		screen.DrawEllipse(position.x, position.y, radian + radius_f, radian + radius_f, 0.0f, 0xFFFFFF33, kFillModeSolid);

	}
	if (shild >= 1) {
		screen.DrawEllipse(position.x, position.y, 200, 200, 0.0f, RED, kFillModeWireFrame);
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


