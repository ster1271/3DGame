#include "DxLib.h"
#include "MyLibrary.h"
#include <math.h>

//ベクトルの足し算
VECTOR MyMath:: AddVec(VECTOR _vec1, VECTOR _vec2)
{
	VECTOR ret;

	ret.x = _vec1.x + _vec2.x;
	ret.y = _vec1.y + _vec2.y;
	ret.z = _vec1.z + _vec2.z;

	return ret;
}

//ベクトルの引き算
VECTOR MyMath:: SubVec(VECTOR _vec1, VECTOR _vec2)
{
	VECTOR ret;

	ret.x = _vec1.x - _vec2.x;
	ret.y = _vec1.y - _vec2.y;
	ret.z = _vec1.z - _vec2.z;

	return ret;
}

//ベクトルを生成する関数
VECTOR MyMath:: VecCreate(VECTOR start, VECTOR end)
{
	VECTOR ret;

	ret.x = end.x - start.x;
	ret.y = end.y - start.y;
	ret.z = end.z - start.z;
	
	return ret;
}

//ベクトルの長さを計算する関数
float MyMath:: VecLong(VECTOR vec)
{
	float veclong = 0.0f;
	
	veclong = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;

	veclong = sqrtf(veclong);

	return veclong;
}

//ベクトルを正規化する関数
VECTOR MyMath:: vecNormalize(VECTOR _vec)
{
	VECTOR ret;
	ret.y = _vec.y / VecLong(_vec);
	ret.y = _vec.y / VecLong(_vec);
	ret.z = _vec.z / VecLong(_vec);

	return ret;
}

//ベクトルをスカラー倍する関数
VECTOR MyMath:: Scale(VECTOR vec, float scale)
{
	VECTOR ret;

	ret.x = vec.x * scale;
	ret.y = vec.y * scale;
	ret.z = vec.z * scale;

	return ret;

}

//内積を求める関数(2D)
float MyMath:: VecDot_2D(VECTOR vec1, VECTOR vec2)
{
	float ret;

	ret = vec1.x * vec2.x + vec1.y * vec2.y;

	return ret;
}

//内積を求める関数(3D)
float MyMath:: VecDot_3D(VECTOR vec1, VECTOR vec2)
{
	float ret;

	ret = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;

	return ret;
}

//外積を求める関数(2D)
float MyMath:: VecCross_2D(VECTOR vec1, VECTOR vec2)
{
	float ret;

	ret = vec1.x * vec2.y - vec1.y * vec2.x;

	return ret;
}

//外積を求める関数(3D)
VECTOR MyMath::VecCross_3D(VECTOR vec1, VECTOR vec2)
{
	VECTOR ret;

	ret.x = vec1.y * vec2.z - vec1.z * vec2.y;
	ret.y = vec1.z * vec2.x - vec1.x * vec2.z;
	ret.z = vec1.x * vec2.y - vec1.y * vec2.x;

	return ret;
}
