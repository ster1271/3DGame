#include "Player.h"
#include "../Input/Input.h"
#include <math.h>
#include "../MyLibrary/MyLibrary.h"

//定義関連
static const char PLAYER_MODEL_PATH[] = { "Data/Tank/Tank.x" };		//ファイル名
static const float ROTATE_SPEED = 0.05f;							//プレイヤーの回転速度
static const float MOVE_SPEED = 0.5f;								//プレイヤーの移動速度


//----------------------------
//コンストラクタ
//----------------------------
CPlayer::CPlayer()
{

	//初期化する
	memset(&vSpeed, 0, sizeof(VECTOR));
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
	Init(VGet(0.0f, 10.0f, 0.0f), VGet(0.0f, DX_PI_F, 0.0f));
}

//----------------------------
//初期化
//----------------------------
void CPlayer::Init(VECTOR Pos, VECTOR Rot)
{
	CModel::Init();

	m_vPos = Pos;
	m_vRot = Rot;
	memset(&vSpeed, 0, sizeof(VECTOR));
	eState = PLAYER_STATE_NORMAL;

}

//----------------------------
//データ関連のロード
//----------------------------
void CPlayer::Load()
{
	LoadModel(PLAYER_MODEL_PATH);
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


//----------------------------
//毎フレーム呼ぶ処理
//----------------------------
void CPlayer::Step(CShotManager& cShotManager)
{
	VECTOR OldMousePos = VGet(MousePosX, MousePosY, 0.0f);

	GetMousePoint(&MousePosX, &MousePosY);
	VECTOR MousePos = VGet(MousePosX, MousePosY, 0.0f);

	VECTOR Move = MyMath::SubVec(MousePos, OldMousePos);
	Move = MyMath::Scale(Move, 0.01f);

	m_OldPos = m_vPos;

	//キャラクターの回転
	m_vRot.y -= Move.y;

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

	//入力したキー情報とプレイヤーの角度から、移動速度を求める
	vSpeed.x = sin(m_vRot.y) * fSpd;
	vSpeed.z = cos(m_vRot.y) * fSpd;
	//移動速度を現在の座標に加算する
	m_vPos.x += vSpeed.x;
	m_vPos.z += vSpeed.z;


	if (CInput::IsKeyPush(KEY_INPUT_SPACE))
	{
		//戦車の打ち出し口から出るように座標を変更する
		VECTOR BulletPos = m_vPos;

		//発射位置座標
		VECTOR SetPos = BulletPos;
		SetPos.z = -70.0f;
		SetPos.y = 5.0f;
		SetPos.x = 0.0f;


		//速度はプレイヤーと同じ方法で移動方向を決める
		const float SHOT_SPEED = 5.0f;
		VECTOR vSpd;
		
		vSpd.x = sinf(m_vRot.y) * -SHOT_SPEED;
		vSpd.z = cosf(m_vRot.y) * -SHOT_SPEED;
		vSpd.y = 0.0f;

		//===================行列による弾の発射位置変更==============================
		
		//①座標を原点に戻す行列を作成
		MATRIX mCenter = MGetTranslate(VScale(BulletPos, -1.0f));
		//②原点座標から元の座標に戻す行列を作成
		MATRIX mPosition = MGetTranslate(BulletPos);

		//③弾の位置に移動する行列を準備
		MATRIX mMove = MGetIdent();
		mMove = MGetTranslate(SetPos); 

		//④X軸回転準備
		MATRIX rotX = MGetRotX(m_vRot.x);

		//⑤Y軸回転準備
		MATRIX rotY = MGetRotY(m_vRot.y);

		/* X -> Y -> Zの順番で計算*/
		
		//⑥原点座標から移動量を増やす
		MATRIX matrix = MMult(mCenter, mMove);

		//⑦回転行列計算
		matrix = MMult(matrix, rotX);
		matrix = MMult(matrix, rotY);

		//⑧元の位置に戻す
		matrix = MMult(matrix, mPosition);

		//⑨求めた行列を座標に反映
		BulletPos = VTransform(BulletPos, matrix);


		//===================行列による弾の発射位置変更==============================

		cShotManager.RequestPlayerShot(BulletPos, vSpd);
	}
}

