#pragma once
#include <DxLib.h>
#include "../Shot/ShotManager.h"
#include "../Object/Model/Model.h"

//タンククラス(発射部分のみ)
class CTank_H : public CModel
{
private:
	//プレイヤーの状態
	enum tagPlayerState
	{
		PLAYER_STATE_NORMAL,	//待機・歩き中
		PLAYER_STATE_JUMP,		//ジャンプ中

		PLAYER_STATE_NUM
	};

	VECTOR vSpeed;			//移動速度
	tagPlayerState eState;	//プレイヤーの状態

public:
	//コンストラクタ・デストラクタ
	CTank_H();
	~CTank_H();

	//初期化
	void Init();
	void Init(VECTOR vPos, VECTOR vRot);

	//データ関連のロード
	void Load();

	//データ関連の破棄
	void Delete();

	//終了処理
	void Exit();

	//毎フレーム呼ぶ処理
	void Step(CShotManager& cShotManager);


	//座標取得
	inline VECTOR GetPosition() { return m_vPos; }
	//Y軸角度取得
	inline float GetRotateY() { return m_vRot.y; }

};

