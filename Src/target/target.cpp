#include "target.h"

static const char TARGET_PATH[] = { "Data/target/target.x" };

//初期化
void CTarget::Init()
{
	for (int i = 0; i < MAX_NUM; i++)
	{
		ImgHndl[i] = -1;
		Pos[i] = VGet(GetRand(100.0f), GetRand(20.0f), GetRand(100.0f));
	}

	Scale = VGet(0.3f, 0.3f, 0.03f);
}

//モデル読み込み
void CTarget::Load()
{
	for (int i = 0; i < MAX_NUM; i++)
	{
		ImgHndl[i] = MV1LoadModel(TARGET_PATH);
	}
}

//モデル描画
void CTarget::Draw()
{

}

//毎フレーム行う処理
void CTarget::Step()
{

}