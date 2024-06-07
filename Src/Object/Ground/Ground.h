#pragma once
#include "../object.h"

class CGround :public CObject
{
public:
	//コンストラクタ・デストラクタ
	CGround();
	~CGround();

	//初期化
	void Init();

	//描画
	void Draw();
};
