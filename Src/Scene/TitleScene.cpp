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
	a = 255;
	Trans = Null;
}

//-------------------------------------
//ロード
//-------------------------------------
void CTitleScene::Load()
{
	TitleHndl = LoadGraph(TITLE_PATH);
}


//-------------------------------------
//ループする処理
//-------------------------------------
int CTitleScene::Loop()
{
	int iRet = 0;
	switch (eSceneID)
	{
	case TITLE_SCENE_INIT:
		Init();
		eSceneID = TITLE_SCENE_LAOD;
		break;

	case TITLE_SCENE_LAOD:
		Load();
		eSceneID = TITLE_SCENE_LOOP;
		break;

	case TITLE_SCENE_LOOP:
		Step();
		Draw();
		break;

	case TITLE_SCENE_END:
		Exit();
		iRet = 1;
		break;


	default:
		break;
	}

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
	//DrawGraph(0, 0, TitleHndl, true);

	SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, a);
	DrawBox(0, 0, 1280, 720, GetColor(255, 0, 0), true);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);

	DrawString(0, 0, "タイトル画面です", GetColor(255, 255, 255));
	DrawString(0, 15, "Enterでシーン移動", GetColor(255, 255, 255));

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
}
