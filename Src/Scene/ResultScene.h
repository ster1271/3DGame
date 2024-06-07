#pragma once

class CResultScene
{
private:
	enum tagRESULT_SCENE
	{
		RESULT_SCENE_INIT,
		RESULT_SCENE_LAOD,
		RESULT_SCENE_LOOP,
		RESULT_SCENE_END,

		RESULT_SCENE_NUM
	};

	tagRESULT_SCENE eSceneID;

	int ResultHndl;


public:
	//コンストラクタ・デストラクタ
	CResultScene();
	~CResultScene();

	//初期化
	void Init();

	//読み込み
	void Load();

	//ループ処理
	int Loop();

	//中身の処理
	void Step();

	//描画処理
	void Draw();

	//後処理
	void Exit();

};

