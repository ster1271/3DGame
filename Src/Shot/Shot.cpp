#include "Shot.h"
#include "../Player/Player.h"


//----------------------------------------
//コンストラクタ
//----------------------------------------
CShot::CShot()
{
	//初期化
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vSpeed, 0, sizeof(VECTOR));
	iHndl = -1;
	isActive = false;
	m_Radius = 0;

}

//----------------------------------------
//デストラクタ
//----------------------------------------
CShot::~CShot()
{
	//念のため
	Exit();
}

//----------------------------------------
//初期化
//----------------------------------------
void CShot::Init()
{
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vSpeed, 0, sizeof(VECTOR));
	iHndl = -1;
	isActive = false;
	m_Radius = SHOTRADIUS;

}


//----------------------------------------
//終了処理
//----------------------------------------
void CShot::Exit()
{
	//モデルハンドル解放
	if (iHndl != -1)
	{
		MV1DeleteModel(iHndl); 
		iHndl = -1;
	}
}


//----------------------------------------
//データロード
//----------------------------------------
void CShot::Load(int iMdlHndl)
{
	if (iHndl == -1)
	{
		iHndl = MV1DuplicateModel(iMdlHndl);
	}
}


//----------------------------------------
//描画処理
//----------------------------------------
void CShot::Draw()
{
	if (isActive)
	{
		MV1DrawModel(iHndl);

		/*VECTOR vPos = m_vPos;*/
		
		/*DrawFormatString(500, 0, GetColor(255, 0, 0), "X座標：%f", m_vPos.x);
		DrawFormatString(500, 15, GetColor(255, 0, 0), "Y座標：%f", m_vPos.y);
		DrawFormatString(500, 30, GetColor(255, 0, 0), "Z座標：%f", m_vPos.z);*/
		/*DrawSphere3D(vPos, m_Radius, 16, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);*/

	}

	
}


//----------------------------------------
//毎フレーム呼ぶ処理
//----------------------------------------
void CShot::Step(VECTOR Pos)
{
	if (!isActive) return;

	//座標に速度を加算
	m_vPos = VAdd(m_vPos, m_vSpeed);
	m_vPos.y += Yspeed;
	Yspeed -= GRAVITY;


	//一定範囲を超えたら消す
	float fLength =	600;

	if (m_vPos.x > Pos.x + fLength || m_vPos.x < Pos.x -fLength
		|| m_vPos.z > Pos.z + fLength || m_vPos.z < Pos.z - fLength
		|| m_vPos.y < 0.0f)
	{
		isActive = false;
	}

	//座標更新
	MV1SetPosition(iHndl, m_vPos);
	MV1SetScale(iHndl, VGet(0.05f, 0.05f, 0.05f));
}


//----------------------------------------
//リクエスト
//----------------------------------------
bool CShot::RequestShot(const VECTOR &vPos, const VECTOR &vSpeed , const float&YSpeed)
{
	//すでに発射されている
	if (isActive) return false;

	m_vPos = vPos;
	m_vSpeed = vSpeed;
	Yspeed = YSpeed;
	isActive = true;

	return true;
	
}


