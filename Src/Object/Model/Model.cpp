#include "Model.h"
#include "math.h"

#define IP	(3.14159265f)

//コンストラクタ
CModel::CModel()
{
	memset(&m_sAnimeData, 0, sizeof(ANIM_DATA));
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vRot, 0, sizeof(VECTOR));
	memset(&m_vScale, 0, sizeof(VECTOR));
	memset(&m_OldPos, 0, sizeof(VECTOR));
	MousePosX = MousePosY = 0;


	m_iHndl = -1;

}

//デストラクタ
 CModel::~CModel()
{
	 Exit();
}

//初期化
 void CModel::Init()
 {
	 Exit();
	 m_vPos = VGet(0.0f, 0.0f, 0.0f);
	 m_vRot = VGet(0.0f, 0.0f, 0.0f);
	 m_vScale = VGet(0.1f, 0.1f, 0.1f);
	 memset(&m_sAnimeData, 0, sizeof(m_sAnimeData));
	 memset(&m_OldPos, 0, sizeof(VECTOR));
	 MousePosX = MousePosY = 0;
	 m_sAnimeData.m_iHndl = -1;
	 m_sAnimeData.m_AnimeId = -1;
 }

//終了処理
 void CModel::Exit()
 {
	 DeleteModel();
 }

//更新処理
void CModel::Update()
{
	if (m_iHndl == -1)
	{
		return;		//モデルの読み込み失敗
	}

	MV1SetPosition(m_iHndl, m_vPos);
	MV1SetRotationXYZ(m_iHndl, m_vRot);
	MV1SetScale(m_iHndl, m_vScale);

	UpdateAnime();
}

//モデル描画
void CModel::Draw()
{
	if (m_iHndl == -1)
	{
		return;
	}

	MV1DrawModel(m_iHndl);

	
	//DrawLine3D(m_vPos);
	
 }


//画像読み込み関連
//モデルの通常ロード
bool CModel::LoadModel(const char* pFileName)
{
	if (m_iHndl != -1)
	{
		return false;	//モデルの読み込み済み
	}

	m_iHndl = MV1LoadModel(pFileName);
	if (m_iHndl == -1)
	{
		return false;	//モデルの読み込み失敗
	}

	return true;
}

//モデルのコピーロード
bool CModel::DuplicateModel(int iSrcHndl)
{
	if (m_iHndl != -1)
	{
		return false;	//モデルの読み込み済み
	}

	m_iHndl = MV1DuplicateModel(iSrcHndl);
	if (m_iHndl == -1)
	{
		return false;	//読み込み失敗
	}

	return true;
}

//モデルデータ削除
void CModel::DeleteModel()
{
	if (m_iHndl == -1)
	{
		return;
	}

	MV1DeleteModel(m_iHndl);
	m_iHndl = -1;
}

//アニメリクエスト
void CModel::Reqest(int iAnimeID, float iAnimeSpd, int iAnimeHundl, bool NameChech)
{
	//アニメ削除
	DetachAnime();

	//アニメ再生&各種データをセット
	m_sAnimeData.m_iHndl = MV1AttachAnim(m_iHndl, iAnimeID, iAnimeHundl, NameChech);
	m_sAnimeData.m_AnimeId = iAnimeID;
	m_sAnimeData.m_MaxAnimeTime = MV1GetAnimTotalTime(m_iHndl, m_sAnimeData.m_iHndl);
	m_sAnimeData.m_AnimeTime = 0.0f;
	m_sAnimeData.m_AddTime = iAnimeSpd;
	m_sAnimeData.m_iState = ANIMSTATE_NORMAL;
}

//ループアニメリクエスト
//アニメーションが最終フレームになったら最初に戻す
void CModel::ReqestLoop(int iAnimeID, float iAnimeSpd, int iAnimeHundl, bool NameChech)
{
	Reqest(iAnimeID, iAnimeSpd, iAnimeHundl, NameChech);
	//ここだけループに変える
	m_sAnimeData.m_iState = ANIMESTATE_LOOP;
}

//エンドループリクエスト
//アニメーションが最終フレームになったらそのまま止まる
void CModel::RequestEndLoop(int iAnimeID, float iAnimeSpd, int iAnimeHundl, bool NameChech)
{
	Reqest(iAnimeID, iAnimeSpd, iAnimeHundl, NameChech);
	//ここだけエンドループに変える
	m_sAnimeData.m_iState = ANIMESTATE_END;
}

//安全にアニメーションをデタッチ
void CModel::DetachAnime()
{
	if (m_sAnimeData.m_iHndl != -1)
	{
		MV1DetachAnim(m_iHndl, m_sAnimeData.m_iHndl);
		m_sAnimeData.m_iHndl = -1;
	}
}




//アニメアップデート
//更新処理は毎フレーム呼び出す
void CModel::UpdateAnime()
{

	if (m_sAnimeData.m_iHndl == -1)
	{
		//アニメーションが再生されていない
		return;
	}

	//アニメーション速度更新
	m_sAnimeData.m_AnimeTime += m_sAnimeData.m_AddTime;

	if (m_sAnimeData.m_AnimeTime >= m_sAnimeData.m_MaxAnimeTime)
	{
		//最終フレームまで来たら、状態に合わせて動作を変える
		switch (m_sAnimeData.m_iState)
		{
		case ANIMSTATE_NORMAL:
			DetachAnime();
			m_sAnimeData.m_MaxAnimeTime = 0.0f;
			m_sAnimeData.m_AnimeTime = 0.0f;
			m_sAnimeData.m_AddTime = 0.0f;
			return;
			//ループは最初に戻るだけ

		case ANIMESTATE_LOOP:
			m_sAnimeData.m_AnimeTime = 0.0f;
			break;
			//エンドループは最後で止める
			
		case ANIMESTATE_END:
			m_sAnimeData.m_AnimeTime = m_sAnimeData.m_MaxAnimeTime;
			break;

		default:
			break;
		}
	}

	//再生時間設定
	MV1SetAttachAnimTime(m_iHndl, m_sAnimeData.m_iHndl, m_sAnimeData.m_AnimeTime);
}
