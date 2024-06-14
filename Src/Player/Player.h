#pragma once
#include <DxLib.h>
#include "../Shot/ShotManager.h"
#include "../Object/Model/Model.h"

class CPlayer : public CModel
{
private:
	//プレイヤーの状態
	enum tagPlayerState
	{
		PLAYER_STATE_NORMAL,	//待機・歩き中
		PLAYER_STATE_JUMP,		//ジャンプ中

		PLAYER_STATE_NUM
	};

	//座標のズレ
	VECTOR PosGap;

	int HeadHndl;
	VECTOR vHeadRot;		//頭部の回転

	VECTOR vSpeed;			//移動速度
	tagPlayerState eState;	//プレイヤーの状態

public:
	//コンストラクタ・デストラクタ
	CPlayer();
	~CPlayer();

	//初期化
	void Init();
	void Init(VECTOR vPos, VECTOR vRot);

	//データ関連のロード
	void Load();

	//データ関連の破棄
	void Delete();

	//終了処理
	void Exit();

	//描画処理
	void Draw();

	//更新処理
	void Update();

	//毎フレーム呼ぶ処理
	void Step(CShotManager& cShotManager);

	//座標取得
	inline VECTOR GetPosition() { return m_vPos; }

	//Y軸角度取得
	inline float GetRotateY() { return m_vRot.y; }

	//X座標取得
	inline float GetPositionX() { return m_vPos.x; }

	//Y座標取得
	inline float GetPositionY() { return m_vPos.y; }

	//Z座標取得
	inline float GetPositionY() { return m_vPos.z; }

	//差分取得(X)
	inline float GetGapPositionX() { return PosGap.x; }

	//差分取得(Y)
	inline float GetGapPositionY() { return PosGap.y; }

	//差分取得(Z)
	inline float GetGapPositionZ() { return PosGap.y; }

	//プレイヤーのめり込み修正
	void SetPos(VECTOR GAP);

};
