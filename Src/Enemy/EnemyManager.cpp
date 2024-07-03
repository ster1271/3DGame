#include "EnemyManager.h"

//定義
static const char ENEMY_MODEL_PATH[] = { "Data/enemy/enemy.pmx" };
static const int WAIT_TIME = 10;		//敵が再登場するまでの時間

//コンストラクタ
CEnemyManager::CEnemyManager()
{
	m_iWaitCnt = 0;
}

//デストラクタ
CEnemyManager::~CEnemyManager()
{

}

//初期化
void CEnemyManager::Init()
{
	m_iWaitCnt = WAIT_TIME;
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		cEnemyBace[i].Init();
	}
}

//データロード
void CEnemyManager::Load()
{
	//オリジナルデータ読み込み	
	int iHndl = MV1LoadModel(ENEMY_MODEL_PATH);
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		cEnemyBace[i].Load(iHndl);
	}
}

//終了処理
void CEnemyManager::Exit()
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		cEnemyBace[i].Exit();
	}
}

//毎フレーム呼ぶ処理
void CEnemyManager::Step()
{
	int iEnemyCnt = 0;	//敵の出現数
	//敵の移動処理
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		cEnemyBace[i].Step();
		if (cEnemyBace[i].IsActive())
		{
			iEnemyCnt++;
		}
	}

	//敵の出現
	m_iWaitCnt--;
	if (m_iWaitCnt < 0 || iEnemyCnt == 0)
	{
		RequestEnemy();
		m_iWaitCnt = WAIT_TIME;
	}
}

//描画処理
void CEnemyManager::Draw()
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		cEnemyBace[i].Draw();
	}
}


//敵リクエスト
void CEnemyManager::RequestEnemy()
{
	VECTOR vPos = VGet((float)GetRand(200) - 100.0f, 0, 200.0f);
	VECTOR vSpeed = VGet(0.0f, 0.0f, -0.1f);
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (cEnemyBace[i].RequestEnemy(vPos, vSpeed))
		{
			break;
		}
	}
}