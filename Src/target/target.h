#pragma once
#include "../Object/object.h"

#define TARGET_NUM		(15)
#define RADIUS		(10)

class CTarget :public CObject
{
private:
	int ImgHndl[TARGET_NUM];

	VECTOR Pos[TARGET_NUM];
	VECTOR FixPos[TARGET_NUM];
	VECTOR Speed[TARGET_NUM];
	VECTOR Rot;
	VECTOR Scale;
	float Radius;

	bool IsActive[TARGET_NUM];
	int TargetCount;

public:
	//コンストラクタ
	CTarget();

	//初期化
	void Init();

	//モデル読み込み
	void Load();

	//後処理
	void Exit();

	//モデル描画
	void Draw();

	//毎フレーム行う処理
	void Step();
	void UpDate();

	//的座標取得
	VECTOR GetPos(int TargetIndex)
	{
		return Pos[TargetIndex];
	}
	//フラグ取得
	bool GetActive(int TargetIndex)
	{
		return IsActive[TargetIndex];
	}

	//半径取得
	float GetRadius()
	{
		return Radius;
	}

	//カウント取得
	int GetCount()
	{
		return TargetCount;
	}

	//フラグを折る
	void SetActive(int TargetIndex)
	{
		//フラグを折る
		IsActive[TargetIndex] = false;
		//カウントを減らす
		TargetCount--;
		if (TargetCount < 0)
		{
			TargetCount = 0;
		}
	}
};
