#include "Draw3D.h"
#include "math.h"
#include "../MyLibrary/MyLibrary.h"

//3Dのボックス表示関数
//第1引数：座標(中心でなくてもよい)
//第2引数：表示したいボックスのサイズ
//第3引数：中心座標でない時のズレ(すでに中心の時は書かなくてよい)
void CDraw3D::DrawBox3D(VECTOR Pos, VECTOR Size, VECTOR Gap = { 0.0f, 0.0f, 0.0f })
{
	//サイズの半分をとる
	VECTOR HalfSize = VScale(Size, 0.5f);

	//中心座標へ変更する
	Pos = VAdd(Pos, Gap);

	/*上の面*/
	//左上から右上(手前)
	DrawLine3D(VGet(Pos.x - HalfSize.x, Pos.y + HalfSize.y, Pos.z - HalfSize.z), VGet(Pos.x + HalfSize.x, Pos.y + HalfSize.y, Pos.z - HalfSize.z), GetColor(255, 0, 0));
}