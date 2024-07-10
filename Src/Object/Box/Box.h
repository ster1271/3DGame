#pragma once
#include "vector"
#include "../Model/Model.h"

const int MAX_NUM = 100;

class CBox : public CModel
{
private:
	int iHndlCopy[MAX_NUM];		//モデルのコピー
	VECTOR m_Pos[MAX_NUM];		//ボックスの座標
	VECTOR m_Size;				//ボックスのサイズ
	bool IsActive[MAX_NUM];		//ボックスフラグ

public:
	CBox();

	void Init();

	//モデルの読み込み
	void Load();

	//モデルの描画
	void Draw();

	//モデルの破棄
	void Exit();

	//モデルの更新
	void Update();

	//ボックスの座標取得
	VECTOR GetPos(int BoxNum)
	{
		return m_Pos[BoxNum];
	}

	//ボックスのサイズ取得
	VECTOR GetSize()
	{
		return m_Size;
	}

	//ボックスのサイズ取得
	bool GetActive(int BoxNum)
	{
		return IsActive[BoxNum];
	}
};
