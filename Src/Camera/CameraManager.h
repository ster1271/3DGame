#pragma once
#include "PlayCamera.h"
#include "DebugCamera.h"

class CCameraManager
{
public:

	//カメラのタイプ
	enum tagCAMERA_ID
	{
		CAMERA_ID_PALY,		//ゲーム中のカメラ
		CAMERA_ID_DEBUG,    //デバッグ用のカメラ(今後作成)

		CAMERA_ID_NUM
	};

private:
	CPlayCamera cPlayCam;			//プレイヤーカメラ
	CDebugCamera cDebugCam;			//デバックカメラ
	tagCAMERA_ID eCurrentCameraID;	//現在のカメラID

	float			PlayerRotateY;	//プレイヤーの角度

public:
	//コンストラクタ・デストラクタ
	CCameraManager();
	~CCameraManager();

	void Init();
	void Init(VECTOR vPos, VECTOR vFocus, VECTOR vUp);

	//終了処理
	void Exit();

	//更新処理
	void Step(VECTOR vForcus, VECTOR fRot);

	//描画
	void Draw();

	//カメラのニア・ファー設定
	void SetNearFar(float fNear, float fFar);

	//カメラのタイプ変更
	void ChangeCamera(tagCAMERA_ID ID);

	//現在のカメラタイプ取得
	tagCAMERA_ID GetCameraID() { return eCurrentCameraID; }

	//プレイヤーの座標と角度を保存
	void SetPlayerRot(float vRot);

};

