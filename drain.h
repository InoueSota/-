#pragma once
#include <math.h>


void Drain(float rad,float erad) {
	rad += (erad / 10);
}
void DrainMiss(float rad, float erad) {
	rad -= (erad / 10);
}

void Drain_Circle(float px, float py, float prad, float ex, float ey, float erad) {
	if ((sqrtf((px - ex) * (px - ex)) + sqrtf((px - ex) * (px - ex))) <= (prad + erad)) {
		Drain(prad, erad);
	}
	else if ((sqrtf((px - ex) * (px - ex)) + sqrtf((px - ex) * (px - ex))) >= (prad + erad)) {
		DrainMiss(prad, erad);
	}
	
}