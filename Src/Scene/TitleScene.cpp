#include "DxLib.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "../Input/Input.h"

#define TITLE_PATH		("Data/Title/Title.png")

//-------------------------------------
//コンストラクタ
//-------------------------------------
CTitleScene::CTitleScene()
{
	//とりあえず初期化に移動させる
	eSceneID = TITLE_SCENE_INIT;
}
//-------------------------------------
//デストラクタ
//-------------------------------------
CTitleScene::~CTitleScene()
{
	Exit();
}

//-------------------------------------
//初期化
//-------------------------------------
void CTitleScene::Init()
{
	memset(&TitleHndl, -1, sizeof(TitleHndl));
	Trans = Null;

	eSceneID = TITLE_SCENE_LAOD;
}

//-------------------------------------
//ロード
//-------------------------------------
void CTitleScene::Load()
{
	TitleHndl = LoadGraph(TITLE_PATH);

	eSceneID = TITLE_SCENE_LOOP;
}


//-------------------------------------
//ループする処理
//-------------------------------------
int CTitleScene::Loop()
{
	int iRet = eSceneID == TITLE_SCENE_END ? 1 : 0;

	void (CTitleScene:: * TitleScene[])() = { &CTitleScene::Init, &CTitleScene::Load, &CTitleScene::Step, &CTitleScene::Exit };
	(this->*TitleScene[eSceneID])();

	return iRet;
}


//-------------------------------------
//中身の処理
//-------------------------------------
void CTitleScene::Step()
{
	if (CInput::IsKeyPush(KEY_INPUT_RETURN))
	{
		eSceneID = TITLE_SCENE_END;
	}
}

//-------------------------------------
//描画処理
//-------------------------------------
void CTitleScene::Draw()
{
	DrawGraph(0, 0, TitleHndl, true);


	//DrawString(0, 0, "タイトル画面です", GetColor(255, 255, 255));
	//DrawString(0, 15, "Enterでシーン移動", GetColor(255, 255, 255));

}

//-------------------------------------
//後処理1
//-------------------------------------
void CTitleScene::Exit()
{
	if (TitleHndl != -1)
	{
		DeleteGraph(TitleHndl);
	} 
	eSceneID = TITLE_SCENE_INIT;
}
