#include "Screen.h"

Screen::Screen(){
	Width = SCREEN_WIDTH;
	Height = SCREEN_HEIGHT;
	Worldcenter.x = SCREEN_WIDTH / 2;
	Worldcenter.y = SCREEN_HEIGHT / 2;
	Scroll.setZero();
	ScreenShake.setZero();
	Scroll_Fixed_Value_X = 250;
	Zoom = { 1.0f, 1.0f };
};

void Screen::Scroll_update(float playerX, int map_sheets_number) {
	
	if (playerX >= Scroll_Fixed_Value_X && playerX <= Width * map_sheets_number - ( Width - Scroll_Fixed_Value_X)) {

		Scroll.x = playerX - Scroll_Fixed_Value_X;
	}
	if (playerX < Scroll_Fixed_Value_X) {
		Scroll.x = 0;
	}
	
};

void Screen::Shake(int minX, int maxX, int minY, int maxY, bool is) {
	if (is == true) {
		ScreenShake.x = RAND(minX, maxX);
		ScreenShake.y = RAND(minY, maxY);
	}
	else {
		ScreenShake.setZero();
	}
}



void Screen::DrawBox(float x, float y, float w, float h, float angle, unsigned int color, FillMode fillMode) {
	Vec2 tmp(x - Scroll.x, y - Scroll.y);
	x = tmp.x * Zoom.x + Worldcenter.x + ScreenShake.x; 
	y = tmp.y * Zoom.y * -1 + Worldcenter.y - ScreenShake.y;
	Novice::DrawBox(static_cast<int>(x), static_cast<int>(y), w, h, angle, color, fillMode);
}

void Screen::DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, unsigned int color, FillMode fillMode) {
	Vec2 tmp1(x1 - Scroll.x, y1 - Scroll.y);
	Vec2 tmp2(x2 - Scroll.x, y2 - Scroll.y);
	Vec2 tmp3(x3 - Scroll.x, y3 - Scroll.y);
	x1 = tmp1.x * Zoom.x + Worldcenter.x + ScreenShake.x; 
	y1 = tmp1.y * Zoom.y * -1 + Worldcenter.y - ScreenShake.y;
	x2 = tmp2.x * Zoom.x + Worldcenter.x + ScreenShake.x; 
	y2 = tmp2.y * Zoom.y * -1 + Worldcenter.y - ScreenShake.y;
	x3 = tmp3.x * Zoom.x + Worldcenter.x + ScreenShake.x; 
	y3 = tmp3.y * Zoom.y * -1 + Worldcenter.y - ScreenShake.y;
	Novice::DrawTriangle(static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(x2), static_cast<int>(y2), static_cast<int>(x3), static_cast<int>(y3), color, fillMode);
}

void Screen::DrawLine(float x1, float y1, float x2, float y2, unsigned int color) {
	Vec2 tmp1(x1 - Scroll.x, y1 - Scroll.y);
	Vec2 tmp2(x2 - Scroll.x, y2 - Scroll.y);
	x1 = tmp1.x * Zoom.x + Worldcenter.x + ScreenShake.x; 
	y1 = tmp1.y * Zoom.y * -1 + Worldcenter.y - ScreenShake.y;
	x2 = tmp2.x * Zoom.x + Worldcenter.x + ScreenShake.x; 
	y2 = tmp2.y * Zoom.y * -1 + Worldcenter.y - ScreenShake.y;
	Novice::DrawLine(static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(x2), static_cast<int>(y2), color);
}

void Screen::DrawEllipse(float x, float y, float radiusX, float radiusY, float angle, unsigned int color, FillMode fillMode) {
	Vec2 tmp(x - Scroll.x, y - Scroll.y);
	x = tmp.x * Zoom.x + Worldcenter.x + ScreenShake.x; 
	y = tmp.y * Zoom.y * -1 + Worldcenter.y - ScreenShake.y;
	Novice::DrawEllipse(static_cast<int>(x), static_cast<int>(y),  radiusX * Zoom.x,  radiusY * Zoom.y,  angle,  color, fillMode);
}

void Screen::DrawSprite(int x, int y, int textureHandle, int scaleX, int scaleY, int angle, unsigned int color) {
	Novice::DrawSprite( 
		x + Worldcenter.x + ScreenShake.x, 
		y * -1 + Worldcenter.y - ScreenShake.y,  
		textureHandle,  scaleX,  scaleY,  angle,  color);
}

void Screen::DrawSpriteRect(int destX, int destY, int srcX, int srcY, int srcW, int srcH, int textureHandle, int scaleX, int scaleY, int angle, unsigned int color) {
	Novice::DrawSpriteRect(
		destX + Worldcenter.x + ScreenShake.x,
		destY * -1 + Worldcenter.y - ScreenShake.y,
		srcX, srcY, srcW, srcH, textureHandle, scaleX, scaleY, angle, color);
}

void Screen::DrawQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float srcX, float srcY, float srcW, float srcH, float textureHandle, unsigned int color) {
	Vec2 tmp1(x1 - Scroll.x, y1 - Scroll.y);
	Vec2 tmp2(x2 - Scroll.x, y2 - Scroll.y);
	Vec2 tmp3(x3 - Scroll.x, y3 - Scroll.y);
	Vec2 tmp4(x4 - Scroll.x, y4 - Scroll.y);
	x1 = tmp1.x * Zoom.x + Worldcenter.x + ScreenShake.x; 
	y1 = tmp1.y * Zoom.y * -1 + Worldcenter.y - ScreenShake.y;
	x2 = tmp2.x * Zoom.x + Worldcenter.x + ScreenShake.x; 
	y2 = tmp2.y * Zoom.y * -1 + Worldcenter.y - ScreenShake.y;
	x3 = tmp3.x * Zoom.x + Worldcenter.x + ScreenShake.x; 
	y3 = tmp3.y * Zoom.y * -1 + Worldcenter.y - ScreenShake.y;
	x4 = tmp4.x * Zoom.x + Worldcenter.x + ScreenShake.x; 
	y4 = tmp4.y * Zoom.y * -1 + Worldcenter.y - ScreenShake.y;
	Novice::DrawQuad(static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(x2), static_cast<int>(y2), static_cast<int>(x3), static_cast<int>(y3), static_cast<int>(x4), static_cast<int>(y4), srcX, srcY, srcW, srcH, textureHandle, color);
}

void Screen::DrawQuad2(int x1, int y1, int quadw, int quadh, int srcX, int srcY, int srcW, int srcH, int textureHandle, unsigned int color) {
	Novice::DrawQuad(
		x1 + Worldcenter.x - Scroll.x + ScreenShake.x, y1  * -1 + Worldcenter.y + Scroll.y - ScreenShake.y,
		x1 + quadw + Worldcenter.x - Scroll.x + ScreenShake.x, y1  * -1 + Worldcenter.y + Scroll.y - ScreenShake.y,
		x1 + Worldcenter.x - Scroll.x + ScreenShake.x, (y1 - quadh) * - 1   + Worldcenter.y + Scroll.y - ScreenShake.y ,
		x1 + quadw + Worldcenter.x - Scroll.x + ScreenShake.x, (y1 - quadh) * -1   + Worldcenter.y + Scroll.y - ScreenShake.y,
		srcX, srcY, srcW, srcH, textureHandle, color);
}

void Screen::DrawQuad2normal(int x1, int y1, int quadw, int quadh, int srcX, int srcY, int srcW, int srcH, int textureHandle, unsigned int color) {
	Novice::DrawQuad(
		x1 + ScreenShake.x, y1 - ScreenShake.y,
		x1 + quadw + ScreenShake.x, y1 - ScreenShake.y,
		x1 + ScreenShake.x, y1 + quadh - ScreenShake.y,
		x1 + quadw + ScreenShake.x, y1 + quadh - ScreenShake.y,
		srcX, srcY, srcW, srcH, textureHandle, color);
}

void Screen::DrawQuad2normal2(int x1, int y1, int quadw, int quadh, int& srcX, int srcY, int srcW, int srcH, int renban, int frame, int& framehensuu, int textureHandle, unsigned int color) {
	if (framehensuu % frame == 0) {

		srcX += srcW;

	}
	if (srcX == srcW * renban) {

		srcX = 0;

	}
	Novice::DrawQuad(
		x1, y1,
		x1 + quadw, y1,
		x1, y1 + quadh,
		x1 + quadw, y1 + quadh,
		srcX, srcY, srcW, srcH, textureHandle, color);
}
void Screen::DrawMaptip(int x1, int y1, int quadw, int quadh, int srcX, int srcY, int srcW, int srcH, int textureHandle, unsigned int color) {
	Novice::DrawQuad(
		x1  - Scroll.x + ScreenShake.x, y1  + Scroll.y - ScreenShake.y,
		x1 + quadw  - Scroll.x + ScreenShake.x, y1   + Scroll.y - ScreenShake.y,
		x1  - Scroll.x + ScreenShake.x, (y1 + quadh) + Scroll.y - ScreenShake.y,
		x1 + quadw  - Scroll.x + ScreenShake.x, (y1 + quadh) + Scroll.y - ScreenShake.y,
		srcX, srcY, srcW, srcH, textureHandle, color);
}

void Screen::Background(int x1, int y1, int quadw, int quadh, float scrollkakeru, int srcX, int srcY, int srcW, int srcH, int textureHandle, unsigned int color) {
	Novice::DrawQuad(
		x1 + ScreenShake.x - Scroll.x * scrollkakeru, y1 - ScreenShake.y,
		x1 + quadw + ScreenShake.x - Scroll.x * scrollkakeru, y1 - ScreenShake.y,
		x1 + ScreenShake.x - Scroll.x * scrollkakeru, y1 + quadh - ScreenShake.y,
		x1 + quadw + ScreenShake.x - Scroll.x * scrollkakeru, y1 + quadh - ScreenShake.y,
		srcX, srcY, srcW, srcH, textureHandle, color);
}

void Screen::DrawQuad2P(int x1, int y1, int quadw, int quadh, int& srcX, int srcY, int srcW, int srcH,int renban,int frame,int& framehensuu, int textureHandle, unsigned int color, bool hanten) {
	
	if (framehensuu % frame == 0) {

		srcX += srcW ;

	}
	if (srcX >= srcW * renban) {

		srcX = 0;

	}
	if (hanten == 0) {
		Novice::DrawQuad(
			x1 + Worldcenter.x - Scroll.x + ScreenShake.x, y1 * -1 + Worldcenter.y + Scroll.y - ScreenShake.y,
			x1 + quadw + Worldcenter.x - Scroll.x + ScreenShake.x, y1 * -1 + Worldcenter.y + Scroll.y - ScreenShake.y,
			x1 + Worldcenter.x - Scroll.x + ScreenShake.x, (y1 - quadh) * -1 + Worldcenter.y + Scroll.y - ScreenShake.y,
			x1 + quadw + Worldcenter.x - Scroll.x + ScreenShake.x, (y1 - quadh) * -1 + Worldcenter.y + Scroll.y - ScreenShake.y,
			srcX, srcY, srcW, srcH, textureHandle, color);
	}
	if (hanten == 1) {
		Novice::DrawQuad(
			x1 + quadw + Worldcenter.x - Scroll.x + ScreenShake.x, y1 * -1 + Worldcenter.y + Scroll.y - ScreenShake.y,
			x1 + Worldcenter.x - Scroll.x + ScreenShake.x, y1 * -1 + Worldcenter.y + Scroll.y - ScreenShake.y,
			x1 + quadw + Worldcenter.x - Scroll.x + ScreenShake.x, (y1 - quadh) * -1 + Worldcenter.y + Scroll.y - ScreenShake.y,
			x1 + Worldcenter.x - Scroll.x + ScreenShake.x, (y1 - quadh) * -1 + Worldcenter.y + Scroll.y - ScreenShake.y,
			srcX, srcY, srcW, srcH, textureHandle, color);
	}
}
