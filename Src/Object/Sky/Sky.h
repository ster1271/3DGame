#pragma once
#include "../object.h"

class CSky :public CObject
{
private:
	VECTOR m_Scale;

public:
	//コンストラクタ・デストラクタ
	CSky();
	~CSky();

	//初期化
	void Init();

	//描画
	void Draw();

	//通常処理
	void Step(VECTOR vForcus, float fRot);

	//ループ処理
	void Loop();

	//移動処理
	void SetSkyPos(VECTOR vF, VECTOR dir);
};
