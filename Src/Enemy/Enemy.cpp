#include"Enemy.h"
#include <math.h>

//--------------------------------------
//コンストラクタ
//--------------------------------------
CEnemyBase::CEnemyBase()
{
	//ひとまず初期化
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vSpeed, 0, sizeof(VECTOR));
	m_iHndl = -1;
	m_Life = MAX_LIFE;
	m_isActive = false;
	HitCount = 0;
	m_Radius = 0;
}

//--------------------------------------
//デストラクタ
//--------------------------------------
CEnemyBase::~CEnemyBase()
{
	//本来は必要ないが念のため
	Exit();
}

//--------------------------------------
//初期化
//--------------------------------------
void CEnemyBase::Init()
{
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vSpeed, 0, sizeof(VECTOR));
	m_iHndl = -1;
	m_isActive = false;
	m_Radius = ENEMYRADIUS;
}

//--------------------------------------
//終了処理
//--------------------------------------
void CEnemyBase::Exit()
{
	//モデルハンドル解放
	if (m_iHndl != -1)
	{
		MV1DeleteModel(m_iHndl);
		m_iHndl = -1;
	}
}

//--------------------------------------
//データロード
//--------------------------------------

void CEnemyBase::Load(int iMdlHndl)
{
	if (m_iHndl == -1)
	{
		m_iHndl = MV1DuplicateModel(iMdlHndl);
		MV1SetScale(m_iHndl, VGet(5.0f, 5.0f, 5.0f));
	}
}


//--------------------------------------
//描画処理
//--------------------------------------
void CEnemyBase::Draw()
{
	if (m_isActive)
	{
		MV1DrawModel(m_iHndl);
		VECTOR vPos = m_vPos;
		vPos.y += m_Radius;

		//デバック用---------------------------------------------------------------------
		int R, G, B;
		B = 255;
		R = G = 0;


		switch (HitCount)
		{
		//一回も当たってないとき
		case 0:
			break;
			B = 255;
			R = G = 0;
		//一回当たったとき
		case 1:
			G = 255;
			R = B = 0;

			break;
		//二回当たったとき
		case 2:
			R = 255;
			G = B = 0;

			break;

		default:
			break;
		}
		DrawSphere3D(vPos, m_Radius, 16, GetColor(R, G, B), GetColor(R, G, B), false);
		//デバック用---------------------------------------------------------------------
	}

}


//--------------------------------------
//リクエスト
//--------------------------------------
bool CEnemyBase::RequestEnemy(const VECTOR &vPos, const VECTOR &vSpeed)
{
	//すでに出現している
	if (m_isActive)
	{
		return false;
	}

	m_vPos = vPos;
	m_vSpeed = vSpeed;
	m_isActive = true;

	//一度座標更新しておく
	MV1SetPosition(m_iHndl, m_vPos);
	return true;
}

//--------------------------------------
//毎フレーム呼ぶ処理
//--------------------------------------
void CEnemyBase::Step()
{
	if (!m_isActive)
	{
		return;
	}

	//座標に速度を加算
	m_vPos = VAdd(m_vPos, m_vSpeed);
	//一定範囲を超えたら消す
	float fLength = 300.0f;
	if (m_vPos.x > fLength || m_vPos.x < -fLength
		|| m_vPos.z > fLength || m_vPos.z < -fLength)
	{
		m_isActive = false;
	}

	//座標更新
	MV1SetPosition(m_iHndl, m_vPos);
}




