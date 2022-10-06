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

void Drain_Circle(float px, float py, float prad, const int i, float ex[], float ey[], float erad[]) {

	if (sqrtf((px - ex[i]) * (px - ex[i]) + (py - ey[i]) * (py - ey[i])) <= (prad + erad[i])) {
		//Drain(prad, erad);
		prad += 200;
	}
	
	
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