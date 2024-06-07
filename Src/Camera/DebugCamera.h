#pragma once
#include <DxLib.h>
#include "../Player/Player.h"


//カメラクラス
class CDebugCamera
{
private:
	VECTOR CameraPos;	//視点
	VECTOR vRot;		//カメラの角度

public:
	//コンストラクタ・デストラクタ
	CDebugCamera();
	~CDebugCamera();

	//初期化
	void Init();
	void Init(VECTOR vPos, float fRot = 0.0f);

	//毎フレーム呼ぶ処理
	void Step();

	//更新したデータを反映させる
	void Update();

	//デバックカメラ時の表示
	void Draw();
};