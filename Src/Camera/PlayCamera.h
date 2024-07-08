#pragma once
#include <DxLib.h>

//カメラクラス
class CPlayCamera
{
private:
	VECTOR CameraPos;			//カメラの視点
	VECTOR ForcusPos;			//カメラの注視点
	VECTOR Up;					//カメラの上方向

public:
	//コンストラクタ・デストラクタ
	CPlayCamera();
	~CPlayCamera();

	//初期化
	void Init();
	void Init(VECTOR vPos, VECTOR vForcusPos, VECTOR vUp);

	//毎フレーム呼ぶ処理
	void Step(VECTOR vForcus, VECTOR fRot);

	//更新したデータを反映させる
	void Update();

	//カメラの座標取得
	VECTOR GetPlayCameraPos() { return CameraPos; }

	//カメラの注視点を取得
	VECTOR GetForcusPosition() { return ForcusPos; }

	//カメラの上方向ベクトルを取得
	VECTOR GetCameraUp() { return Up; }
};



