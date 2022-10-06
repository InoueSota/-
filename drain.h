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

bool Drain_Circle(float px, float py, float prad, llipse& ellipse) {

	float a = px - ellipse.position.x;
	float b = py - ellipse.position.y;
	float c = sqrtf(a * a + b * b);

	if (c <= (prad + ellipse.radian)) {
		//Drain(prad, erad);
		return true;
	}
	return false;
	
	
}

//void Drain_Circle(float px, float py, float prad,class llipse&) {
//
//	if (sqrtf((px - maru[].position.x) * (px - maru[].position.x) + (px - maru[].position.y) * (px - maru[].position.y)) <= (prad + maru[].radian)) {
//		
//		prad += 200;
//	}
//
//
//}