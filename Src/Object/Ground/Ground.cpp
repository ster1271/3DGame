#include "Ground.h"

//コンストラクタ
CGround::CGround()
{

}

//デストラクタ
CGround::~CGround()
{

}

//初期化
void CGround::Init()
{
	cPos = VGet(0.0f, 0.0f, 0.0f);
	iHndl = MV1LoadModel("Data/field/field.x");
	MV1SetPosition(iHndl, cPos);
	MV1SetScale(iHndl, VGet(0.1f, 0.1f, 0.1f));
}

//描画
void CGround::Draw()
{
	MV1DrawModel(iHndl);
}