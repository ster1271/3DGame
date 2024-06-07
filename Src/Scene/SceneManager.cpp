#include "SceneManager.h"

//=============定義関連================


//=====================================

//-------------------------------------
//コンストラクタ
//-------------------------------------
SceneManager::SceneManager()
{
	//タイトル画面がないのでSCENE_PLAYに
	eSceneID = SCENE_TITLE;
	CInput::InitInput();
	CSoundManager::Init();
	CSoundManager::LoadAllData();
}

//-------------------------------------
//デストラクタ
//-------------------------------------
SceneManager::~SceneManager()
{
	CSoundManager::Exit();
}



//-------------------------------------
//毎フレーム呼ぶ処理
//-------------------------------------
void SceneManager::Loop()
{
	switch (eSceneID)
	{
	case SCENE_TITLE:
		if (cTitleScene.Loop() != 0)
		{
			eSceneID = SCENE_PLAY;
		}
		break;

	case SCENE_PLAY:
		if (cPlayScene.Loop() != 0)
		{
			eSceneID = SCENE_RESULT;
		}
		break;

	case SCENE_RESULT:
		if (cResultScene.Loop() != 0)
		{
			eSceneID = SCENE_TITLE;
		}
		break;

	case SCENE_NUM:

		break;

	default:
		break;
	}
}


//-------------------------------------
//毎フレーム呼ぶ処理
//-------------------------------------
void SceneManager::Draw()
{
	switch (eSceneID)
	{
	case SCENE_TITLE:

		break;

	case SCENE_PLAY:
		cPlayScene.Draw();
		break;

	case SCENE_RESULT:

		break;

	case SCENE_NUM:

		break;

	default:
		break;
	}
}
