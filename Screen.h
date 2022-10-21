#pragma once
#include <Novice.h>
#include <Vec2.h>
#include "Function.h"
#include "Quad.h"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

class Screen
{
public:

	Screen();

	int Width;
	int Height;
	Vec2 Worldcenter;
	Vec2 Scroll;
	Vec2 ScreenShake;
	float Scroll_Fixed_Value_X;
	bool Ishit;

	Vec2 Zoom;
	
	void Scroll_update(float playerX, int map_sheets_number);
	
	
	void Shake(int mixX,int maxX,int mixY,int maxY, bool is);

	
    /// <summary>
	/// 四角形を描画する
	/// </summary>
	/// <param name="x">描画する四角形の左上座標 X</param>
	/// <param name="y">描画する四角形の左上座標 Y</param>
	/// <param name="w">描画する四角形の横幅</param>
	/// <param name="h">描画する四角形の縦幅</param>
	/// <param name="angle">描画する四角形の回転角</param>
	/// <param name="color">描画する四角形の色</param>
	/// <param name="fillMode">塗りつぶしモード</param>
	void DrawBox(float x, float y, float w, float h, float angle, unsigned int color, FillMode fillMode);
	/// <summary>
	/// 三角形を描画する
	/// </summary>
	/// <param name="x1">描画する三角形の頂点1 X</param>
	/// <param name="y1">描画する三角形の頂点1 Y</param>
	/// <param name="x2">描画する三角形の頂点2 X</param>
	/// <param name="y2">描画する三角形の頂点2 Y</param>
	/// <param name="x3">描画する三角形の頂点3 X</param>
	/// <param name="y3">描画する三角形の頂点3 Y</param>
	/// <param name="color">描画する三角形の色</param>
	/// <param name="fillMode">塗りつぶしモード</param>
	void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, unsigned int color, FillMode fillMode);
	/// <summary>
	/// 線を描画する
	/// </summary>
	/// <param name="x1">描画する線の始点座標 X</param>
	/// <param name="y1">描画する線の始点座標 Y</param>
	/// <param name="x2">描画する線の終点座標 X</param>
	/// <param name="y2">描画する線の終点座標 Y</param>
	/// <param name="color">描画する三角形の色</param>
	void DrawLine(float x1, float y1, float x2, float y2, unsigned int color);
	/// <summary>
	/// 楕円を描画する
	/// </summary>
	/// <param name="x">楕円の中心座標 X</param>
	/// <param name="y">楕円の中心座標 Y</param>
	/// <param name="radiusX">楕円の半径 X</param>
	/// <param name="radiusY">楕円の半径 Y</param>
	/// <param name="angle">楕円の回転角(rad)</param>
	/// <param name="color">楕円の色</param>
	void DrawEllipse(float x, float y, float radiusX, float radiusY, float angle, unsigned int color, FillMode fillMode);
	/// <summary>
	/// スプライトを描画する
	/// </summary>
	/// <param name="x">描画するスプライトの左上座標 X</param>
	/// <param name="y">描画するスプライトの左上座標 Y</param>
	/// <param name="textureHandle">テクスチャのハンドル</param>
	/// <param name="scale">描画するスプライトの倍率 X</param>
	/// <param name="scale">描画するスプライトの倍率 Y</param>
	/// <param name="angle">描画するスプライトの回転角</param>
	/// <param name="color">描画するスプライトの色</param>
	void DrawSprite(int x, int y, int textureHandle, int scaleX, int scaleY, int angle, unsigned int color);
	/// <summary>
	/// スプライトの指定矩形部分のみを描画を描画する
	/// </summary>
	/// <param name="destX">描画するスプライトの左上座標 X</param>
	/// <param name="destY">描画するスプライトの左上座標 X</param>
	/// <param name="srcX">画像上の描画したい範囲左上座標 X</param>
	/// <param name="srcY">画像上の描画したい範囲左上座標 Y</param>
	/// <param name="srcW">画像上の描画したい範囲横幅</param>
	/// <param name="srcH">画像上の描画したい範囲縦幅</param>
	/// <param name="textureHandle">テクスチャのハンドル</param>
	/// <param name="scale">描画するスプライトの倍率 X</param>
	/// <param name="scale">描画するスプライトの倍率 Y</param>
	/// <param name="angle">描画するスプライトの回転角</param>
	/// <param name="color">描画するスプライトの色</param>
	void DrawSpriteRect(int destX, int destY, int srcX, int srcY, int srcW, int srcH, int textureHandle, int scaleX,int scaleY, int angle, unsigned int color);
	/// <summary>
	/// 四角形描画
	/// </summary>
	/// <param name="x1">描画する四角形の左上座標 X</param>
	/// <param name="y1">描画する四角形の左上座標 Y</param>
	/// <param name="x2">描画する四角形の右上座標 X</param>
	/// <param name="y2">描画する四角形の右上座標 Y</param>
	/// <param name="x3">描画する四角形の左下座標 X</param>
	/// <param name="y3">描画する四角形の左下座標 Y</param>
	/// <param name="x4">描画する四角形の右下座標 X</param>
	/// <param name="y4">描画する四角形の右下座標 Y</param>
	/// <param name="srcX">画像上の描画したい範囲左上座標 X</param>
	/// <param name="srcY">画像上の描画したい範囲左上座標 Y</param>
	/// <param name="srcW">画像上の描画したい範囲横幅</param>
	/// <param name="srcH">画像上の描画したい範囲縦幅</param>
	/// <param name="textureHandle">テクスチャのハンドル</param>
	/// <param name="color">描画するスプライトの色</param>
	void DrawQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float srcX, float srcY, float srcW,float srcH, float textureHandle, unsigned int color);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="x1">描画する四角形の左上座標</param>
	/// <param name="y1">描画する四角形の左上座標</param>
	/// <param name="quadw">描画する四角形の範囲横幅</param>
	/// <param name="quadh">描画する四角形の範囲縦幅</param>
	/// <param name="srcX">画像上の描画したい範囲左上座標 X</param>
	/// <param name="srcY">画像上の描画したい範囲左上座標 Y</param>
	/// <param name="srcW">画像上の描画したい範囲横幅</param>
	/// <param name="srcH">画像上の描画したい範囲縦幅</param>
	/// <param name="textureHandle">テクスチャのハンドル</param>
	/// <param name="color">描画するスプライトの色</param>
	void DrawQuad2(Quad& quad, float srcX, float srcY, float srcW, float srcH, float textureHandle, unsigned int color);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="x1">描画する四角形の左上座標</param>
	/// <param name="y1">描画する四角形の左上座標</param>
	/// <param name="quadw">描画する四角形の範囲横幅</param>
	/// <param name="quadh">描画する四角形の範囲縦幅</param>
	/// <param name="srcX">画像上の描画したい範囲左上座標 X</param>
	/// <param name="srcY">画像上の描画したい範囲左上座標 Y</param>
	/// <param name="srcW">画像上の描画したい範囲横幅</param>
	/// <param name="srcH">画像上の描画したい範囲縦幅</param>
	/// <param name="textureHandle">テクスチャのハンドル</param>
	/// <param name="color">描画するスプライトの色</param>
	void DrawQuad2normal(int x1, int y1, int quadw, int quadh, int srcX, int srcY, int srcW, int srcH, int textureHandle, unsigned int color);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="x1">描画する四角形の左上座標</param>
	/// <param name="y1">描画する四角形の左上座標</param>
	/// <param name="quadw">描画する四角形の範囲横幅</param>
	/// <param name="quadh">描画する四角形の範囲縦幅</param>
	/// <param name="srcX">画像上の描画したい範囲左上座標 X</param>
	/// <param name="srcY">画像上の描画したい範囲左上座標 Y</param>
	/// <param name="srcW">画像上の描画したい範囲横幅</param>
	/// <param name="srcH">画像上の描画したい範囲縦幅</param>
	/// <param name="textureHandle">テクスチャのハンドル</param>
	/// <param name="color">描画するスプライトの色</param>
	void DrawQuad2normal2(int x1, int y1, int quadw, int quadh, int& srcX, int srcY, int srcW, int srcH,int renban,int frame,int& framehensuu, int textureHandle, unsigned int color);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="x1">描画する四角形の左上座標</param>
	/// <param name="y1">描画する四角形の左上座標</param>
	/// <param name="quadw">描画する四角形の範囲横幅</param>
	/// <param name="quadh">描画する四角形の範囲縦幅</param>
	/// <param name="scroll">スクロールする値</param>
	/// <param name="srcX">画像上の描画したい範囲左上座標 X</param>
	/// <param name="srcY">画像上の描画したい範囲左上座標 Y</param>
	/// <param name="srcW">画像上の描画したい範囲横幅</param>
	/// <param name="srcH">画像上の描画したい範囲縦幅</param>
	/// <param name="textureHandle">テクスチャのハンドル</param>
	/// <param name="color">描画するスプライトの色</param>
	void Background(int x1, int y1, int quadw, int quadh,float scrollkakeru, int srcX, int srcY, int srcW, int srcH, int textureHandle, unsigned int color);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="x1">描画する四角形の左上座標</param>
	/// <param name="y1">描画する四角形の左上座標</param>
	/// <param name="quadw">描画する四角形の範囲横幅</param>
	/// <param name="quadh">描画する四角形の範囲縦幅</param>
	/// <param name="srcX">画像上の描画したい範囲左上座標 X</param>
	/// <param name="srcY">画像上の描画したい範囲左上座標 Y</param>
	/// <param name="srcW">画像上の描画したい範囲横幅</param>
	/// <param name="srcH">画像上の描画したい範囲縦幅</param>
	/// <param name="textureHandle">テクスチャのハンドル</param>
	/// <param name="color">描画するスプライトの色</param>
	void DrawMaptip(int x1, int y1, int quadw, int quadh, int srcX, int srcY, int srcW, int srcH, int textureHandle, unsigned int color);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="x1">描画する四角形の左上座標</param>
	/// <param name="y1">描画する四角形の左上座標</param>
	/// <param name="quadw">描画する四角形の範囲横幅</param>
	/// <param name="quadh">描画する四角形の範囲縦幅</param>
	/// <param name="srcX">画像上の描画したい範囲左上座標 X</param>
	/// <param name="srcY">画像上の描画したい範囲左上座標 Y</param>
	/// <param name="srcW">画像上の描画したい範囲横幅</param>
	/// <param name="srcH">画像上の描画したい範囲縦幅</param>
	/// <param name="renban">画像上の描画したい範囲縦幅</param>
	/// <param name="frame">何フレームで次の連番画像に移るか</param>
	/// <param name="framehensuu">フレームの変数</param>
	/// <param name="textureHandle">テクスチャのハンドル</param>
	/// <param name="color">描画するスプライトの色</param>
	/// <param name="hanten">反転をするか</param>
	void DrawQuad2P(int x1, int y1, int quadw, int quadh, int& srcX, int srcY, int srcW, int srcH,int renban,int frame,int& framehensuu, int textureHandle, unsigned int color, bool hanten);


};


