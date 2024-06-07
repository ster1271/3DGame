#include "DxLib.h"
#include "math.h"
#include "Src/Input/Input.h"
#include "Src/CollisionManager/Collision/Collision.h"
#include "Src/Player/Player.h"
#include "Src/Camera/CameraManager.h"
#include "Src/Scene/PlayScene.h"
#include "Src/Scene/SceneManager.h"
#include "Src/Object/Model/Model.h"

#define	SCREEN_SIZE_X	1280	// X方向の画面サイズを指定
#define	SCREEN_SIZE_Y	720	// Y方向の画面サイズを指定


// Win32アプリケーションは WinMain関数 から始まる
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウの状態を設定する
	ChangeWindowMode(true);

	//DXライブラリの初期化
	if (DxLib_Init() == -1) {
		return -1;
	}

	// 画面サイズを変更
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);

	//描画するスクリーンを設定する
	SetDrawScreen(DX_SCREEN_BACK);
	
	//-----------------------------------------
	//一番最初に１回だけやる処理をここに書く
	CInput::InitInput();

	//シーン
	SceneManager cSceneManager;
	

	//-----------------------------------------

	//ゲームメインループ
	while (ProcessMessage() != -1)
	{
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			//エスケープキーが押されたら終了
			break;
		}

		//画面に表示されたものを初期化
		ClearDrawScreen();

		CInput::StepInput();
		//-----------------------------------------
		//ここからゲームの本体を書くことになる
		//-----------------------------------------

		//計算処理
		cSceneManager.Loop();


		//描画処理
		cSceneManager.Draw();

		//-----------------------------------------
		//ループの終わりに
		//フリップ関数
		ScreenFlip();

	}

	//-----------------------------------------
	//最後に１回だけやる処理をここに書く

	//-----------------------------------------
	//DXライブラリの後処理
	DxLib_End();

	return 0;
}

