#pragma once

//インプットクラス
class CInput
{
public:
	//入力制御初期化
	static void InitInput();

	//入力制御ステップ
	//他のStepより早く呼ぶ
	static void StepInput();

	//今押された
	static bool IsKeyPush(int Key_code);

	//ずっと押されている
	static bool IsKeyKeep(int Key_code);

	//キーを離した
	static bool IsKeyRelease(int Key_code);

	//単純に押されているか
	static bool IsKeyDown(int Key_code);
};



