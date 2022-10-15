#pragma once
#include <math.h>
#include<Novice.h>
#include "Figure.h"
#include "main.h"
#include "Screen.h"


///プロトタイプ宣言//////////////////
bool Drain_Line_top_left(float px, float py, float prad, Triangle& triangle);
bool Drain_Line_right_left(float px, float py, float prad, Triangle& triangle);
bool Drain_Line_top_right(float px, float py, float prad, Triangle& triangle);

bool Drain_Line_topR_topL(float px, float py, float prad, Quadrangle& quad);
bool Drain_Line_bottomR_bottomL(float px, float py, float prad, Quadrangle& quad);
bool Drain_Line_topR_bottomR(float px, float py, float prad, Quadrangle& quad);
bool Drain_Line_topL_bottomL(float px, float py, float prad, Quadrangle& quad);

bool IsHit_Drain(float px, float py, float prad, llipse& ellipse, Triangle& triangle, Quadrangle& quad, float zoom);
///プロトタイプ宣言ここまで//////////////////
///円と円の当たり判定/////////////////

bool Drain_Circle(float px, float py, float prad, llipse& ellipse, float zoom) {

	float a = px - ellipse.position.x;
	float b = py - ellipse.position.y;
	float c = sqrtf(a * a + b * b);

	if (c <= (prad * zoom + ellipse.radian * zoom)) {
		if (prad * zoom >= ellipse.radian * zoom) {
			return true;
		}
	}
	return false;
}
///円と三角形の当たり判定/////////////////

bool Drain_Triangle(float px, float py, float prad, Triangle& triangle) {
	if (Drain_Line_top_left(px, py, prad, triangle) == true || Drain_Line_top_right(px, py, prad, triangle) == true || Drain_Line_right_left(px, py, prad, triangle) == true) {
		if (prad >= triangle.radian) {
			return true;
		}
	}
	return false;
}

bool Drain_Quadrangl(float px, float py, float prad, Quadrangle& quad) {
	if (Drain_Line_topR_topL(px, py, prad, quad) == true || Drain_Line_bottomR_bottomL(px, py, prad, quad) == true || Drain_Line_topR_bottomR(px, py, prad, quad) == true || Drain_Line_topL_bottomL(px, py, prad, quad) == true) {

		if (prad >= quad.radian) {
			return true;
		}
	}
	return false;
}


///ここから3角形処理///////////////

bool Drain_Line_top_left(float px, float py, float prad, Triangle& triangle) {
	Vec2 start_to_center = Vec2(px - triangle.top_position.x, py - triangle.top_position.y);
	Vec2 end_to_center = Vec2(px - triangle.left_position.x, py - triangle.left_position.y);
	Vec2 start_to_end = Vec2(triangle.left_position.x - triangle.top_position.x, triangle.left_position.y - triangle.top_position.y);

	
	Vec2 Nomalize_STE = start_to_end.Normalized();

	float distance_projection = start_to_center.x * Nomalize_STE.y - Nomalize_STE.x * start_to_center.y;
		 
	if (fabs(distance_projection) < prad) {
		//当たってる
		float dot01 = start_to_center.x * start_to_end.x + start_to_center.y * start_to_end.y;
		float dot02 = end_to_center.x * start_to_end.x + end_to_center.y * start_to_end.y;

		if (dot01 * dot02 <= 0.0f) {
			return true;
		}else 
			if (start_to_center.Length() < prad/2 || end_to_center.Length() < prad/2) {
				return true;
		}

	}
	//当たってない
	return false;

}
bool Drain_Line_right_left(float px, float py, float prad, Triangle& triangle) {
	Vec2 start_to_center = Vec2(px - triangle.right_position.x, py - triangle.right_position.y);
	Vec2 end_to_center = Vec2(px - triangle.left_position.x, py - triangle.left_position.y);
	Vec2 start_to_end = Vec2(triangle.left_position.x - triangle.right_position.x, triangle.left_position.y - triangle.right_position.y);


	Vec2 Nomalize_STE = start_to_end.Normalized();

	float distance_projection = start_to_center.x * Nomalize_STE.y - Nomalize_STE.x * start_to_center.y;

	if (fabs(distance_projection) < prad) {
		//当たってる
		float dot01 = start_to_center.x * start_to_end.x + start_to_center.y * start_to_end.y;
		float dot02 = end_to_center.x * start_to_end.x + end_to_center.y * start_to_end.y;

		if (dot01 * dot02 <= 0.0f) {
			return true;
		}
		else
			if (start_to_center.Length() < prad/2 || end_to_center.Length() < prad/2) {
				return true;
			}

	}
	//当たってない
	return false;

}

bool Drain_Line_top_right(float px, float py, float prad, Triangle& triangle) {
	Vec2 start_to_center = Vec2(px - triangle.top_position.x, py - triangle.top_position.y);
	Vec2 end_to_center = Vec2(px - triangle.right_position.x, py - triangle.right_position.y);
	Vec2 start_to_end = Vec2(triangle.right_position.x - triangle.top_position.x, triangle.right_position.y - triangle.top_position.y);

	Vec2 Nomalize_STE = start_to_end.Normalized();

	float distance_projection = start_to_center.x * Nomalize_STE.y - Nomalize_STE.x * start_to_center.y;

	if (fabs(distance_projection) < prad) {
		//当たってる
		float dot01 = start_to_center.x * start_to_end.x + start_to_center.y * start_to_end.y;
		float dot02 = end_to_center.x * start_to_end.x + end_to_center.y * start_to_end.y;

		if (dot01 * dot02 <= 0.0f) {
			return true;
		}
		else
			if (start_to_center.Length() < prad/2 || end_to_center.Length() < prad/2) {
				return true;
			}

	}
	//当たってない
	return false;

}
///ここから四角形処理///////////////

bool Drain_Line_topR_topL(float px, float py, float prad,Quadrangle& quad) {
	Vec2 start_to_center = Vec2(px - quad.top_right_position.x, py - quad.top_right_position.y);
	Vec2 end_to_center = Vec2(px - quad.top_left_position.x, py - quad.top_left_position.y);
	Vec2 start_to_end = Vec2(quad.top_left_position.x - quad.top_right_position.x, quad.top_left_position.y - quad.top_right_position.y);


	Vec2 Nomalize_STE = start_to_end.Normalized();

	float distance_projection = start_to_center.x * Nomalize_STE.y - Nomalize_STE.x * start_to_center.y;

	if (fabs(distance_projection) < prad) {
		//当たってる
		float dot01 = start_to_center.x * start_to_end.x + start_to_center.y * start_to_end.y;
		float dot02 = end_to_center.x * start_to_end.x + end_to_center.y * start_to_end.y;

		if (dot01 * dot02 <= 0.0f) {
			return true;
		}
		else
			if (start_to_center.Length() < prad || end_to_center.Length() < prad) {
				return true;
			}

	}
	//当たってない
	return false;

}
bool Drain_Line_bottomR_bottomL(float px, float py, float prad, Quadrangle& quad) {
	Vec2 start_to_center = Vec2(px - quad.bottom_right_position.x, py - quad.bottom_right_position.y);
	Vec2 end_to_center = Vec2(px - quad.bottom_left_position.x, py - quad.bottom_left_position.y);
	Vec2 start_to_end = Vec2(quad.bottom_left_position.x - quad.bottom_right_position.x, quad.bottom_left_position.y - quad.bottom_right_position.y);


	Vec2 Nomalize_STE = start_to_end.Normalized();

	float distance_projection = start_to_center.x * Nomalize_STE.y - Nomalize_STE.x * start_to_center.y;

	if (fabs(distance_projection) < prad) {
		//当たってる
		float dot01 = start_to_center.x * start_to_end.x + start_to_center.y * start_to_end.y;
		float dot02 = end_to_center.x * start_to_end.x + end_to_center.y * start_to_end.y;

		if (dot01 * dot02 <= 0.0f) {
			return true;
		}
		else
			if (start_to_center.Length() < prad || end_to_center.Length() < prad) {
				return true;
			}

	}
	//当たってない
	return false;


}
bool Drain_Line_topR_bottomR(float px, float py, float prad, Quadrangle& quad) {
	Vec2 start_to_center = Vec2(px - quad.top_right_position.x, py - quad.top_right_position.y);
	Vec2 end_to_center = Vec2(px - quad.bottom_right_position.x, py - quad.bottom_right_position.y);
	Vec2 start_to_end = Vec2(quad.bottom_right_position.x - quad.top_right_position.x, quad.bottom_right_position.y - quad.top_right_position.y);


	Vec2 Nomalize_STE = start_to_end.Normalized();

	float distance_projection = start_to_center.x * Nomalize_STE.y - Nomalize_STE.x * start_to_center.y;

	if (fabs(distance_projection) < prad) {
		//当たってる
		float dot01 = start_to_center.x * start_to_end.x + start_to_center.y * start_to_end.y;
		float dot02 = end_to_center.x * start_to_end.x + end_to_center.y * start_to_end.y;

		if (dot01 * dot02 <= 0.0f) {
			return true;
		}
		else
			if (start_to_center.Length() < prad || end_to_center.Length() < prad) {
				return true;
			}

	}
	//当たってない
	return false;


}
bool Drain_Line_topL_bottomL(float px, float py, float prad, Quadrangle& quad) {
	Vec2 start_to_center = Vec2(px - quad.top_left_position.x, py - quad.top_left_position.y);
	Vec2 end_to_center = Vec2(px - quad.bottom_left_position.x, py - quad.bottom_left_position.y);
	Vec2 start_to_end = Vec2(quad.bottom_left_position.x - quad.top_left_position.x, quad.bottom_left_position.y - quad.top_left_position.y);


	Vec2 Nomalize_STE = start_to_end.Normalized();

	float distance_projection = start_to_center.x * Nomalize_STE.y - Nomalize_STE.x * start_to_center.y;

	if (fabs(distance_projection) < prad) {
		//当たってる
		float dot01 = start_to_center.x * start_to_end.x + start_to_center.y * start_to_end.y;
		float dot02 = end_to_center.x * start_to_end.x + end_to_center.y * start_to_end.y;

		if (dot01 * dot02 <= 0.0f) {
			return true;
		}
		else
			if (start_to_center.Length() < prad || end_to_center.Length() < prad) {
				return true;
			}

	}
	//当たってない
	return false;

}

///真ん中の線の当たり判定/////////




bool Drain_Center_Circle(Player& player, llipse& ellipse) {

	//center::回っていない
	//pos::回っている

	Vec2 start_to_center = Vec2(ellipse.position - player.center);
	Vec2 start_to_end = Vec2(player.pos - player.center);
	Vec2 nomalize_stc = start_to_center.Normalized();

	/*float dot01 = start_to_center.x * start_to_end.x + start_to_center.y * start_to_end.y;*/

	float t = ((start_to_center.Dot(nomalize_stc)) / start_to_end.Length());
	t = Clamp(t, 0, 1);

	Vec2 f = (1.0f - t) * player.center + t * player.pos;

	float distance =(ellipse.position - f).Length();

	if (distance < player.radius/50 + ellipse.radian) {
		return true;
	}
	return false;

}

bool Drain_Center_Triangle(Player& player,Triangle&triangle) {

	//center::回っていない
	//pos::回っている

	Vec2 start_to_center = Vec2(triangle.position - player.center);
	Vec2 start_to_end = Vec2(player.pos - player.center);
	Vec2 nomalize_stc = start_to_center.Normalized();

	/*float dot01 = start_to_center.x * start_to_end.x + start_to_center.y * start_to_end.y;*/

	float t = ((start_to_center.Dot(nomalize_stc)) / start_to_end.Length());
	t = Clamp(t, 0, 1);

	Vec2 f = (1.0f - t) * player.center + t * player.pos;

	float distance = (triangle.position - f).Length();

	if (distance < player.radius / 50 + triangle.radian) {
		return true;
	}
	return false;

}

bool Drain_Center_Quad(Player& player, Quadrangle& quad) {

	//center::回っていない
	//pos::回っている

	Vec2 start_to_center = Vec2(quad.position - player.center);
	Vec2 start_to_end = Vec2(player.pos - player.center);
	Vec2 nomalize_stc = start_to_center.Normalized();

	/*float dot01 = start_to_center.x * start_to_end.x + start_to_center.y * start_to_end.y;*/

	float t = ((start_to_center.Dot(nomalize_stc)) / start_to_end.Length());
	t = Clamp(t, 0, 1);

	Vec2 f = (1.0f - t) * player.center + t * player.pos;

	float distance = (quad.position - f).Length();

	if (distance < player.radius / 50 + quad.radian) {
		return true;
	}
	return false;

}

///そもそも当たっているのか/////////////////
bool IsHit_Drain(float px, float py, float prad, llipse& ellipse, Triangle& triangle, Quadrangle& quad, float zoom) {
	float a = px - ellipse.position.x;
	float b = py - ellipse.position.y;
	float c = sqrtf(a * a + b * b);

	if (c <= (prad * zoom + ellipse.radian * zoom)) {
		return true;
	}
	if (Drain_Line_top_left(px, py, prad, triangle) == true || Drain_Line_top_right(px, py, prad, triangle) == true || Drain_Line_right_left(px, py, prad, triangle) == true) {
		return true;
	}
	if (Drain_Line_topR_topL(px, py, prad, quad) == true || Drain_Line_bottomR_bottomL(px, py, prad, quad) == true || Drain_Line_topR_bottomR(px, py, prad, quad) == true || Drain_Line_topL_bottomL(px, py, prad, quad) == true) {
		return true;
	}
	return false;
}

//近いかどうか
bool Drain_Check_Ellipse(Player player, llipse ellipse) {
	if (sqrt(powf(player.center.x - player.pos.x, 2) + powf(player.center.y - player.pos.y, 2)) + player.radius >= sqrt(powf(player.center.x - ellipse.position.x, 2) + powf(player.center.y - ellipse.position.y, 2)) - ellipse.radian) {
		return true;
	}
	return false;
}

bool Drain_Check_Triangle(Player player, Triangle triangle) {
	if (sqrt(powf(player.center.x - player.pos.x, 2) + powf(player.center.y - player.pos.y, 2)) + player.radius >= sqrt(powf(player.center.x - triangle.position.x, 2) + powf(player.center.y - triangle.position.y, 2)) - powf(triangle.radian, 2)) {
		return true;
	}
	return false;
}

bool Drain_Check_Quadrangle(Player player, Quadrangle quadrangle) {
	if (sqrt(powf(player.center.x-player.pos.x,2)+powf(player.center.y - player.pos.y, 2))+player.radius >= sqrt(powf(player.center.x - quadrangle.position.x, 2) + powf(player.center.y - quadrangle.position.y, 2)) - powf(quadrangle.radian,2)) {
		return true;
	}
	return false;
}
