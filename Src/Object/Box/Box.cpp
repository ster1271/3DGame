#include "Box.h"

static const char BOX_PATH[] = { "Data/Box/Box.x" };

CBox::CBox()
{
	for (int i = 0; i < MAX_NUM; i++)
	{
		iHndlCopy[i] = -1;						//モデルのコピー
		m_Pos[i] = VGet(0.0f,0.0f, 0.0f);		//ボックスの座標
		IsActive[i] = false;
	}
	m_Size = VGet(0.0f,0.0f, 0.0f);				//ボックスのサイズ
}

void CBox::Init()
{
	for (int i = 0; i < MAX_NUM; i++)
	{
		iHndlCopy[i] = -1;
		m_Pos[i] = VGet(50.0f, 30.0f, 50.0f * i);
		IsActive[i] = true;
	}

	m_vScale = VGet(0.3f, 0.3f, 0.3f);
	m_Size = VGet(60.0f, 60.0f, 60.0f);
}

void CBox::Load()
{
	//オリジナルモデルの読み込み
	m_iHndl = MV1LoadModel(BOX_PATH);


	//コピーの読み込み
	for (int i = 0; i < MAX_NUM; i++)
	{
		iHndlCopy[i] = MV1DuplicateModel(m_iHndl);
	}
}

//モデルの破棄
void CBox::Exit()
{
	//コピーの削除
	for (int i = 0; i < MAX_NUM; i++)
	{
		MV1DeleteModel(iHndlCopy[i]);
	}

	//オリジナルの削除
	DeleteModel();
}


//モデルの描画
void CBox::Draw()
{

	for (int i = 0; i < MAX_NUM; i++)
	{
		if (IsActive[i] == true)
		{
			MV1DrawModel(iHndlCopy[i]);
		}
	}
}

//モデルの更新
void CBox::Update()
{
	for (int i = 0; i < MAX_NUM; i++)
	{
		MV1SetPosition(iHndlCopy[i], m_Pos[i]);
		MV1SetRotationXYZ(iHndlCopy[i], VGet(0.0f, 0.0f, 0.0f));
		MV1SetScale(iHndlCopy[i], m_vScale);
	}
}



