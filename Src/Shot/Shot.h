#pragma once
#include <DxLib.h>

const int SHOTRADIUS	(1);
const float GRAVITY		(0.03f);

class CShot
{
private:
	VECTOR m_vPos;			//座標
	VECTOR m_vSpeed;		//移動速度
	float Yspeed;			//Yスピード
	float m_Radius;			//モデルの半径
	int iHndl;				//モデルのハンドル
	bool isActive;			//生存フラグ


public:
	//コンストラクタ・デストラクタ
	CShot();
	~CShot();

	//初期化
	void Init();

	//データロード
	void Load(int iMdlHndl);

	//終了処理
	void Exit();

	//毎フレーム呼ぶ処理
	void Step(VECTOR Pos);

	//描画処理
	void Draw();

	//リクエスト
	//m_vPos		： 初期座標
	//m_vSpeed	： 移動速度(方向ベクトルで)
	//return	： true = リクエスト成功, false = 失敗
	bool RequestShot(const VECTOR& vPos, const VECTOR& vSpeed, const float& YSpeed);

	//生存判定
	//return 　： true = 生存, false = 失敗
	bool IsActive() { return isActive; }

	//座標取得
	VECTOR GetPosition(VECTOR& vPos)
	{
		return vPos = m_vPos;
	}


	//モデルの半径取得
	float GetRadius()
	{
		return m_Radius;
	}

	//当たり判定の処理
	void HitCalc()
	{
		//当たったらフラグをおる
		isActive = false;
	}
};