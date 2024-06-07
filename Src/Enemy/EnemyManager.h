#pragma once
#include "Enemy.h"

#define ENEMY_NUM	(1)

class CEnemyManager
{
private:
	CEnemyBase cEnemyBace[ENEMY_NUM];

	int m_iWaitCnt;		//敵が生成されるまでの時間

public:
	//コンストラクタ・デストラクタ
	CEnemyManager();
	~CEnemyManager();

	//初期化
	void Init();

	//データロード
	void Load();

	//終了処理
	void Exit();

	//毎フレーム呼ぶ処理
	void Step();

	//描画処理
	void Draw();

	//敵情報取得
	inline CEnemyBase& GetEnemy(int iID) { return cEnemyBace[iID]; }

private:
	//敵リクエスト
	void RequestEnemy();
};
