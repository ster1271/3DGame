#include "target.h"

static const char TARGET_PATH[] = { "Data/target/target.x" };

//コンストラクタ
CTarget::CTarget()
{
	for (int targetIndex = 0; targetIndex < TARGET_NUM; targetIndex++)
	{
		//とりあえず-1を入れておく
		ImgHndl[targetIndex] = -1;
		//フラグをすべてfalseにする
		IsActive[targetIndex] = false;
		//ランダムで場所を設定
		Pos[targetIndex] = VGet(0.0f, 0.0f, 0.0f);
		//初期座標格納しておく
		FixPos[targetIndex] = Pos[targetIndex];
		//スピードをそれぞれ変える
		Speed[targetIndex] = VGet(0.0f, 0.0f, 0.0f);
	}
	Scale = VGet(0.0f, 0.0f, 0.0f);
	Rot = VGet(0.0f, 0.0f, 0.0f);
	Radius = 0.0f;
	TargetCount = TARGET_NUM;
}

//初期化
void CTarget::Init()
{
	for (int targetIndex = 0; targetIndex < TARGET_NUM; targetIndex++)
	{
		//とりあえず-1を入れておく
		ImgHndl[targetIndex] = -1;
		//フラグをすべてtrueにする
		IsActive[targetIndex] = true;
		//ランダムで場所を設定
		Pos[targetIndex] = VGet((float)GetRand(100.0f)-50.0f, (float)GetRand(20.0f)+ 10.0f, (float)GetRand(400.0f) + 200.0f);
		//初期座標格納しておく
		FixPos[targetIndex] = Pos[targetIndex];
		//スピードをそれぞれ変える
		Speed[targetIndex] = VGet((float)GetRand(3.0f), (float)GetRand(3.0f), (float)GetRand(3.0f));
	}
	Scale = VGet(0.1f, 0.1f, 0.1f);
	Rot = VGet(DX_PI_F / 2, 0.0f, 0.0f);
	Radius = RADIUS;
	TargetCount = TARGET_NUM;
}


//後処理
void CTarget::Exit()
{
	for (int targetIndex = 0; targetIndex < TARGET_NUM; targetIndex++)
	{
		ImgHndl[targetIndex] = -1;
		IsActive[targetIndex] = false;
		//すべて0.0fにする
		Pos[targetIndex] = VGet(0.0f, 0.0f, 0.0f);
		//すべて0.0fにする
		FixPos[targetIndex] = VGet(0.0f, 0.0f, 0.0f);
		//すべて0.0fにする
		Speed[targetIndex] = VGet(0.0f, 0.0f, 0.0f);
	}
	Scale = VGet(0.0f, 0.0f, 0.0f);
}

//モデル読み込み
void CTarget::Load()
{
	for (int targetIndex = 0; targetIndex < TARGET_NUM; targetIndex++)
	{
		ImgHndl[targetIndex] = MV1LoadModel(TARGET_PATH);
	}
}

//モデル描画
void CTarget::Draw()
{
	for (int targetIndex = 0; targetIndex < TARGET_NUM; targetIndex++)
	{
		if (IsActive[targetIndex] == true)
		{
			MV1DrawModel(ImgHndl[targetIndex]);
			//DrawSphere3D(Pos[targetIndex], Radius, 16, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);
		}
	}

}

//毎フレーム行う処理
void CTarget::Step()
{
	//移動範囲
	VECTOR Renge = VGet(100.0f, 100.0f, 100.0f);


	for (int targetIndex = 0; targetIndex < TARGET_NUM; targetIndex++)
	{
		Pos[targetIndex].x += Speed[targetIndex].x;
		//設定値より大きくなればスピード値を変更する
		if (Pos[targetIndex].x > FixPos[targetIndex].x + Renge.x)
		{
			Speed[targetIndex] = VScale(Speed[targetIndex], -1.0f);
		}
		//設定値より小さくなればスピード値を変更する
		else if (Pos[targetIndex].x < FixPos[targetIndex].x - Renge.x)
		{
			Speed[targetIndex] = VScale(Speed[targetIndex], -1.0f);
		}
	}
}

void CTarget::UpDate()
{
	//座標・スケール・回転値のアップデート
	for (int targetIndex = 0; targetIndex < TARGET_NUM; targetIndex++)
	{
		MV1SetPosition(ImgHndl[targetIndex], Pos[targetIndex]);
		MV1SetRotationXYZ(ImgHndl[targetIndex], Rot);
		MV1SetScale(ImgHndl[targetIndex], Scale);
	}
}