#pragma once
#include <Novice.h>
#include <Vec2.h>
#include "Function.h"

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

	
	
	void Scroll_update(float playerX, int map_sheets_number);
	
	
	void Shake(int mixX,int maxX,int mixY,int maxY, bool is);

	
    /// <summary>
	/// �l�p�`��`�悷��
	/// </summary>
	/// <param name="x">�`�悷��l�p�`�̍�����W X</param>
	/// <param name="y">�`�悷��l�p�`�̍�����W Y</param>
	/// <param name="w">�`�悷��l�p�`�̉���</param>
	/// <param name="h">�`�悷��l�p�`�̏c��</param>
	/// <param name="angle">�`�悷��l�p�`�̉�]�p</param>
	/// <param name="color">�`�悷��l�p�`�̐F</param>
	/// <param name="fillMode">�h��Ԃ����[�h</param>
	void DrawBox(int x, int y, int w, int h, float angle, unsigned int color, FillMode fillMode);
	/// <summary>
	/// �O�p�`��`�悷��
	/// </summary>
	/// <param name="x1">�`�悷��O�p�`�̒��_1 X</param>
	/// <param name="y1">�`�悷��O�p�`�̒��_1 Y</param>
	/// <param name="x2">�`�悷��O�p�`�̒��_2 X</param>
	/// <param name="y2">�`�悷��O�p�`�̒��_2 Y</param>
	/// <param name="x3">�`�悷��O�p�`�̒��_3 X</param>
	/// <param name="y3">�`�悷��O�p�`�̒��_3 Y</param>
	/// <param name="color">�`�悷��O�p�`�̐F</param>
	/// <param name="fillMode">�h��Ԃ����[�h</param>
	void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, unsigned int color, FillMode fillMode);
	/// <summary>
	/// ����`�悷��
	/// </summary>
	/// <param name="x1">�`�悷����̎n�_���W X</param>
	/// <param name="y1">�`�悷����̎n�_���W Y</param>
	/// <param name="x2">�`�悷����̏I�_���W X</param>
	/// <param name="y2">�`�悷����̏I�_���W Y</param>
	/// <param name="color">�`�悷��O�p�`�̐F</param>
	void DrawLine(int x1, int y1, int x2, int y2, unsigned int color);
	/// <summary>
	/// �ȉ~��`�悷��
	/// </summary>
	/// <param name="x">�ȉ~�̒��S���W X</param>
	/// <param name="y">�ȉ~�̒��S���W Y</param>
	/// <param name="radiusX">�ȉ~�̔��a X</param>
	/// <param name="radiusY">�ȉ~�̔��a Y</param>
	/// <param name="angle">�ȉ~�̉�]�p(rad)</param>
	/// <param name="color">�ȉ~�̐F</param>
	void DrawEllipse(int x, int y, int radiusX, int radiusY, float angle, unsigned int color, FillMode fillMode);
	/// <summary>
	/// �X�v���C�g��`�悷��
	/// </summary>
	/// <param name="x">�`�悷��X�v���C�g�̍�����W X</param>
	/// <param name="y">�`�悷��X�v���C�g�̍�����W Y</param>
	/// <param name="textureHandle">�e�N�X�`���̃n���h��</param>
	/// <param name="scale">�`�悷��X�v���C�g�̔{�� X</param>
	/// <param name="scale">�`�悷��X�v���C�g�̔{�� Y</param>
	/// <param name="angle">�`�悷��X�v���C�g�̉�]�p</param>
	/// <param name="color">�`�悷��X�v���C�g�̐F</param>
	void DrawSprite(int x, int y, int textureHandle, float scaleX, float scaleY, float angle, unsigned int color);
	/// <summary>
	/// �X�v���C�g�̎w���`�����݂̂�`���`�悷��
	/// </summary>
	/// <param name="destX">�`�悷��X�v���C�g�̍�����W X</param>
	/// <param name="destY">�`�悷��X�v���C�g�̍�����W X</param>
	/// <param name="srcX">�摜��̕`�悵�����͈͍�����W X</param>
	/// <param name="srcY">�摜��̕`�悵�����͈͍�����W Y</param>
	/// <param name="srcW">�摜��̕`�悵�����͈͉���</param>
	/// <param name="srcH">�摜��̕`�悵�����͈͏c��</param>
	/// <param name="textureHandle">�e�N�X�`���̃n���h��</param>
	/// <param name="scale">�`�悷��X�v���C�g�̔{�� X</param>
	/// <param name="scale">�`�悷��X�v���C�g�̔{�� Y</param>
	/// <param name="angle">�`�悷��X�v���C�g�̉�]�p</param>
	/// <param name="color">�`�悷��X�v���C�g�̐F</param>
	void DrawSpriteRect(int destX, int destY, int srcX, int srcY, int srcW, int srcH, int textureHandle, float scaleX,float scaleY, float angle, unsigned int color);
	/// <summary>
	/// �l�p�`�`��
	/// </summary>
	/// <param name="x1">�`�悷��l�p�`�̍�����W X</param>
	/// <param name="y1">�`�悷��l�p�`�̍�����W Y</param>
	/// <param name="x2">�`�悷��l�p�`�̉E����W X</param>
	/// <param name="y2">�`�悷��l�p�`�̉E����W Y</param>
	/// <param name="x3">�`�悷��l�p�`�̍������W X</param>
	/// <param name="y3">�`�悷��l�p�`�̍������W Y</param>
	/// <param name="x4">�`�悷��l�p�`�̉E�����W X</param>
	/// <param name="y4">�`�悷��l�p�`�̉E�����W Y</param>
	/// <param name="srcX">�摜��̕`�悵�����͈͍�����W X</param>
	/// <param name="srcY">�摜��̕`�悵�����͈͍�����W Y</param>
	/// <param name="srcW">�摜��̕`�悵�����͈͉���</param>
	/// <param name="srcH">�摜��̕`�悵�����͈͏c��</param>
	/// <param name="textureHandle">�e�N�X�`���̃n���h��</param>
	/// <param name="color">�`�悷��X�v���C�g�̐F</param>
	void DrawQuad(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int srcX, int srcY, int srcW,int srcH, int textureHandle, unsigned int color);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="x1">�`�悷��l�p�`�̍�����W</param>
	/// <param name="y1">�`�悷��l�p�`�̍�����W</param>
	/// <param name="quadw">�`�悷��l�p�`�͈͉̔���</param>
	/// <param name="quadh">�`�悷��l�p�`�͈̔͏c��</param>
	/// <param name="srcX">�摜��̕`�悵�����͈͍�����W X</param>
	/// <param name="srcY">�摜��̕`�悵�����͈͍�����W Y</param>
	/// <param name="srcW">�摜��̕`�悵�����͈͉���</param>
	/// <param name="srcH">�摜��̕`�悵�����͈͏c��</param>
	/// <param name="textureHandle">�e�N�X�`���̃n���h��</param>
	/// <param name="color">�`�悷��X�v���C�g�̐F</param>
	void DrawQuad2(int x1, int y1, int quadw, int quadh, int srcX, int srcY, int srcW, int srcH, int textureHandle, unsigned int color);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="x1">�`�悷��l�p�`�̍�����W</param>
	/// <param name="y1">�`�悷��l�p�`�̍�����W</param>
	/// <param name="quadw">�`�悷��l�p�`�͈͉̔���</param>
	/// <param name="quadh">�`�悷��l�p�`�͈̔͏c��</param>
	/// <param name="srcX">�摜��̕`�悵�����͈͍�����W X</param>
	/// <param name="srcY">�摜��̕`�悵�����͈͍�����W Y</param>
	/// <param name="srcW">�摜��̕`�悵�����͈͉���</param>
	/// <param name="srcH">�摜��̕`�悵�����͈͏c��</param>
	/// <param name="textureHandle">�e�N�X�`���̃n���h��</param>
	/// <param name="color">�`�悷��X�v���C�g�̐F</param>
	void DrawQuad2normal(int x1, int y1, int quadw, int quadh, int srcX, int srcY, int srcW, int srcH, int textureHandle, unsigned int color);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="x1">�`�悷��l�p�`�̍�����W</param>
	/// <param name="y1">�`�悷��l�p�`�̍�����W</param>
	/// <param name="quadw">�`�悷��l�p�`�͈͉̔���</param>
	/// <param name="quadh">�`�悷��l�p�`�͈̔͏c��</param>
	/// <param name="srcX">�摜��̕`�悵�����͈͍�����W X</param>
	/// <param name="srcY">�摜��̕`�悵�����͈͍�����W Y</param>
	/// <param name="srcW">�摜��̕`�悵�����͈͉���</param>
	/// <param name="srcH">�摜��̕`�悵�����͈͏c��</param>
	/// <param name="textureHandle">�e�N�X�`���̃n���h��</param>
	/// <param name="color">�`�悷��X�v���C�g�̐F</param>
	void DrawQuad2normal2(int x1, int y1, int quadw, int quadh, int& srcX, int srcY, int srcW, int srcH,int renban,int frame,int& framehensuu, int textureHandle, unsigned int color);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="x1">�`�悷��l�p�`�̍�����W</param>
	/// <param name="y1">�`�悷��l�p�`�̍�����W</param>
	/// <param name="quadw">�`�悷��l�p�`�͈͉̔���</param>
	/// <param name="quadh">�`�悷��l�p�`�͈̔͏c��</param>
	/// <param name="scroll">�X�N���[������l</param>
	/// <param name="srcX">�摜��̕`�悵�����͈͍�����W X</param>
	/// <param name="srcY">�摜��̕`�悵�����͈͍�����W Y</param>
	/// <param name="srcW">�摜��̕`�悵�����͈͉���</param>
	/// <param name="srcH">�摜��̕`�悵�����͈͏c��</param>
	/// <param name="textureHandle">�e�N�X�`���̃n���h��</param>
	/// <param name="color">�`�悷��X�v���C�g�̐F</param>
	void Background(int x1, int y1, int quadw, int quadh,float scrollkakeru, int srcX, int srcY, int srcW, int srcH, int textureHandle, unsigned int color);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="x1">�`�悷��l�p�`�̍�����W</param>
	/// <param name="y1">�`�悷��l�p�`�̍�����W</param>
	/// <param name="quadw">�`�悷��l�p�`�͈͉̔���</param>
	/// <param name="quadh">�`�悷��l�p�`�͈̔͏c��</param>
	/// <param name="srcX">�摜��̕`�悵�����͈͍�����W X</param>
	/// <param name="srcY">�摜��̕`�悵�����͈͍�����W Y</param>
	/// <param name="srcW">�摜��̕`�悵�����͈͉���</param>
	/// <param name="srcH">�摜��̕`�悵�����͈͏c��</param>
	/// <param name="textureHandle">�e�N�X�`���̃n���h��</param>
	/// <param name="color">�`�悷��X�v���C�g�̐F</param>
	void DrawMaptip(int x1, int y1, int quadw, int quadh, int srcX, int srcY, int srcW, int srcH, int textureHandle, unsigned int color);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="x1">�`�悷��l�p�`�̍�����W</param>
	/// <param name="y1">�`�悷��l�p�`�̍�����W</param>
	/// <param name="quadw">�`�悷��l�p�`�͈͉̔���</param>
	/// <param name="quadh">�`�悷��l�p�`�͈̔͏c��</param>
	/// <param name="srcX">�摜��̕`�悵�����͈͍�����W X</param>
	/// <param name="srcY">�摜��̕`�悵�����͈͍�����W Y</param>
	/// <param name="srcW">�摜��̕`�悵�����͈͉���</param>
	/// <param name="srcH">�摜��̕`�悵�����͈͏c��</param>
	/// <param name="renban">�摜��̕`�悵�����͈͏c��</param>
	/// <param name="frame">���t���[���Ŏ��̘A�ԉ摜�Ɉڂ邩</param>
	/// <param name="framehensuu">�t���[���̕ϐ�</param>
	/// <param name="textureHandle">�e�N�X�`���̃n���h��</param>
	/// <param name="color">�`�悷��X�v���C�g�̐F</param>
	/// <param name="hanten">���]�����邩</param>
	void DrawQuad2P(int x1, int y1, int quadw, int quadh, int& srcX, int srcY, int srcW, int srcH,int renban,int frame,int& framehensuu, int textureHandle, unsigned int color, bool hanten);


};


