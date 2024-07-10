#pragma once
#include "Shot.h"


#define PL_SHOT_NUM	(3)

class CShotManager
{
private:
	//プレイヤーのショット
	//メモリの動的確保が望ましい
	CShot cPlayerShot[PL_SHOT_NUM];

public:
	//コンストラクタ・デストラクタ
	CShotManager();
	~CShotManager();

	//初期化
	void Init();
	//データロード
	void Load();
	//終了処理
	void Exit();
	//繰り返し行う処理
	void Step(VECTOR Pos);
	//描画処理
	void Draw();

	//プレイヤーのショット情報取得
	inline CShot& GetPlayerShot(int iID) { return cPlayerShot[iID]; }

	//プレイヤーのショットリクエスト
	void RequestPlayerShot(const VECTOR& vPos, const VECTOR& vSpeed, const float& YSpeed);
};