#pragma once
#include "DxLib.h"

class  CDraw3D
{
public:

	//3Dのボックス表示関数
	//第1引数：座標(中心でなくてもよい)
	//第2引数：表示したいボックスのサイズ
	//第3引数：中心座標でない時のズレ(すでに中心の時は書かなくてよい)
	static void DrawBox3D(VECTOR Pos, VECTOR Size, VECTOR Gap = { 0.0f, 0.0f, 0.0f });
	
};


