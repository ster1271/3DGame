#include "PlayScene.h"
#include "../Input/Input.h"
#include "../SoundManager/SoundManager.h"


//定義関連----------------------------------

//------------------------------------------


//------------------------------------------
//コンストラクタ
//------------------------------------------
CPlayScene::CPlayScene()
{
	//ひとまず初期化にしておく
	eSceneID = PLAY_SCENE_INIT;
}


//------------------------------------------
//デストラクタ
//------------------------------------------
CPlayScene::~CPlayScene()
{
	//念の為
	Exit();
}

//------------------------------------------
//毎フレーム呼ぶ処理
//------------------------------------------
int CPlayScene::Loop()
{
	int iRet = eSceneID == CPlayScene::PLAY_SCENE_END ? 1 : 0;

	//関数ポインタを作成
	void (CPlayScene:: * PlayScene[])() = { &CPlayScene::Init, &CPlayScene::Load, &CPlayScene::Step, &CPlayScene::Exit };
	(this->*PlayScene[eSceneID])();

	return iRet;
}


//-----------------------------------
//更新処理
//-----------------------------------
void CPlayScene::Draw()
{
	if (eSceneID == PLAY_SCENE_LOOP)
	{
		cSky.Draw();
		cGround.Draw();
		cPlayer.Draw();
		cEnemyManager.Draw();
		cShotManager.Draw();
		cCameraManager.Draw();

	}
}


//-----------------------------------
//初期化
//-----------------------------------
void CPlayScene::Init()
{
	//カメラ初期化
	cCameraManager.Init();
	cCameraManager.SetNearFar(5.0f, 5000.0f);
	//プレイヤー初期化
	cPlayer.Init();
	//敵初期化
	cEnemyManager.Init();
	//フィールド初期化
	cGround.Init();
	//天球初期化
	cSky.Init();
	//弾初期化
	cShotManager.Init();

	eSceneID = PLAY_SCENE_LAOD;
}


//-----------------------------------
//終了処理
//-----------------------------------
void CPlayScene::Exit()
{
	cCameraManager.Exit();
	cPlayer.Exit();
	cEnemyManager.Exit();
	cShotManager.Exit();

	eSceneID = PLAY_SCENE_INIT;
}


//-----------------------------------
//データロード
//-----------------------------------
void CPlayScene::Load()
{
	cPlayer.Load();
	cEnemyManager.Load();
	cShotManager.Load();

	CSoundManager::Play(CSoundManager::SOUNDID_BGM, DX_PLAYTYPE_LOOP);
	eSceneID = PLAY_SCENE_LOOP;
}


//-----------------------------------
//毎フレーム呼ぶ処理
//-----------------------------------
void CPlayScene::Step()
{
	if (CInput::IsKeyPush(KEY_INPUT_RETURN))
	{
		eSceneID = PLAY_SCENE_END;
	}

	//天球処理
	cSky.Step(cPlayer.GetPosition(), cPlayer.GetRotateY());
	cSky.Loop();

	//プレイヤー更新処理
	if (cCameraManager.GetCameraID() == CCameraManager::CAMERA_ID_PALY)
	{
		cPlayer.Step(cShotManager);
		cEnemyManager.Step();
		cShotManager.Step(cPlayer.GetPosition());

		//当たり判定
		CCollisionManager::CheckHitShotToEnemy(cEnemyManager, cShotManager);
		CCollisionManager::HitToObject(cPlayer, VGet(0.0f, 30.0f, 100.0f), VGet(20.0f, 20.0f, 20.0f));

		cPlayer.Update();
	}

	//カメラの切り替え処理
	if (CInput::IsKeyPush(KEY_INPUT_C))
	{
		cCameraManager.ChangeCamera(CCameraManager::CAMERA_ID_DEBUG);
	}
	else if (CInput::IsKeyPush(KEY_INPUT_V))
	{
		cCameraManager.ChangeCamera(CCameraManager::CAMERA_ID_PALY);
	}
	//カメラ更新処理
	cCameraManager.Step(cPlayer.GetPosition(), cPlayer.GetRotateY());


}