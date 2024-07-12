#pragma once
#include "../Object/object.h"

#define MAX_NUM		(15)

class CTarget :public CObject
{
private:
	int ImgHndl[MAX_NUM];

	VECTOR Pos[MAX_NUM];
	VECTOR Scale;

public:
	//初期化
	void Init();

	//モデル読み込み
	void Load();

	//モデル描画
	void Draw();

	//毎フレーム行う処理
	void Step();
};
