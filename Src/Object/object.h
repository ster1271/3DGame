#pragma once
#include <DxLib.h>

class CObject
{

public:
	//コンストラクタ・デストラクタ
	CObject();
	~CObject();

protected:
	//座標
	VECTOR cPos;

	//回転値
	VECTOR cRotate;

	//ハンドル
	int iHndl;
};
