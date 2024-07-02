#include "Player.h"
#include "../Common.h"


//定義関連
static const char MODEL_PATH[] = { "Data/il/あいえるたん.pmx" };
static const char PLAYER_MODEL_PATH[] = { "Data/Tank/Tank.x" };					//ファイル名
static const char PLAYER_MODEL_FOUND_PATH[] = { "Data/Tank/tank_M.x" };		//タンクのファイル名(本体)
static const char PLAYER_MODEL_HEAD_PATH[] = { "Data/Tank/tank_H.x" };		//タンクのファイル名(頭)

static const float ROTATE_SPEED = 0.05f;							//プレイヤーの回転速度
static const float MOVE_SPEED = 0.5f;								//プレイヤーの移動速度

const float ROT_SPEED = 0.02f;			//軸の回転スピード

//----------------------------
//コンストラクタ
//----------------------------
CPlayer::CPlayer()
{

	//初期化する
	memset(&vSpeed, 0, sizeof(VECTOR));
	memset(&vHeadPos, 0, sizeof(VECTOR));
	memset(&vHeadRot, 0, sizeof(VECTOR));
	HeadHndl = -1;

	eState = PLAYER_STATE_NORMAL;

}

//----------------------------
//デストラクタ
//----------------------------
CPlayer::~CPlayer()
{
	Delete();
	Exit();
}

//----------------------------
//初期化
//----------------------------
void CPlayer::Init()
{
	Init(VGet(0.0f, 10.0f, 0.0f), VGet(0.0f, 0.0f, 0.0f));
}

//----------------------------
//初期化
//----------------------------
void CPlayer::Init(VECTOR Pos, VECTOR Rot)
{
	CModel::Init();

	m_vPos = Pos;
	NextPos = m_vPos;
	m_vRot = Rot;
	vHeadRot = Rot;
	memset(&vSpeed, 0, sizeof(VECTOR));
	vHeadPos = Pos;
	eState = PLAYER_STATE_NORMAL;

}

//----------------------------
//データ関連のロード
//----------------------------
void CPlayer::Load()
{
	LoadModel(PLAYER_MODEL_FOUND_PATH);
	HeadHndl = MV1LoadModel(PLAYER_MODEL_HEAD_PATH);
}

//----------------------------
//データ関連の破棄
//----------------------------
void CPlayer::Delete()
{
	if (m_iHndl != -1)
	{
		MV1DeleteModel(m_iHndl);
		m_iHndl = -1;
	}
}

//----------------------------
//終了処理
//----------------------------
void CPlayer::Exit()
{
	//メモリ開放などを記述
	CModel::Exit();
}

//描画処理
void CPlayer::Draw()
{
	if (m_iHndl == -1)
	{
		return;
	}
	if (HeadHndl == -1)
	{
		return;
	}

	MV1DrawModel(m_iHndl);
	MV1DrawModel(HeadHndl);

	CDraw3D::DrawBox3D(m_vPos, VGet(40.0f, 50.0f, 40.0f));
	CDraw3D::DrawBox3D(VGet(0.0f, 30.0f, 100.0f), VGet(20.0f, 20.0f, 20.0f));

	DrawFormatString(0, 0, GetColor(255, 0, 0), "X座標：%f", m_vPos.x);
	DrawFormatString(0, 15, GetColor(255, 0, 0), "Y座標：%f", m_vPos.y);
	DrawFormatString(0, 30, GetColor(255, 0, 0), "Z座標：%f", m_vPos.z);
}

//更新処理
void CPlayer::Update()
{
	if (m_iHndl == -1)
	{
		return;		//モデルの読み込み失敗
	}
	if (HeadHndl == -1)
	{
		return;
	}

	MV1SetPosition(m_iHndl, m_vPos);
	MV1SetRotationXYZ(m_iHndl, m_vRot);
	MV1SetScale(m_iHndl, m_vScale);

	MV1SetPosition(HeadHndl, vHeadPos);
	MV1SetRotationXYZ(HeadHndl, vHeadRot);
	MV1SetScale(HeadHndl, m_vScale);


	UpdateAnime();
}


//----------------------------
//毎フレーム呼ぶ処理
//----------------------------
void CPlayer::Step(CShotManager& cShotManager)
{
	for (int i = 0; i < 6; i++)
	{
		//方向チェックの初期化
		Dir[i] = false;
	}

	//前座標の格納
	m_OldPos = m_vPos;

	GetMousePoint(&MousePosX, &MousePosY);

	VECTOR Move = MyMath::SubVec(VGet((float)MousePosX, (float)MousePosY, 0.0f), VGet((float)SCREEN_SIZE_X / 2.0f, (float)SCREEN_SIZE_Y / 2.0f, 0.0f));
	//vHeadRot.x += (Move.y * 0.01f) * DX_PI_F / 180.0f;
	VECTOR vOldRot = VGet(0.0f, vHeadRot.y, 0.0f);

	vHeadRot.y += (Move.x * 0.01f) * DX_PI_F / 180.0f;

	//砲台の角度制限(制作中)
	float a = (-45.0f * DX_PI_F / 180.0f);
	//float b = (275.0f * DX_PI_F / 180.0f);

	if (vHeadRot.y < a /*|| vHeadRot.y > b*/)
	{
		vHeadRot.y = vOldRot.y;
	}
	

	SetMousePoint(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2);

	//キャラクターの回転
	if (CInput::IsKeyKeep(KEY_INPUT_A))
	{
		m_vRot.y -= ROT_SPEED;
		vHeadRot.y -= ROT_SPEED;
	}
	else if (CInput::IsKeyKeep(KEY_INPUT_D))
	{
		m_vRot.y += ROT_SPEED;
		vHeadRot.y += ROT_SPEED;
	}


	//キャラクターの移動
	float fSpd = 0.0f;
	if (CInput::IsKeyKeep(KEY_INPUT_W))
	{
		fSpd = -MOVE_SPEED;
	}
	else if (CInput::IsKeyKeep(KEY_INPUT_S))
	{
		fSpd = MOVE_SPEED;
	}

	m_vPos = NextPos;
	vHeadPos = m_vPos;

	//入力したキー情報とプレイヤーの角度から、移動速度を求める
	vSpeed.x = sin(m_vRot.y) * fSpd;
	vSpeed.z = cos(m_vRot.y) * fSpd;
	//移動速度を現在の座標に加算する
	NextPos.x += vSpeed.x;
	NextPos.z += vSpeed.z;


	if (CInput::IsKeyPush(KEY_INPUT_SPACE))
	{
		//戦車の打ち出し口から出るように座標を変更する
		VECTOR BulletPos = vHeadPos;

		//発射位置座標
		VECTOR SetPos = VGet(0.0f, 5.0f, -70.0f);

		//速度はプレイヤーと同じ方法で移動方向を決める
		const float SHOT_SPEED = 5.0f;
		VECTOR vSpd;
		
		vSpd.x = sinf(vHeadRot.y) * -SHOT_SPEED;
		vSpd.z = cosf(vHeadRot.y) * -SHOT_SPEED;
		vSpd.y = 0.0f;

		//===================行列による弾の発射位置変更==============================
		
		//�@座標を原点に戻す行列を作成
		MATRIX mCenter = MGetTranslate(VScale(BulletPos, -1.0f));
		//�A原点座標から元の座標に戻す行列を作成
		MATRIX mPosition = MGetTranslate(BulletPos);

		//�B弾の発射位置に移動する行列を準備
		MATRIX mMove = MGetIdent();
		mMove = MGetTranslate(SetPos); 

		//�CX軸回転準備
		MATRIX rotX = MGetRotX(vHeadRot.x);

		//�DY軸回転準備
		MATRIX rotY = MGetRotY(vHeadRot.y);
		
		//�E原点座標から移動量を増やす
		MATRIX matrix = MMult(mCenter, mMove);

		//�F回転行列計算
		/* X -> Y -> Zの順番で計算*/
		matrix = MMult(matrix, rotX);
		matrix = MMult(matrix, rotY);

		//�G元の位置に戻す
		matrix = MMult(matrix, mPosition);

		//�H求めた行列を座標に反映
		BulletPos = VTransform(BulletPos, matrix);


		//===================行列による弾の発射位置変更==============================

		cShotManager.RequestPlayerShot(BulletPos, vSpd, 2.0f);
	}

	//向いている方向チェック
	CheckDir();
}

//プレイヤーのめり込み修正
void CPlayer::SetPos(VECTOR NewPos)
{
	NextPos = NewPos;
}


//向いている方向チェック
void CPlayer::CheckDir()
{
	if (NextPos.x > m_vPos.x)
	{
		//右に動いている
		Dir[0] = true;
	}
	if (NextPos.x < m_vPos.x)
	{
		//左に動いている
		Dir[1] = true;
	}
	if (NextPos.y > m_vPos.y)
	{
		//上に動いている
		Dir[2] = true;
	}
	if (NextPos.y < m_vPos.y)
	{
		//下に動いている
		Dir[3] = true;
	}
	if (NextPos.z > m_vPos.z)
	{
		//奥に動いている
		Dir[4] = true;
	}
	if (NextPos.z < m_vPos.z)
	{
		//手前に動いている
		Dir[5] = true;
	}

}