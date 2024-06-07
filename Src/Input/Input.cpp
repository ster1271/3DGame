#include "DxLib.h"
#include "Input.h"

#define KEY_BUF_LEN	(256)

//現在のフレームのキー情報
char currentKeyBuf[KEY_BUF_LEN] = { 0 };

//前フレームのキー情報
char preKeyBuf[KEY_BUF_LEN]= { 0 };

//入力制御初期化
void CInput::InitInput()
{
	for (int index = 0; index < KEY_BUF_LEN; index++)
	{
		currentKeyBuf[index] = '\0';
		preKeyBuf[index] = '\0';
	}
}

//入力制御ステップ
//他のStepより早く呼ぶ
void CInput::StepInput()
{
	//前フレームのキー情報変数に記録しておく
	for (int index = 0; index < KEY_BUF_LEN; index++)
	{
		preKeyBuf[index] = currentKeyBuf[index];
	}

	//現在のキー情報を取得
	GetHitKeyStateAll(currentKeyBuf);
}

bool CInput::IsKeyPush(int Key_code)
{
	//前フレで押されていない かつ 現フレで押されている
	if (preKeyBuf[Key_code] == 0 && currentKeyBuf[Key_code] == 1)
		return true;

	//押されていないので false
	return false;
}

bool CInput::IsKeyKeep(int Key_code)
{
	//前フレで押されている かつ 現フレで押されている
	if (preKeyBuf[Key_code] == 1 && currentKeyBuf[Key_code] == 1)
		return true;

	//押されていないので false
	return false;
}

bool CInput::IsKeyRelease(int Key_code)
{
	//前フレで押されている かつ 現フレで押されていない
	if (preKeyBuf[Key_code] == 1 && currentKeyBuf[Key_code] == 0)
		return true;

	//押されていないので false
	return false;
}

bool CInput::IsKeyDown(int Key_code)
{
	//現フレで押されている（前フレの状態は関係なし）
	if (currentKeyBuf[Key_code] == 1)
		return true;

	return false;
}