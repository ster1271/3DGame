#pragma once
#include <DxLib.h>

#define ANIMSTATE_NORMAL	0
#define ANIMESTATE_LOOP		1
#define ANIMESTATE_END		2

class CModel
{
protected:
	//アニメ関連のデータをまとめた構造体
	typedef struct 
	{
		float m_MaxAnimeTime;	//アニメ全再生時間
		float m_AnimeTime;		//アニメ再生時間
		float m_AddTime;		//再生速度
		int m_iHndl;			//アニメハンドル
		int m_AnimeId;			//再生中のアニメID
		int m_iState;			//アニメの状態
	}ANIM_DATA;

	VECTOR m_vPos;				//座標
	VECTOR m_OldPos;			//前座標
	VECTOR m_vRot;				//回転角度
	VECTOR m_vScale;			//拡大縮小率
	VECTOR m_HarfPos;			//サイズの半分の座標ベクトル
	ANIM_DATA m_sAnimeData;		//アニメ再生関連データ
	int MousePosX, MousePosY;	//マウス座標
	int m_iHndl;				//モデルハンドル

public:
	CModel();
	virtual ~CModel();

	//初期化
	virtual void Init();

	//終了処理
	virtual void Exit();

	//更新処理
	virtual void Update();

	//モデル描画
	virtual void Draw();


	//画像読み込み関連
	//モデルの通常ロード
	bool LoadModel(const char* pFileName);

	//モデルのコピーロード
	bool DuplicateModel(int iSrcHndl);

	//モデルデータ削除
	void DeleteModel();


	//アニメーション関連関数

	//アニメアップデート
	//更新処理は毎フレーム呼び出す
	void UpdateAnime();

	//アニメリクエスト
	// iAnimeID    : アタッチするアニメ番号
	// iAnimeSpd   : アニメ再生速度
	// iAnimeHundl : アニメーションを持っているモデルのハンドル(-1ならばこのモデルのアニメ使用)
	// NameCheck   : 別モデルのアニメーションを使用する場合、モデルのフレーム名が一致してない場合
	//				 アニメをアタッチするか(iAnimeHundl = -1の場合は無視)
	void Reqest(int iAnimeID, float iAnimeSpd, int iAnimeHundl = -1, bool NameChech = false);

	//ループアニメリクエスト
	//アニメーションが最終フレームになったら最初に戻す
	void ReqestLoop(int iAnimeID, float iAnimeSpd, int iAnimeHundl = -1, bool NameChech = false);

	//エンドループリクエスト
	//アニメーションが最終フレームになったらそのまま止まる
	void RequestEndLoop(int iAnimeID, float iAnimeSpd, int iAnimeHundl = -1, bool NameChech = false);


private:
	//安全にアニメーションをデタッチ
	void DetachAnime();
};
