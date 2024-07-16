#include "DxLib.h"
#include "SceneManager.h"
#include "ResultScene.h"
#include "../Input/Input.h"

#define RESULT_PATH		("Data/Result/result.png")

//-------------------------------------
//コンストラクタ
//-------------------------------------
CResultScene::CResultScene()
{
	//とりあえず初期化に移動させる
	eSceneID = RESULT_SCENE_INIT;
	ResultHndl = -1;
}
//-------------------------------------
//デストラクタ
//-------------------------------------
CResultScene::~CResultScene()
{
	Exit();
}

//-------------------------------------
//初期化
//-------------------------------------
void CResultScene::Init()
{
	memset(&ResultHndl, -1, sizeof(ResultHndl));

	eSceneID = RESULT_SCENE_LAOD;
}

//-------------------------------------
//ロード
//-------------------------------------
void CResultScene::Load()
{
	ResultHndl = LoadGraph(RESULT_PATH);

	eSceneID = RESULT_SCENE_LOOP;
}


//-------------------------------------
//ループする処理
//-------------------------------------
int CResultScene::Loop()
{
	//シーンIDがRESULT_SCENE_ENDなら1そうでなければ0を返す
	int iRet = eSceneID == RESULT_SCENE_END ? 1 : 0;

	//関数ポインタを作成
	void (CResultScene:: * ResultScene[])() = { &CResultScene::Init, &CResultScene::Load, &CResultScene::Step, &CResultScene::Exit };
	(this->*ResultScene[eSceneID])();

	return iRet;
}


//-------------------------------------
//中身の処理
//-------------------------------------
void CResultScene::Step()
{
	if (CInput::IsKeyPush(KEY_INPUT_RETURN))
	{
		eSceneID = RESULT_SCENE_END;
	}
}

//-------------------------------------
//描画処理
//-------------------------------------
void CResultScene::Draw()
{
	DrawGraph(0, 0, ResultHndl, true);

	
	//DrawString(0, 0, "リザルト画面です", GetColor(255, 255, 255));
	//DrawString(0, 15, "Enterでシーン移動", GetColor(255, 255, 255));

}

//-------------------------------------
//後処理1
//-------------------------------------
void CResultScene::Exit()
{
	if (ResultHndl != -1)
	{
		DeleteGraph(ResultHndl);
	}
	eSceneID = RESULT_SCENE_INIT;
}
