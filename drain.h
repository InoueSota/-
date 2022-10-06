#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "Figure.h"

void Drain(float prad) {
	prad += 200;
}
void DrainMiss(float rad, float erad) {
	rad -= (erad / 10);
}

bool Drain_Circle(float px, float py, float prad, llipse& ellipse) {
	
	float a = px - ellipse.position.x;
	float b = py - ellipse.position.y;
	float c = sqrtf(a * a + b * b);

	if (c <= (prad + ellipse.radian)) {
		/*Drain(prad);*/
		return true;
	}
	return false;
	/*else if ((sqrtf((px - ex) * (px - ex)) + sqrtf((px - ex) * (px - ex))) >= (prad + erad)) {
		DrainMiss(prad, erad);
	}*/
	
}