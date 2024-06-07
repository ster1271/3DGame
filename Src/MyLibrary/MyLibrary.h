#pragma once

class MyMath
{
public:
	 //ベクトルの足し算
	static	VECTOR AddVec(VECTOR _vec1, VECTOR _vec2);

	//ベクトルの引き算
	static VECTOR SubVec(VECTOR _vec1, VECTOR _vec2);

	//ベクトルを生成する関数
	static VECTOR VecCreate(VECTOR start, VECTOR end);

	//ベクトルの長さを計算する関数
	static float VecLong(VECTOR vec);

	//ベクトルを正規化する関数
	static VECTOR vecNormalize(VECTOR vec);

	//ベクトルをスカラー倍する関数
	static VECTOR Scale(VECTOR vec, float scale);

	//内積を求める関数(2D)
	static float VecDot_2D(VECTOR vec1, VECTOR vec2);

	//内積を求める関数(3D)
	static float VecDot_3D(VECTOR vec1, VECTOR vec2);

	//外積を求める関数(2D)
	static float VecCross_2D(VECTOR vec1, VECTOR vec2);

	//外積を求める関数(3D)
	static VECTOR VecCross_3D(VECTOR vec1, VECTOR vec2);
};

