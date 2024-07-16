#pragma once
#include <DxLib.h>

#include "../Camera/CameraManager.h"
#include "../Fade/Fade.h"
#include "../Player/Player.h"
#include "../Object/Ground/Ground.h"
#include "../Object/Sky/Sky.h"
#include "../Object/Box/Box.h"
#include "../target/target.h"
#include "../Shot/ShotManager.h"
#include "../Enemy/EnemyManager.h"
#include "../CollisionManager/CollisionManager.h"

class CPlayScene
{
private:
	enum tagPLAY_SCENE
	{
		PLAY_SCENE_INIT,
		PLAY_SCENE_LAOD,
		PLAY_SCENE_LOOP,
		PLAY_SCENE_END,

		PLAY_SCENE_NUM
	};

	CCameraManager cCameraManager;			//カメラマネージャー
	CPlayer cPlayer;						//プレイヤー
	tagPLAY_SCENE eSceneID;					//シーン保存
	CGround cGround;						//フィールド
	CBox cBox;								//ボックス
	CSky cSky;								//天球
	CTarget cTarget;						//的
	CShotManager cShotManager;				//弾マネージャー
	CEnemyManager cEnemyManager;			//敵マネージャー

public:
	//コンストラクタ・デストラクタ
	CPlayScene();
	~CPlayScene();

	//繰り返し行う処理
	int Loop();

	//描画処理
	void Draw();

private:
	//初期化
	void Init();

	//終了処理
	void Exit();

	//データロード
	void Load();

	//毎フレーム呼ぶ処理
	void Step();
};
