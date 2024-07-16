#pragma once

class CTitleScene
{
private:
	enum tagTITLE_SCENE
	{
		TITLE_SCENE_INIT,
		TITLE_SCENE_LAOD,
		TITLE_SCENE_LOOP,
		TITLE_SCENE_END,

		TITLE_SCENE_NUM
	};

	tagTITLE_SCENE eSceneID;

	int TitleHndl;

	enum TRANSPARENCY
	{
		Null,
		TransTrue,
		Transfalse,
	};

	TRANSPARENCY Trans;

public:
	//コンストラクタ・デストラクタ
	CTitleScene();
	~CTitleScene();

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
