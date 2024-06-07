#include "DebugCamera.h"
#include "../Input/Input.h"
#include <math.h>
#include "../MyLibrary/MyLibrary.h"

//カメラの距離
#define CAMERA_LENGTH	(30.0f)

//視点の高さ
#define CAMERA_OFFSET_Y	(10.0f)

//注視点の高さ
#define FORCUS_OFFSET_Y	(10.0f)

//カメラの移動速度
#define CAMERA_MOVE_SPEED	(1.0f)

//カメラの回転速度
#define CAMERA_ROTATE_SPEED	(0.02f)

CDebugCamera::CDebugCamera()
{
	//初期化
	memset(&CameraPos, 0, sizeof(VECTOR));
	memset(&vRot, 0, sizeof(VECTOR));
}

CDebugCamera::~CDebugCamera()
{

}


//初期化
void CDebugCamera::Init()
{
	CameraPos = VGet(0.0f, 0.0f, 1.0f);
	vRot = VGet(0.0f, 0.0f, 0.0f);

}
void CDebugCamera::Init(VECTOR vPos, float fRot)
{
	CameraPos = vPos;
	vRot.y = fRot + DX_PI_F;
}

//毎フレーム呼ぶ処理
void CDebugCamera::Step()
{
	//カメラの移動
	float fSpd = 0.0f;
	if (CInput::IsKeyKeep(KEY_INPUT_W))
	{
		fSpd = CAMERA_MOVE_SPEED;
	}
	else if (CInput::IsKeyKeep(KEY_INPUT_S))
	{
		fSpd = -CAMERA_MOVE_SPEED;
	}
	float fRot = 0.0f;
	if (CInput::IsKeyKeep(KEY_INPUT_A)) {
		fSpd = -CAMERA_MOVE_SPEED;
		fRot = 90.0f * DX_PI_F / 180.0f;
	}
	else if (CInput::IsKeyKeep(KEY_INPUT_D)) {
		fSpd = CAMERA_MOVE_SPEED;
		fRot = 90.0f * DX_PI_F / 180.0f;
	}

	// カメラの向きの操作
	if (CInput::IsKeyKeep(KEY_INPUT_UP)) {
		vRot.x -= CAMERA_ROTATE_SPEED;
	}
	else if (CInput::IsKeyKeep(KEY_INPUT_DOWN)) {
		vRot.x += CAMERA_ROTATE_SPEED;
	}
	else if (CInput::IsKeyKeep(KEY_INPUT_LEFT)) {
		vRot.y -= CAMERA_ROTATE_SPEED;
	}
	else if (CInput::IsKeyKeep(KEY_INPUT_RIGHT)) {
		vRot.y += CAMERA_ROTATE_SPEED;
	}

	// 入力したキー情報とカメラの角度から、移動速度を求める
	CameraPos.x += sinf(vRot.y + fRot) * fSpd;
	CameraPos.z += cosf(vRot.y + fRot) * fSpd;
}

//更新したデータを反映させる
void CDebugCamera::Update()
{
	SetCameraPositionAndAngle(CameraPos, vRot.x, vRot.y, vRot.z);
}

//-----------------------
//デバックカメラ時の表示
//-----------------------
void CDebugCamera::Draw()
{
	DrawString(0, 0, "デバックカメラモード", GetColor(255, 255, 255));
	DrawFormatString(0, 15, GetColor(255, 255, 255), "座標X：%f, 座標Y：%f, 座標Z：%f", CameraPos.x, CameraPos.y, CameraPos.z);
}