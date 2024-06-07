#pragma once
#include "DxLib.h"

class CCollision
{
public:
	//IsHitRectのプロトタイプ宣言
	static bool IsHitRect(int myPos_X, int myPos_Y, int side, int Vertical,
		int pos_1X, int pos_1Y, int Rectside, int RectVertical);

	//IsHitCircleのプロトタイプ宣言
	static bool IsHitCircle(int PosX, int PosY, int circle1, int aPosX, int aPosY, int circle2);

	// ボックス同士の当たり判定
	static bool CheckHitBoxToBox(VECTOR ACenterPos, VECTOR MySize, VECTOR BCenterPos, VECTOR Size);

	// 球同士の当たり判定
	static bool CheckHitSphereToSphere(VECTOR APos, float ASpereR, VECTOR BPos, float BSpereR);
};

