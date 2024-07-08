#pragma once
#include <DxLib.h>
#include <math.h>
#include "../Object/Model/Model.h"
#include "../Shot/ShotManager.h"
#include "../Input/Input.h"
#include "../MyLibrary/MyLibrary.h"
#include "../Draw3D/Draw3D.h"

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

	int HeadHndl;			//頭部のモデル
	VECTOR vHeadPos;		//頭部の座標
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

	//向いている方向チェック
	void CheckDir(bool *Dir);

	//座標取得
	inline VECTOR GetPosition() { return m_vPos; }

	//NextPos取得
	inline VECTOR GetNextPos() { return NextPos; }

	//Y軸角度取得
	inline VECTOR GetRotate() { return m_vRot; }

	//Y軸角度取得

	inline float GetRotateY() { return m_vRot.y; }
	

	//プレイヤーの更新座標取得
	void SetPosX(VECTOR NewPos);
	//プレイヤーの更新座標取得
	void SetPosY(VECTOR NewPos);
	//プレイヤーの更新座標取得
	void SetPosZ(VECTOR NewPos);


};
