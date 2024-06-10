#include "Draw3D.h"
#include "math.h"
#include "../MyLibrary/MyLibrary.h"

//3Dのボックス表示関数
//第1引数：座標(中心でなくてもよい)
//第2引数：表示したいボックスのサイズ
//第3引数：中心座標でない時のズレ(すでに中心の時は書かなくてよい)
void CDraw3D::DrawBox3D(VECTOR Pos, VECTOR Size, VECTOR Gap)
{
	//サイズの半分をとる
	VECTOR HalfSize = VScale(Size, 0.5f);

	//中心座標へ変更する
	Pos = VAdd(Pos, Gap);

	/*上の面*/
	//左から右(手前)
	DrawLine3D(VGet(Pos.x - HalfSize.x, Pos.y + HalfSize.y, Pos.z - HalfSize.z), VGet(Pos.x + HalfSize.x, Pos.y + HalfSize.y, Pos.z - HalfSize.z), GetColor(255, 0, 0));
	//左から右(奥)
	DrawLine3D(VGet(Pos.x - HalfSize.x, Pos.y + HalfSize.y, Pos.z + HalfSize.z), VGet(Pos.x + HalfSize.x, Pos.y + HalfSize.y, Pos.z + HalfSize.z), GetColor(255, 0, 0));
	//左手前から左奥
	DrawLine3D(VGet(Pos.x - HalfSize.x, Pos.y + HalfSize.y, Pos.z - HalfSize.z), VGet(Pos.x - HalfSize.x, Pos.y + HalfSize.y, Pos.z + HalfSize.z), GetColor(255, 0, 0));
	//右手前から右奥
	DrawLine3D(VGet(Pos.x + HalfSize.x, Pos.y + HalfSize.y, Pos.z - HalfSize.z), VGet(Pos.x + HalfSize.x, Pos.y + HalfSize.y, Pos.z + HalfSize.z), GetColor(255, 0, 0));

	/*下の面*/
	//左から右(手前)
	DrawLine3D(VGet(Pos.x - HalfSize.x, Pos.y - HalfSize.y, Pos.z - HalfSize.z), VGet(Pos.x + HalfSize.x, Pos.y - HalfSize.y, Pos.z - HalfSize.z), GetColor(255, 0, 0));
	//左から右(奥)
	DrawLine3D(VGet(Pos.x - HalfSize.x, Pos.y - HalfSize.y, Pos.z + HalfSize.z), VGet(Pos.x + HalfSize.x, Pos.y - HalfSize.y, Pos.z + HalfSize.z), GetColor(255, 0, 0));
	//左手前から左奥
	DrawLine3D(VGet(Pos.x - HalfSize.x, Pos.y - HalfSize.y, Pos.z - HalfSize.z), VGet(Pos.x - HalfSize.x, Pos.y - HalfSize.y, Pos.z + HalfSize.z), GetColor(255, 0, 0));
	//右手前から右奥
	DrawLine3D(VGet(Pos.x + HalfSize.x, Pos.y - HalfSize.y, Pos.z - HalfSize.z), VGet(Pos.x + HalfSize.x, Pos.y - HalfSize.y, Pos.z + HalfSize.z), GetColor(255, 0, 0));

	/*側面*/
	//手前左(上から下)
	DrawLine3D(VGet(Pos.x - HalfSize.x, Pos.y + HalfSize.y, Pos.z - HalfSize.z), VGet(Pos.x - HalfSize.x, Pos.y - HalfSize.y, Pos.z - HalfSize.z), GetColor(255, 0, 0));
	//手前右(上から下)
	DrawLine3D(VGet(Pos.x + HalfSize.x, Pos.y + HalfSize.y, Pos.z - HalfSize.z), VGet(Pos.x + HalfSize.x, Pos.y - HalfSize.y, Pos.z - HalfSize.z), GetColor(255, 0, 0));
	//奥左(上から下)
	DrawLine3D(VGet(Pos.x - HalfSize.x, Pos.y + HalfSize.y, Pos.z + HalfSize.z), VGet(Pos.x - HalfSize.x, Pos.y - HalfSize.y, Pos.z + HalfSize.z), GetColor(255, 0, 0));
	//奥右(上から下)
	DrawLine3D(VGet(Pos.x + HalfSize.x, Pos.y + HalfSize.y, Pos.z + HalfSize.z), VGet(Pos.x + HalfSize.x, Pos.y - HalfSize.y, Pos.z + HalfSize.z), GetColor(255, 0, 0));
}