#include "ShotManager.h"
#include "../SoundManager/SoundManager.h"

//定義
static const char PLSHOT_MODEL_PATH[] = { "Data/shot/plshot.x" };

//------------------------------------
//コンストラクタ
//------------------------------------
CShotManager::CShotManager()
{

}


//------------------------------------
//デストラクタ
//------------------------------------
CShotManager::~CShotManager()
{

}


//------------------------------------
//初期化
//------------------------------------
void CShotManager::Init()
{
	for (int i = 0; i < PL_SHOT_NUM; i++)
	{
		cPlayerShot[i].Init();
	}
}


//------------------------------------
//ロード
//------------------------------------
void CShotManager::Load()
{
	//オリジナルモデルの読み込み
	int iHndl = MV1LoadModel(PLSHOT_MODEL_PATH);
	//モデルの複製
	for (int i = 0; i < PL_SHOT_NUM; i++)
	{
		cPlayerShot[i].Load(iHndl);
	}
	MV1DeleteModel(iHndl);
}


//------------------------------------
//終了処理
//------------------------------------
void CShotManager::Exit()
{
	for (int i = 0; i < PL_SHOT_NUM; i++)
	{
		cPlayerShot[i].Exit();
	}
}

//------------------------------------
//毎フレーム呼ぶ処理
//------------------------------------
void CShotManager::Step(VECTOR Pos)
{
	for (int i = 0; i < PL_SHOT_NUM; i++)
	{
		cPlayerShot[i].Step(Pos);
	}

	
}


//------------------------------------
//更新処理
//------------------------------------
void CShotManager::Draw()
{
	for (int i = 0; i < PL_SHOT_NUM; i++)
	{
		cPlayerShot[i].Draw();
	}

	

}


//------------------------------------
//プレイヤーのショットリクエスト
//------------------------------------
void CShotManager::RequestPlayerShot(const VECTOR& vPos, const VECTOR& vSpeed, const float& YSpeed)
{
	for (int i = 0; i < PL_SHOT_NUM; i++)
	{
		if (cPlayerShot[i].RequestShot(vPos, vSpeed, YSpeed))
		{
			CSoundManager::Play(CSoundManager::SOUNDID_SE_PLSHOT);
			break;
		}
	}
}

