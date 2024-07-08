#include <DxLib.h>
#include "CameraManager.h"
#include "../Input/Input.h"

static const VECTOR DEFAULT_EYE_POS = { 0.0f, 0.0f, -20.0f };
static const VECTOR DEFAULT_FORCUS_POS = { 0.0f, 0.0f, 0.0f };
static const VECTOR DEFAULT_UP_VEC = { 0.0f, 1.0f, 0.0f };


//-------------------------
//コンストラクタ
//-------------------------

CCameraManager::CCameraManager()
{
	//初期にゲーム中のカメラにする
	eCurrentCameraID = CAMERA_ID_PALY;
	PlayerRotateY = 0.0f;
}


//-------------------------
//デストラクタ
//-------------------------
CCameraManager::~CCameraManager()
{

}

//-------------------------
//初期化
//-------------------------
void CCameraManager::Init()
{
	cPlayCam.Init(DEFAULT_EYE_POS, DEFAULT_FORCUS_POS, DEFAULT_UP_VEC);
	cDebugCam.Init(DEFAULT_EYE_POS);
}

//-------------------------
//初期化
//-------------------------
void CCameraManager::Init(VECTOR vPos, VECTOR vForcus, VECTOR vUp)
{
	cPlayCam.Init(vPos, vForcus, vUp);
	cDebugCam.Init(vPos);
}

//-------------------------
//終了処理
//-------------------------
void CCameraManager::Exit()
{
}

//-------------------------
//毎フレーム呼ぶ処理
//-------------------------
void CCameraManager::Step(VECTOR vForcus, VECTOR fRot)
{
	//カメラのタイプに合わせて、更新処理を変更する
	switch (eCurrentCameraID)
	{
	case CAMERA_ID_PALY:
		cPlayCam.Step(vForcus, fRot);
		cPlayCam.Update();
		break;

	case CAMERA_ID_DEBUG:
		cDebugCam.Step();
		cDebugCam.Update();
		
	default:
		break;
	}
	
}


//描画
void CCameraManager::Draw()
{
	switch (eCurrentCameraID)
	{
	case CCameraManager::CAMERA_ID_DEBUG:

		cDebugCam.Draw();
		break;
	default:
		break;
	}
}

//-------------------------
//カメラのニア・ファー設定
//-------------------------
void CCameraManager::SetNearFar(float fNear, float fFar)
{
	SetCameraNearFar(fNear, fFar);
}

//カメラタイプ変更
void CCameraManager::ChangeCamera(tagCAMERA_ID ID)
{
	// ID変更
	eCurrentCameraID = ID;

	// 変更後にカメラを初期化
	switch (eCurrentCameraID)
	{
	case CCameraManager::CAMERA_ID_DEBUG:
		// デバッグカメラ初期化
		cDebugCam.Init(cPlayCam.GetPlayCameraPos(), PlayerRotateY);
	default:
		break;
	}

	return;
}


//プレイヤーの角度を保存
void CCameraManager::SetPlayerRot(float vRot)
{
	PlayerRotateY = vRot;
}