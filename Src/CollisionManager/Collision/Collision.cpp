#include "Collision.h"

//IsHitRect(2D)の定義
bool CCollision::IsHitRect(int myPos_X, int myPos_Y, int side, int Vertical,
	int pos_1X, int pos_1Y, int Rectside, int RectVertical)
{
	if (myPos_X < pos_1X + Rectside &&
		myPos_X + side > pos_1X &&
		myPos_Y + Vertical > pos_1Y &&
		myPos_Y < pos_1Y + RectVertical)
		return true;
	else
		return false;
}


//IsHitCircle(2D)の定義
bool CCollision::IsHitCircle(int PosX, int PosY, int circle1, int aPosX, int aPosY, int circle2)
{
	if ((circle1 + circle2) * (circle1 + circle2) >
		(aPosX - PosX) * (aPosX - PosX) + (aPosY - PosY) * (aPosY - PosY))
	{
		return true;
	}
	else
		return false;
}

// ボックス同士の当たり判定
bool CCollision::CheckHitBoxToBox(VECTOR ACenterPos, VECTOR ASize, VECTOR BCenterPos, VECTOR BSize)
{
	VECTOR AHalfSize = VScale(ASize, 0.5f);
	VECTOR BHalfSize = VScale(BSize, 0.5f);

	if (ACenterPos.x - AHalfSize.x < BCenterPos.x + BHalfSize.x &&
		ACenterPos.x + AHalfSize.x > BCenterPos.x - BHalfSize.x &&
		ACenterPos.y - AHalfSize.y < BCenterPos.y + BHalfSize.y &&
		ACenterPos.y + AHalfSize.y > BCenterPos.y - BHalfSize.y &&
		ACenterPos.z - AHalfSize.z < BCenterPos.z + BHalfSize.z &&
		ACenterPos.z + AHalfSize.z > BCenterPos.z - BHalfSize.z)
	{
		return true;
	}
	else
		return false;
}

// 球同士の当たり判定
bool CCollision::CheckHitSphereToSphere(VECTOR APos, float ASpereR, VECTOR BPos, float BSpereR)
{
	VECTOR tempPos;

	tempPos.x = APos.x - BPos.x;
	tempPos.y = APos.y - BPos.y;
	tempPos.z = APos.z - BPos.z;

	float tempR = ASpereR + BSpereR;

	if ((tempR * tempR) > (tempPos.x * tempPos.x) + (tempPos.y * tempPos.y) + (tempPos.z * tempPos.z))
	{
		return true;
	}
	else
		return false;

}
