#include "Screen.h"

Screen::Screen(){
	Width = SCREEN_WIDTH;
	Height = SCREEN_HEIGHT;
	Worldcenter.x = SCREEN_WIDTH / 2;
	Worldcenter.y = SCREEN_HEIGHT / 2;
	Scroll.setZero();
	ScreenShake.setZero();
	Scroll_Fixed_Value_X = 250;
	
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



void Screen::DrawBox(int x, int y, int w, int h, float angle, unsigned int color, FillMode fillMode) {
	Novice::DrawBox(x + Worldcenter.x - Scroll.x + ScreenShake.x, y * -1 + Worldcenter.y + Scroll.y - ScreenShake.y, w, h, angle, color, fillMode);
}

void Screen::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, unsigned int color, FillMode fillMode) {
	Novice::DrawTriangle(x1, y1, x2, y2, x3, y3, color, fillMode);
}

void Screen::DrawLine(int x1, int y1, int x2, int y2, unsigned int color) {
	Novice::DrawLine(x1, y1, x2, y2, color);
}

void Screen::DrawEllipse(int x, int y, int radiusX, int radiusY, float angle, unsigned int color, FillMode fillMode) {
	Novice::DrawEllipse(x + Worldcenter.x - Scroll.x + ScreenShake.x, y * -1 + Worldcenter.y + Scroll.y - ScreenShake.y,  radiusX,  radiusY,  angle,  color, fillMode);
}

void Screen::DrawSprite(int x, int y, int textureHandle, float scaleX, float scaleY, float angle, unsigned int color) {
	Novice::DrawSprite( 
		x + Worldcenter.x - Scroll.x + ScreenShake.x, 
		y * -1 + Worldcenter.y+ Scroll.y - ScreenShake.y,  
		textureHandle,  scaleX,  scaleY,  angle,  color);
}

void Screen::DrawSpriteRect(int destX, int destY, int srcX, int srcY, int srcW, int srcH, int textureHandle, float scaleX, float scaleY, float angle, unsigned int color) {
	Novice::DrawSpriteRect(
		destX + Worldcenter.x - Scroll.x + ScreenShake.x,
		destY * -1 + Worldcenter.y+ Scroll.y - ScreenShake.y,
		srcX, srcY, srcW, srcH, textureHandle, scaleX, scaleY, angle, color);
}

void Screen::DrawQuad(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int srcX, int srcY, int srcW, int srcH, int textureHandle, unsigned int color) {
	Novice::DrawQuad(
		x1 + Worldcenter.x - Scroll.x + ScreenShake.x,		y1 * -1 + Worldcenter.y+ Scroll.y - ScreenShake.y,
		x2 + Worldcenter.x - Scroll.x + ScreenShake.x,	    y2 * -1 + Worldcenter.y+ Scroll.y - ScreenShake.y,
		x3 + Worldcenter.x - Scroll.x + ScreenShake.x,		y3 * -1 + Worldcenter.y+ Scroll.y - ScreenShake.y,
		x4 + Worldcenter.x - Scroll.x + ScreenShake.x,		y4 * -1 + Worldcenter.y+ Scroll.y - ScreenShake.y,
		srcX, srcY, srcW, srcH, textureHandle, color);
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
