#pragma once
#include <math.h>
#include "Figure.h"
#include "main.h"

void Drain(float rad,float erad) {
	rad +=200;
}
void DrainMiss(float rad, float erad) {
	rad -= (erad / 10);
}
///プロトタイプ宣言//////////////////
bool Drain_Line_top_left(float px, float py, float prad, Triangle& triangle);
bool Drain_Line_right_left(float px, float py, float prad, Triangle& triangle);
bool Drain_Line_top_right(float px, float py, float prad, Triangle& triangle);

bool Drain_Line_topR_topL(float px, float py, float prad, Quadrangle& quad);
bool Drain_Line_bottomR_bottomL(float px, float py, float prad, Quadrangle& quad);
bool Drain_Line_topR_bottomR(float px, float py, float prad, Quadrangle& quad);
bool Drain_Line_topL_bottomL(float px, float py, float prad, Quadrangle& quad);
///プロトタイプ宣言ここまで//////////////////
///円と円の当たり判定/////////////////

bool Drain_Circle(float px, float py, float prad, llipse& ellipse) {

	float a = px - ellipse.position.x;
	float b = py - ellipse.position.y;
	float c = sqrtf(a * a + b * b);

	if (c <= (prad + ellipse.radian)) {
		if (prad >= ellipse.radian) {
			return true;
		}
		if (prad <= ellipse.radian) {
			return false;

		}
	}
	
	
}
///円と三角形の当たり判定/////////////////

bool Drain_Triangle(float px, float py, float prad, Triangle& triangle) {
	if (Drain_Line_top_left(px, py, prad, triangle) == true || Drain_Line_top_right(px, py, prad, triangle) == true || Drain_Line_right_left(px, py, prad, triangle) == true) {
		if (prad >= triangle.radian) {
			return true;
		}
		else
			if (prad < triangle.radian) {
				return false;
			}
	}
}

bool Drain_Quadrangl(float px, float py, float prad, Quadrangle& quad) {
	if (Drain_Line_topR_topL(px, py, prad, quad) == true || Drain_Line_bottomR_bottomL(px, py, prad, quad) == true || Drain_Line_topR_bottomR(px, py, prad, quad) == true || Drain_Line_topL_bottomL(px, py, prad, quad) == true) {

		if (prad >= quad.radian) {
			return true;
		}else
			if (prad < quad.radian) {
				return false;
			}
	}
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
			if (start_to_center.Length() < prad || end_to_center.Length() < prad) {
				return true;
		}

	}
	else {
		//当たってない
		return false;
	}


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
			if (start_to_center.Length() < prad || end_to_center.Length() < prad) {
				return true;
			}

	}
	else {
		//当たってない
		return false;
	}


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
			if (start_to_center.Length() < prad || end_to_center.Length() < prad) {
				return true;
			}

	}
	else {
		//当たってない
		return false;
	}


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
	else {
		//当たってない
		return false;
	}


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
	else {
		//当たってない
		return false;
	}


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
	else {
		//当たってない
		return false;
	}


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
	else {
		//当たってない
		return false;
	}


}