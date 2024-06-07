#pragma once
#include "../Input/Input.h"
#include "PlayScene.h"
#include "TitleScene.h"
#include "ResultScene.h"
#include "../SoundManager/SoundManager.h"

class SceneManager
{
private:
	enum tagSCENE
	{
		SCENE_TITLE,	//タイトル画面
		SCENE_PLAY,		//ゲーム中
		SCENE_RESULT,	//リザルト画面

		SCENE_NUM
	};

	CPlayScene cPlayScene;
	CTitleScene cTitleScene;
	CResultScene cResultScene;
	tagSCENE eSceneID;			//シーン保存

public:
	//コンストラクタ・デストラクタ
	SceneManager();
	~SceneManager();

	//繰り返し行う処理
	void Loop();

	//描画処理
	void Draw();

};