#pragma once
#include <DxLib.h>
#include "../SoundManager/SoundManager.h"

const int ENEMYRADIUS		(5);
const int MAX_LIFE			(3);


class CEnemyBase
{
private:
	VECTOR m_vPos;			//座標
	VECTOR m_vSpeed;		//移動速度
	int m_Life;				//敵のライフ
	float m_Radius;			//モデルの半径
	int m_iHndl;			//モデルハンドル
	bool m_isActive;		//生存フラグ

	int HitCount;			//弾の当たった回数格納

public:
	//コンストラクタ・デストラクタ
	CEnemyBase();
	~CEnemyBase();

	//初期化
	void Init();

	//データロード
	void Load(int iMdlHndl);

	//終了処理
	void Exit();

	//毎フレーム呼ぶ処理
	void Step();

	//描画処理
	void Draw();

	//リクエスト
	bool RequestEnemy(const VECTOR& vPos, const VECTOR& vSpeed);

	//生存判定
	bool IsActive() { return m_isActive; }

	//座標取得
	void GetPosition(VECTOR &vPos) { vPos = m_vPos; }

	//モデルの半径取得
	float GetRadius()
	{
		return m_Radius;
	}

	//当たり判定の処理
	void HitCalc()
	{
		CSoundManager::Play(CSoundManager::SOUNDID_SE_EXPLORE);
		m_Life -= 1;
		m_vPos.z += 2.0f;
		HitCount++;

		//ライフがなくなったらフラグをおる
		if (m_Life <= 0)
		{
			HitCount = 0;
			m_isActive = false;
		}
	}

};