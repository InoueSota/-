#include "Figure.h"


Figure::Figure() {
	SRAND();
	colortime = 0;
	responflag = false;
}

float Figure::IsRespon(Map map) {
	return map.radius * 0.04;
}

float Figure::stage(Map map) {
	return map.radius;
}

float Figure::Area(Player& player,Screen screen,Map map) {
	return player.center.x + stage(map) / screen.Zoom.x;
}

float Figure::RadianMin(Player& player) {
	return player.radius * 0.4;
}

float Figure::RadianMax(Player& player) {
	return player.radius * 2.5;
}

bool Figure::cheakdraw(Player player, Vec2 Position, Screen screen ,bool Flag) {
	Vec2 tmp(Position.x - screen.Scroll.x, Position.y - screen.Scroll.y);
	Position.x = tmp.x * screen.Zoom.x + player.center.x + screen.ScreenShake.x;
	Position.y = tmp.y * screen.Zoom.y * -1 + player.center.y - screen.ScreenShake.y;
	if (player.center.x + (SCREEN_WIDTH / 2 ) + 100 > Position.x /** screen.Zoom.x*/ && player.center.x - (SCREEN_WIDTH / 2)  - 100 < Position.x /** screen.Zoom.x */&& player.center.y + (SCREEN_HEIGHT / 2) + 100 > Position.y /** screen.Zoom.y*/ && player.center.y - (SCREEN_HEIGHT / 2) - 100 < Position.y /** screen.Zoom.y*/ && Flag == true && player.radius / 11 < radian) {
		return true;
	}
	else {
		return false;
	}
}

bool Figure::InScreen(Player player, Vec2 Position, Screen screen) {
	Vec2 tmp(Position.x - screen.Scroll.x, Position.y - screen.Scroll.y);
	Position.x = tmp.x * screen.Zoom.x + player.center.x + screen.ScreenShake.x;
	Position.y = tmp.y * screen.Zoom.y * -1 + player.center.y - screen.ScreenShake.y;
	if (player.center.x + SCREEN_WIDTH / 2 + 100 > Position.x && player.center.x - SCREEN_WIDTH / 2 - 100 < Position.x && player.center.y + SCREEN_HEIGHT / 2 + 100 > Position.y && player.center.y - SCREEN_HEIGHT / 2 - 100 < Position.y) {
		return true;
	}
	else {
		return false;
	}
}

llipse::llipse() {
	count_state = 240;
	count_end = 300;
	
}

bool llipse::IsInStage(float stage) {
	stage;//ステージの半径
	if (sqrt((powf(position.x, 2) + powf(position.y, 2)) + radian ) < stage - 200) {
		return false;
	}
	return true;
}
void llipse::Update(Player player, Screen screen, Map map, WAVE wave) {
	if (!(InScreen(player,position,screen)) && radian >= player.radius * 8.0) {
		flag = false;
	}
	//if (!easingset) {
	//	start = {0,0};
	//	end = player.center;
	//	/*end.x = (player.center.x - position.x) / radian;
	//	end.y = (player.center.y - position.y) / radian;*/
	//	easingset = true;
	//	easingflag = true;
	//	t = 0.0f;
	//}
	//if (easingflag) {
	//	t+=0.01;
	//	position.x = Lerp(Easing::easeInSine(t),end.x)+ position.x;
	//	position.y = Lerp(Easing::easeInSine(t), end.y) + position.y;
	//	if (t >= 1.0f) {
	//		easingflag = false;
	//		easingset = false;
	//		count = 0;
	//		t = 0.0f;
	//	}
	//}

}

void llipse::set(Player& player,Screen screen,Map map,WAVE wave) {
		do {
			position.x = RAND(-Area(player, screen, map), Area(player, screen, map));
			position.y = RAND(-Area(player, screen, map), Area(player, screen, map));
		} while (llipse::IsInStage(stage(map)));
	count = RAND(0, 240);
	//半径
	if (wave.stage_1_only) {
		radian = RAND(25 * 1.5, 25 * 8.0);
	}
	else if(wave.stage_2) {
		radian = RAND(80 * 1.5, 80 * 5.0);
	}
	else {
		radian = RAND(80 * 1.5, 80 * 5.0);
	}
	//色
	color = 0xE80971FF;
	responflag = true;
	flag = true;
}

//bool llipse::cheakdraw(Screen screen, Vec2 Position, int width, int height,bool Flag) {
//	if (screen.Scroll.x + width / 2 + 100 > Position.x && screen.Scroll.x - width / 2 - 100 < Position.x && screen.Scroll.y + height / 2 + 100 > Position.y && screen.Scroll.y - height / 2 - 100 < Position.y && Flag == true) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}

void Figure::reset() {
	colortime += 0.01f;
	color = 0xE8097100 | static_cast<int>((1.0f - colortime) * 0x00 + colortime * 0xFF);
	if (colortime >= 1) {
		color = 0xE80971FF;
		colortime = 0.0f;
		responflag = false;
	}
}
void llipse::respon(Player player, Screen screen,Map map,WAVE wave) {
	if (player.radius < IsRespon(map)) {
		cooltime = 0;
		set(player, screen,map, wave);
	}
	else {
		flag = false;
	}
}

void llipse::draw(Screen& screen, Player& players) {
	screen.DrawEllipse(position.x, position.y, radian, radian, 0.0f, color, kFillModeSolid);
}

bool llipse::Player_Ellipse(Player player) {
	Vec2 start_to_center = Vec2(position - player.center);
	Vec2 start_to_end = Vec2(player.pos - player.center);
	Vec2 nomalize_stc = start_to_center.Normalized();

	/*float dot01 = start_to_center.x * start_to_end.x + start_to_center.y * start_to_end.y;*/

	float t = ((start_to_center.Dot(nomalize_stc)) / start_to_end.Length());
	t = Clamp(t, 0, 1);

	Vec2 f = (1.0f - t) * player.center + t * player.pos;

	float distance = (position - f).Length();

	if (distance < player.radius / 50 + radian) {
		if (player.Length <= radian*2) {

			return true;
		}
	}
	return false;
}

Seed::Seed() {
	seedcount = 0;
	t = 0.0f;
	/*UpdateFlag = false;*/
}

void Seed::set(Player& player, Screen screen, Map map, Vec2 pos,int seed) {
	if (seed > SeedMax) {
		seedcount = SeedMax;
	}
	else {
		seedcount = seed;
	}
	for (int i = 0; i < seedcount; i++) {
		position[i] = pos;
		Vec2 Vec;
		Vec.x = RAND(-500, 500);
		Vec.y = RAND(-500, 500);
		vec[i] = Vec.Normalized() * RAND(2, 4);
	}

	radian = player.radius * 0.5;
	color = WHITE;

	UpdateFlag = true;
	setFlag = true;
}

void Seed::Update(Player player, Screen screen, Map map) {
		t += 0.01;
		if (t > 1) {
			UpdateFlag = false;
			setFlag = false;
			t = 0.0f;
			seedcount = 0;
			for (int i = 0; i < seedcount; i++) {
				vec[i] = { 0.0f, 0.0f };
				position[i] = { 0.0f, 0.0f };
			}
		}
		else {
			for (int i = 0; i < seedcount; i++) {
				position[i] += vec[i];
			}
		}

}

void Seed::respon(Player player, Screen screen,Vec2 pos ,Map map) {

	if (player.radius < IsRespon(map)) {
		set(player,screen,map,pos,3);
	}
	else {
		/*setFlag = true;*/
		UpdateFlag = false;
	}
}

bool Seed::Player_Seed(Player player) {
	Vec2 start_to_center[3];
	Vec2 start_to_end[3];
	Vec2 nomalize_stc[3];
	for (int i = 0; i < 3; i++) {
		start_to_center[i] = Vec2(position[i] - player.center);
		start_to_end[i] = Vec2(player.pos - player.center);
		nomalize_stc[i] = start_to_center[i].Normalized();

		/*float dot01 = start_to_center.x * start_to_end.x + start_to_center.y * start_to_end.y;*/

		float t = ((start_to_center[i].Dot(nomalize_stc[i])) / start_to_end[i].Length());
		t = Clamp(t, 0, 1);

		Vec2 f = (1.0f - t) * player.center + t * player.pos;

		float distance = (position[i] - f).Length();

		if (distance < player.radius / 50 + radian) {
			if (player.Length <= radian * 2) {

				return true;
			}
		}
		return false;
	}
}

void Seed::draw(Screen& screen) {
	for (int i = 0; i < seedcount; i++) {
		screen.DrawEllipse(position[i].x, position[i].y, radian, radian, 0.0f, color, kFillModeSolid);
	}
}

Triangle::Triangle() {
	triangle_death = false;
}

bool Triangle::IsInStage(float stage) {
	if (sqrt((powf(position.x, 2) + powf(position.y, 2)) + sqrt(powf(radian, 2))) < stage - 200) {
		return false;
	}
	return true;
}

void Triangle::Update(Player player, Screen screen, Map map,Seed seed) {
	if (player.radius * 3.0 > radian) {
		radian += 0.5;
		//頂点
		top_position.x = position.x + cosf(theta) * radian;
		top_position.y = position.y + sinf(theta) * radian;
		//左
		left_position.x = position.x + cosf(theta_left) * radian;
		left_position.y = position.y + sinf(theta_left) * radian;
		//右
		right_position.x = position.x + cosf(theta_right) * radian;
		right_position.y = position.y + sinf(theta_right) * radian;
	}
	else {
		seedcount = (int)(radian / 4.0f);
		triangle_death = true;
		flag = false;
		/*respon(player,screen,map);*/
	}
}
void Triangle::set(Player& player, Screen screen,Map map, WAVE wave) {
	do {
		position.x = RAND(-Area(player,screen,map), Area(player,screen,map));
		position.y = RAND(-Area(player,screen,map), Area(player,screen,map));
		//半径
		if (wave.stage_2) {
			radian = RAND(80 * 0.3, 80 * 0.7);
		}
		else {

		}
	} while (Triangle::IsInStage(stage(map)));

	//頂点
	theta = (float)Degree(RAND(0, 360));
	theta_left = 0;
	theta_right = 0;
	if (theta - Degree(120) <= 0.0f) {
		theta_left = theta + Degree(120) - Degree(360);
	}
	else {
		theta_left = theta + Degree(120);
	}

	if (theta_left - Degree(120) <= 0.0f) {
		theta_right = theta_left + Degree(120) - Degree(360);
	}
	else {
		theta_right = theta_left + Degree(120);
	}
	
	//頂点
	top_position.x = position.x + cosf(theta) * radian;
	top_position.y = position.y + sinf(theta) * radian;
	//左
	left_position.x = position.x + cosf(theta_left) * radian;
	left_position.y = position.y + sinf(theta_left) * radian;
	//右
	right_position.x = position.x + cosf(theta_right) * radian;
	right_position.y = position.y + sinf(theta_right) * radian;
	//色
	color = 0xE80971FF;
	responflag = true;
	flag = true;

}

void Triangle::respon(Player player, Screen screen,Map map, WAVE wave) {
	if (player.radius < IsRespon(map)) {
		cooltime = 0;
		set(player, screen,map,wave);
	}
	else {
		flag = false;
		triangle_death = false;
	}
}

//bool Triangle::cheakdraw(Screen screen, Vec2 Position, int width, int height, bool Flag) {
//	if (screen.Scroll.x + width / 2 + 100 > Position.x && screen.Scroll.x - width / 2 - 100 < Position.x && screen.Scroll.y + height / 2 + 100 > Position.y && screen.Scroll.y - height / 2 - 100 < Position.y && Flag == true) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}

void Triangle::draw(Screen& screen) {
	screen.DrawTriangle(top_position.x, top_position.y, left_position.x, left_position.y, right_position.x, right_position.y, color, kFillModeSolid);
}
bool Triangle::Player_Triangle(Player player) {
	Vec2 start_to_center = Vec2(position - player.center);
	Vec2 start_to_end = Vec2(player.pos - player.center);
	Vec2 nomalize_stc = start_to_center.Normalized();

	/*float dot01 = start_to_center.x * start_to_end.x + start_to_center.y * start_to_end.y;*/

	float t = ((start_to_center.Dot(nomalize_stc)) / start_to_end.Length());
	t = Clamp(t, 0, 1);

	Vec2 f = (1.0f - t) * player.center + t * player.pos;

	float distance = (position - f).Length();

	if (distance < player.radius / 50 + radian) {
		if (player.Length <= radian * 2) {

			return true;
		}
	}
	return false;
}


Quadrangle::Quadrangle() {
	UpdatesetFlag = false;
	BreadOpenFlag = false;
	BreadCloseFlag = false;
	drawflag = false;
	vel = { 0,0 };
	t = 0.0f;
	///ブレード1
	bread_1_top_left_position_end = { -20,-20};
	bread_1_top_right_position_end = { -20,-20 };
	bread_1_bottom_left_position_end = { -20,-20 };
	bread_1_bottom_right_position_end = { -20,-20 };
	//ブレード2
	bread_2_top_left_position_end = { -20,-20 };
	bread_2_top_right_position_end = { -20,-20 };
	bread_2_bottom_left_position_end = { -20,-20 };
	bread_2_bottom_right_position_end = { -20,-20 };
}

float Quadrangle::checkroll(float Theta) {
	float a = 0.0f;
	if (Theta - Degree(90) <= 0.0f) {
		return a = Theta - Degree(90) - Degree(360);
	}
	else {
		return a = Theta - Degree(90);
	}
}

bool Quadrangle::IsInStage(float stage) {
	if (sqrt((powf(position.x, 2) + powf(position.y, 2)) + sqrt(powf(radian,2))) < stage - 200) {
		return false;
	}
	return true;
}

void Quadrangle::set(Player& player, Screen screen,Map map) {
	do {
		position.x = RAND(-Area(player,screen,map), Area(player,screen,map));
		position.y = RAND(-Area(player,screen,map), Area(player,screen,map));
		//半径
		radian = RAND(player.radius*2.0, player.radius * 5.0);
	} while (Quadrangle::IsInStage(stage(map)));
	
	//頂点
	theta = (float)Degree(RAND(0, 360));
	Quad op,bread_1,bread_2;
	Matrix33 mat;
	op = {
		{-radian/2,+radian/2},
		{+radian/2,+radian/2},
		{-radian/2,-radian/2},
		{+radian/2,-radian/2},
	};
	bread_1 = {
		{-radian*2,+radian/2 },
		{+radian*2,+radian/2 },
		{-radian*2,-radian/2 },
		{+radian*2,-radian/2 },
	};
	bread_2 = {
		{-(radian / 2),+radian*2},
		{+(radian / 2),+radian*2},
		{-(radian / 2),-radian*2},
		{+(radian / 2),-radian*2},
	};
	mat = Matrix33::Identity();
	mat *= Matrix33::MakeScaling(screen.Zoom);
	mat *= Matrix33::MakeRotation(theta);
	mat *= Matrix33::MakeTranslation(position);
	/*top_right = checkroll(theta);
	bottom_left = checkroll(top_right);
	bottom_right = checkroll(bottom_left);*/

	
	top_left_position = op.LeftTop * mat;
	top_right_position = op.RightTop * mat;
	bottom_left_position = op.LeftBottom * mat;
	bottom_right_position = op.RightBottom * mat;

	///ブレード1
	bread_1_top_left_position_end = bread_1.LeftTop * mat;
	bread_1_top_right_position_end = bread_1.RightTop * mat;
	bread_1_bottom_left_position_end = bread_1.LeftBottom * mat;
	bread_1_bottom_right_position_end = bread_1.RightBottom * mat;
	//ブレード2
	bread_2_top_left_position_end = bread_2.LeftTop * mat;
	bread_2_top_right_position_end = bread_2.RightTop * mat;
	bread_2_bottom_left_position_end = bread_2.LeftBottom * mat;
	bread_2_bottom_right_position_end = bread_2.RightBottom * mat;
	//色
	color = 0xE80971FF;
	flag = true;
	responflag = true;
	BreadOpenFlag = true;
	drawflag = true;
}

void Quadrangle::Update(Player& player, Screen screen, Map map,WAVE wave) {
	if (UpdatesetFlag) {
		theta += theta_plus;
		Matrix33 mat;
		Quad op, bread_1, bread_2;
		op = {
			{-radian / 2,+radian / 2},
			{+radian / 2,+radian / 2},
			{-radian / 2,-radian / 2},
			{+radian / 2,-radian / 2},
		};
		bread_1 = {
			{-radian * 2,+radian / 2 },
			{+radian * 2,+radian / 2 },
			{-radian * 2,-radian / 2 },
			{+radian * 2,-radian / 2 },
		};
		bread_2 = {
			{-(radian / 2),+radian * 2},
			{+(radian / 2),+radian * 2},
			{-(radian / 2),-radian * 2},
			{+(radian / 2),-radian * 2},
		};
		mat = Matrix33::Identity();
		mat *= Matrix33::MakeScaling(screen.Zoom);
		mat *= Matrix33::MakeRotation(theta);
		mat *= Matrix33::MakeTranslation(position);

		top_left_position = op.LeftTop * mat;
		top_right_position = op.RightTop * mat;
		bottom_left_position = op.LeftBottom * mat;
		bottom_right_position = op.RightBottom * mat;
		///ブレード1
		bread_1_top_left_position = bread_1.LeftTop * mat;
		bread_1_top_right_position = bread_1.RightTop * mat;
		bread_1_bottom_left_position = bread_1.LeftBottom * mat;
		bread_1_bottom_right_position = bread_1.RightBottom * mat;
		//ブレード2
		bread_2_top_left_position = bread_2.LeftTop * mat;
		bread_2_top_right_position = bread_2.RightTop * mat;
		bread_2_bottom_left_position = bread_2.LeftBottom * mat;
		bread_2_bottom_right_position = bread_2.RightBottom * mat;
		/*vel = (player.center - position).Normalized() * radian * (1 / radian * 3);*/
		position += vel;
		if (position.x <= End_position.x + radian && position.x >= End_position.x - radian && position.y <= End_position.y+radian&& position.y >= End_position.y - radian) {
			Quad bread_1, bread_2;
				Matrix33 mat;
				bread_1 = {
					{-radian / 2,+radian / 2},
					{+radian / 2,+radian / 2},
					{-radian / 2,-radian / 2},
					{+radian / 2,-radian / 2},
				};
				bread_2 = {
					{-(radian / 2),+radian / 2},
					{+(radian / 2),+radian / 2},
					{-(radian / 2),-radian / 2},
					{+(radian / 2),-radian / 2},
				};

				mat = Matrix33::Identity();
				mat *= Matrix33::MakeScaling(screen.Zoom);
				mat *= Matrix33::MakeRotation(theta);
				mat *= Matrix33::MakeTranslation(position);
				///ブレード1
				bread_1_top_left_position_state = bread_1_top_left_position;
				bread_1_top_right_position_state = bread_1_top_right_position;
				bread_1_bottom_left_position_state = bread_1_bottom_left_position;
				bread_1_bottom_right_position_state = bread_1_bottom_right_position;

				bread_1_top_left_position_end = bread_1.LeftTop * mat;
				bread_1_top_right_position_end = bread_1.RightTop * mat;
				bread_1_bottom_left_position_end = bread_1.LeftBottom * mat;
				bread_1_bottom_right_position_end = bread_1.RightBottom * mat;
				//ブレード2
				bread_2_top_left_position_state = bread_2_top_left_position;
				bread_2_top_right_position_state = bread_2_top_right_position;
				bread_2_bottom_left_position_state = bread_2_bottom_left_position;
				bread_2_bottom_right_position_state = bread_2_bottom_right_position;

				bread_2_top_left_position_end = bread_2.LeftTop * mat;
				bread_2_top_right_position_end = bread_2.RightTop * mat;
				bread_2_bottom_left_position_end = bread_2.LeftBottom * mat;
				bread_2_bottom_right_position_end = bread_2.RightBottom * mat;
			UpdatesetFlag = false;
			BreadCloseFlag = true;
		}
		if (!(InScreen(player, position, screen)) && radian >= player.radius * 1.5) {
			respon(player, screen, map);
		}
		
	}
	if(BreadOpenFlag) {
		if (t > 1) {
			t = 0.0f;
			vel = (player.center - position).Normalized() * radian * (1 / radian * 3);
			theta_plus = (float)Degree(10);
			UpdatesetFlag = true;
			BreadOpenFlag = false;
			End_position = player.center;
		}
		else {
			t += 0.01;

			//bread_1_top_left_position.x = (1.0f- t)* top_left_position.x + t * bread_1_top_left_position_end.x;
			//bread_1_top_left_position.y = (1.0f -t) * top_left_position.y + t * bread_1_top_left_position_end.y;
			//bread_1_top_right_position.x = (1.0f - t) * top_right_position.x + t * bread_1_top_right_position_end.x;
			//bread_1_top_right_position.y = (1.0f - t) * top_right_position.y + t * bread_1_top_right_position_end.y;
			//bread_1_bottom_left_position.x = (1.0f - t) * bottom_left_position.x + t * bread_1_bottom_left_position_end.x;
			//bread_1_bottom_left_position.y = (1.0f - t) * bottom_left_position.y + t * bread_1_bottom_left_position_end.y;
			//bread_1_bottom_right_position.x = (1.0f -t) * bottom_right_position.x + t * bread_1_bottom_right_position_end.x;
			//bread_1_bottom_right_position.y = (1.0f - t) * bottom_right_position.y + t * bread_1_bottom_right_position_end.y;
			////ブレード2
			//bread_2_top_left_position.x = Lerp(Easing::easeOutQuint(t), bread_2_top_left_position_end.x) + position.x;
			//bread_2_top_left_position.y = Lerp(Easing::easeOutQuint(t), bread_2_top_left_position_end.y) + position.y;
			//bread_2_top_right_position.x = Lerp(Easing::easeOutQuint(t), bread_2_top_right_position_end.x) + position.x;
			//bread_2_top_right_position.y = Lerp(Easing::easeOutQuint(t), bread_2_top_right_position_end.y) + position.y;
			//bread_2_bottom_left_position.x = Lerp(Easing::easeOutQuint(t), bread_2_bottom_left_position_end.x) + position.x;
			//bread_2_bottom_left_position.y = Lerp(Easing::easeOutQuint(t), bread_2_bottom_left_position_end.y) + position.y;
			//bread_2_bottom_right_position.x = Lerp(Easing::easeOutQuint(t), bread_2_bottom_right_position_end.x) + position.x;
			//bread_2_bottom_right_position.y = Lerp(Easing::easeOutQuint(t), bread_2_bottom_right_position_end.y) + position.y;
			bread_1_top_left_position.x = Lerp(Easing::easeInOutCirc(t), bread_1_top_left_position_end.x - position.x) + position.x;
			bread_1_top_left_position.y = Lerp(Easing::easeInOutCirc(t), bread_1_top_left_position_end.y - position.y) + position.y;
			bread_1_top_right_position.x = Lerp(Easing::easeInOutCirc(t), bread_1_top_right_position_end.x - position.x) + position.x;
			bread_1_top_right_position.y = Lerp(Easing::easeInOutCirc(t), bread_1_top_right_position_end.y - position.y) + position.y;
			bread_1_bottom_left_position.x = Lerp(Easing::easeInOutCirc(t), bread_1_bottom_left_position_end.x - position.x) + position.x;
			bread_1_bottom_left_position.y = Lerp(Easing::easeInOutCirc(t), bread_1_bottom_left_position_end.y - position.y) + position.y;
			bread_1_bottom_right_position.x = Lerp(Easing::easeInOutCirc(t), bread_1_bottom_right_position_end.x - position.x) + position.x;
			bread_1_bottom_right_position.y = Lerp(Easing::easeInOutCirc(t), bread_1_bottom_right_position_end.y - position.y) + position.y;
			//ブレード2
			bread_2_top_left_position.x = Lerp(Easing::easeInOutCirc(t), bread_2_top_left_position_end.x - position.x) + position.x;
			bread_2_top_left_position.y = Lerp(Easing::easeInOutCirc(t), bread_2_top_left_position_end.y - position.y) + position.y;
			bread_2_top_right_position.x = Lerp(Easing::easeInOutCirc(t), bread_2_top_right_position_end.x - position.x) + position.x;
			bread_2_top_right_position.y = Lerp(Easing::easeInOutCirc(t), bread_2_top_right_position_end.y - position.y) + position.y;
			bread_2_bottom_left_position.x = Lerp(Easing::easeInOutCirc(t), bread_2_bottom_left_position_end.x - position.x) + position.x;
			bread_2_bottom_left_position.y = Lerp(Easing::easeInOutCirc(t), bread_2_bottom_left_position_end.y - position.y) + position.y;
			bread_2_bottom_right_position.x = Lerp(Easing::easeInOutCirc(t), bread_2_bottom_right_position_end.x - position.x) + position.x;
			bread_2_bottom_right_position.y = Lerp(Easing::easeInOutCirc(t), bread_2_bottom_right_position_end.y - position.y) + position.y;

		}
		
	}
	if (BreadCloseFlag) {
		if (t > 1) {
			cooltime += 1;
			if (cooltime > 300) {
				Quad bread_1, bread_2;
				Matrix33 mat;
				bread_1 = {
					{-radian * 2,+radian / 2},
					{+radian * 2,+radian / 2},
					{-radian * 2,-radian / 2},
					{+radian * 2,-radian / 2},
				};
				bread_2 = {
					{-(radian / 2),+radian * 2},
					{+(radian / 2),+radian * 2},
					{-(radian / 2),-radian * 2},
					{+(radian / 2),-radian * 2},
				};

				mat = Matrix33::Identity();
				mat *= Matrix33::MakeScaling(screen.Zoom);
				mat *= Matrix33::MakeRotation(theta);
				mat *= Matrix33::MakeTranslation(position);
				///ブレード1
				bread_1_top_left_position_end = bread_1.LeftTop * mat;
				bread_1_top_right_position_end = bread_1.RightTop * mat;
				bread_1_bottom_left_position_end = bread_1.LeftBottom * mat;
				bread_1_bottom_right_position_end = bread_1.RightBottom * mat;
				//ブレード2
				bread_2_top_left_position_end = bread_2.LeftTop * mat;
				bread_2_top_right_position_end = bread_2.RightTop * mat;
				bread_2_bottom_left_position_end = bread_2.LeftBottom * mat;
				bread_2_bottom_right_position_end = bread_2.RightBottom * mat;

				BreadCloseFlag = false;
				BreadOpenFlag = true;
				cooltime = 0;
				t = 0.0f;
			}
		}
		else {
			t += 0.01;

			bread_1_top_left_position.x = (1.0f - t) * bread_1_top_left_position_state.x + t * bread_1_top_left_position_end.x;/*Lerp(Easing::easeInOutCirc(t), bread_1_top_left_position_end.x - position.x) + position.x*/;
			bread_1_top_left_position.y = (1.0f - t) * bread_1_top_left_position_state.y + t * bread_1_top_left_position_end.y/*Lerp(Easing::easeInOutCirc(t), bread_1_top_left_position_end.y - position.y) + position.y;*/;
			bread_1_top_right_position.x = (1.0f - t) * bread_1_top_right_position_state.x + t * bread_1_top_right_position_end.x/* Lerp(Easing::easeInOutCirc(t), bread_1_top_right_position_end.x - position.x) + position.x;*/;
			bread_1_top_right_position.y = (1.0f - t) * bread_1_top_right_position_state.y + t * bread_1_top_right_position_end.y/*Lerp(Easing::easeInOutCirc(t), bread_1_top_right_position_end.y - position.y) + position.y;*/;
			bread_1_bottom_left_position.x = (1.0f - t) * bread_1_bottom_left_position_state.x + t * bread_1_bottom_left_position_end.x/* Lerp(Easing::easeInOutCirc(t), bread_1_bottom_left_position_end.x - position.x) + position.x;*/;
			bread_1_bottom_left_position.y = (1.0f - t) * bread_1_bottom_left_position_state.y + t * bread_1_bottom_left_position_end.y/*Lerp(Easing::easeInOutCirc(t), bread_1_bottom_left_position_end.y - position.y) + position.y;*/;
			bread_1_bottom_right_position.x = (1.0f - t) * bread_1_bottom_right_position_state.x + t * bread_1_bottom_right_position_end.x/*Lerp(Easing::easeInOutCirc(t), bread_1_bottom_right_position_end.x - position.x) + position.x;*/;
			bread_1_bottom_right_position.y = (1.0f - t) * bread_1_bottom_right_position_state.y + t * bread_1_bottom_right_position_end.y/*Lerp(Easing::easeInOutCirc(t), bread_1_bottom_right_position_end.y - position.y) + position.y;*/;
			//ブレード2
			bread_2_top_left_position.x = (1.0f - t) * bread_2_top_left_position_state.x + t * bread_2_top_left_position_end.x;
			bread_2_top_left_position.y = (1.0f - t) * bread_2_top_left_position_state.y + t * bread_2_top_left_position_end.y;
			bread_2_top_right_position.x = (1.0f - t) * bread_2_top_right_position_state.x + t * bread_2_top_right_position_end.x;
			bread_2_top_right_position.y = (1.0f - t) * bread_2_top_right_position_state.y + t * bread_2_top_right_position_end.y;
			bread_2_bottom_left_position.x = (1.0f - t) * bread_2_bottom_left_position_state.x + t * bread_2_bottom_left_position_end.x;
			bread_2_bottom_left_position.y = (1.0f - t) * bread_2_bottom_left_position_state.y + t * bread_2_bottom_left_position_end.y;
			bread_2_bottom_right_position.x = (1.0f - t) * bread_2_bottom_right_position_state.x + t * bread_2_bottom_right_position_end.x;
			bread_2_bottom_right_position.y = (1.0f - t) * bread_2_bottom_right_position_state.y + t * bread_2_bottom_right_position_end.y;


		}
	}

}

void Quadrangle::respon(Player player,Screen screen,Map map) {
	if (player.radius < IsRespon(map)) {
		cooltime = 0;
		UpdatesetFlag = false;
		BreadOpenFlag = false;
		BreadCloseFlag = false;
		vel = { 0,0 };
		set(player, screen,map);
		t = 0.0f;
	}
	else {
		flag = false;
	}
}

//bool Quadrangle::cheakdraw(Screen screen, Vec2 Position, int width, int height, bool Flag) {
//	if (screen.Scroll.x + width / 2 + 100 > Position.x && screen.Scroll.x - width / 2 - 100 < Position.x && screen.Scroll.y + height / 2 + 100 > Position.y && screen.Scroll.y - height / 2 - 100 < Position.y && Flag == true) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}
bool Quadrangle::Player_Quadrangle(Player player) {
	Vec2 start_to_center = Vec2(position - player.center);
	Vec2 start_to_end = Vec2(player.pos - player.center);
	Vec2 nomalize_stc = start_to_center.Normalized();

	/*float dot01 = start_to_center.x * start_to_end.x + start_to_center.y * start_to_end.y;*/

	float t = ((start_to_center.Dot(nomalize_stc)) / start_to_end.Length());
	t = Clamp(t, 0, 1);

	Vec2 f = (1.0f - t) * player.center + t * player.pos;

	float distance = (position - f).Length();

	if (distance < player.radius / 50 + radian) {
		if (player.Length <= radian * 2) {

			return true;
		}
	}
	return false;
}
bool Quadrangle::Player_Update(Player player) {
	Vec2 start_to_center = Vec2(position - player.center);
	Vec2 start_to_end = Vec2(player.pos - player.center);
	Vec2 nomalize_stc = start_to_center.Normalized();

	/*float dot01 = start_to_center.x * start_to_end.x + start_to_center.y * start_to_end.y;*/

	float t = ((start_to_center.Dot(nomalize_stc)) / start_to_end.Length());
	t = Clamp(t, 0, 1);

	Vec2 f = (1.0f - t) * player.center + t * player.pos;

	float distance = (position - f).Length();

	if (distance < player.radius / 50 + radian) {
		if (player.Length <= radian * 4) {

			return true;
		}
	}
	return false;
}
void Quadrangle::draw(Screen& screen) {
	screen.DrawQuad(top_left_position.x, top_left_position.y, top_right_position.x, top_right_position.y, bottom_left_position.x, bottom_left_position.y, bottom_right_position.x, bottom_right_position.y, 0.0f, 0.0f, radian, radian, 0, color);
}

void Quadrangle::breaddraw(Screen& screen) {
	if (!(t > 1 && BreadCloseFlag)) {
		screen.DrawQuad(bread_1_top_left_position.x, bread_1_top_left_position.y, bread_1_top_right_position.x, bread_1_top_right_position.y, bread_1_bottom_left_position.x, bread_1_bottom_left_position.y, bread_1_bottom_right_position.x, bread_1_bottom_right_position.y, 0.0f, 0.0f, radian, radian, 0, WHITE);
		screen.DrawQuad(bread_2_top_left_position.x, bread_2_top_left_position.y, bread_2_top_right_position.x, bread_2_top_right_position.y, bread_2_bottom_left_position.x, bread_2_bottom_left_position.y, bread_2_bottom_right_position.x, bread_2_bottom_right_position.y, 0.0f, 0.0f, radian / 2, radian, 0, WHITE);
	}
}