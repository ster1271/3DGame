#pragma once
#include "vector"
#include "../Model/Model.h"

const int MAX_NUM = 20;

class CBox : public CModel
{
private:
	int iHndlCopy[MAX_NUM];		//モデルのコピー
	VECTOR m_Pos[MAX_NUM];

public:
	void Init();

	//モデルの読み込み
	void Load();

	//モデルの描画
	void Draw();

	//モデルの破棄
	void Exit();

	//モデルの更新
	void Update();



};
