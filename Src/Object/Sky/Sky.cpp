#include "Sky.h"
#include <math.h>

//コンストラクタ
CSky::CSky()
{
	m_Scale = VGet(0.0f, 0.0f, 0.0f);
}

//デストラクタ
CSky::~CSky()
{

}

//初期化
void CSky::Init()
{
	cPos = VGet(0.0f, 0.0f, 0.0f);
	m_Scale = VGet(2.0f, 2.0f, 2.0f);
	iHndl = MV1LoadModel("Data/Sky/きれいな空(・ω・)_by西山.x");

	MV1SetPosition(iHndl, cPos);
	MV1SetScale(iHndl, VGet(1.0f, 1.0f, 1.0f));
}

//描画
void CSky::Draw()
{
	MV1DrawModel(iHndl);
}

//通常処理
void CSky::Step(VECTOR vForcus, float fRot)
{
	cRotate.y += 0.0005f;

	VECTOR vDir;
	vDir.x = sinf(fRot) * 30.0f;
	vDir.z = cosf(fRot) * 30.0f;

	//視点の高さは固定
	vDir.y = 10.0f;

	SetSkyPos(vForcus, vDir);
}

//ループ処理
void CSky::Loop()
{
	MV1SetPosition(iHndl, cPos);
	MV1SetRotationXYZ(iHndl, cRotate);
	MV1SetScale(iHndl, m_Scale);
}

//移動処理
void CSky::SetSkyPos(VECTOR vF, VECTOR dir)
{
	cPos = VAdd(vF, dir);
}