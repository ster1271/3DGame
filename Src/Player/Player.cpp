#include "Player.h"
#include "../Common.h"


//��`�֘A
static const char MODEL_PATH[] = { "Data/il/�������邽��.pmx" };
static const char PLAYER_MODEL_PATH[] = { "Data/Tank/Tank.x" };					//�t�@�C����
static const char PLAYER_MODEL_FOUND_PATH[] = { "Data/Tank/tank_M.x" };		//�^���N�̃t�@�C����(�{��)
static const char PLAYER_MODEL_HEAD_PATH[] = { "Data/Tank/tank_H.x" };		//�^���N�̃t�@�C����(��)
static const char SHOT_MODEL_PATH[] = { "Data/Tank/tank_shot.x" };			//���˓��̃t�@�C����

static const float ROTATE_SPEED = 0.05f;							//�v���C���[�̉�]���x
static const float MOVE_SPEED = 0.5f;								//�v���C���[�̈ړ����x

const float ROT_SPEED = 0.02f;			//���̉�]�X�s�[�h

//----------------------------
//�R���X�g���N�^
//----------------------------
CPlayer::CPlayer()
{

	//����������
	memset(&vSpeed, 0, sizeof(VECTOR));
	memset(&vHeadPos, 0, sizeof(VECTOR));
	memset(&vHeadRot, 0, sizeof(VECTOR));
	HeadHndl = -1;

	eState = PLAYER_STATE_NORMAL;

}

//----------------------------
//�f�X�g���N�^
//----------------------------
CPlayer::~CPlayer()
{
	Delete();
	Exit();
}

//----------------------------
//������
//----------------------------
void CPlayer::Init()
{
	Init(VGet(0.0f, 10.0f, 0.0f), VGet(0.0f, DX_PI_F, 0.0f));
}

//----------------------------
//������
//----------------------------
void CPlayer::Init(VECTOR Pos, VECTOR Rot)
{
	CModel::Init();

	m_vPos = Pos;
	NextPos = m_vPos;
	m_vRot = Rot;
	vHeadRot = Rot;
	memset(&vSpeed, 0, sizeof(VECTOR));
	vHeadPos = VGet(0.0f, 23.0f, 0.0f);
	eState = PLAYER_STATE_NORMAL;

}

//----------------------------
//�f�[�^�֘A�̃��[�h
//----------------------------
void CPlayer::Load()
{
	LoadModel(PLAYER_MODEL_FOUND_PATH);
	HeadHndl = MV1LoadModel(PLAYER_MODEL_HEAD_PATH);
	ShotHndl = MV1LoadModel(SHOT_MODEL_PATH);
}

//----------------------------
//�f�[�^�֘A�̔j��
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
//�I������
//----------------------------
void CPlayer::Exit()
{
	//�������J���Ȃǂ��L�q
	CModel::Exit();
}

//�`�揈��
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

	DrawFormatString(0, 0, GetColor(255, 0, 0), "X���W�F%f", m_vPos.x);
	DrawFormatString(0, 15, GetColor(255, 0, 0), "Y���W�F%f", m_vPos.y);
	DrawFormatString(0, 30, GetColor(255, 0, 0), "Z���W�F%f", m_vPos.z);

	DrawFormatString(0, 90, GetColor(255, 0, 0), "��]�lY�F%f", vHeadRot.y);
	DrawFormatString(0, 105, GetColor(255, 0, 0), "��]�lX�F%f", vHeadRot.x);

	//DrawSphere3D(TEST_BULLETPOS, 3.0f, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), false);
}

//�X�V����
void CPlayer::Update()
{
	if (m_iHndl == -1)
	{
		return;		//���f���̓ǂݍ��ݎ��s
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
//���t���[���Ăԏ���
//----------------------------
void CPlayer::Step(CShotManager& cShotManager)
{
	for (int i = 0; i < 6; i++)
	{
		//�����`�F�b�N�̏�����
		Dir[i] = false;
	}

	//�O���W�̊i�[
	m_OldPos = m_vPos;

	GetMousePoint(&MousePosX, &MousePosY);

	VECTOR Move = MyMath::SubVec(VGet((float)MousePosX, (float)MousePosY, 0.0f), VGet((float)SCREEN_SIZE_X / 2.0f, (float)SCREEN_SIZE_Y / 2.0f, 0.0f));
	VECTOR vOldRot = VGet(vHeadRot.x, vHeadRot.y, 0.0f);

	vHeadRot.y += (Move.x * 0.01f) * DX_PI_F / 180.0f;
	vHeadRot.x += (Move.y * 0.01f) * DX_PI_F / 180.0f;

	//�C��̊p�x����(���E)
	float Angle_Limit_L = m_vRot.y + (-90.0f * DX_PI_F / 180.0f);
	float Angle_Limit_R = m_vRot.y + (90.0f * DX_PI_F / 180.0f);

	if (vHeadRot.y < Angle_Limit_L || vHeadRot.y > Angle_Limit_R)
	{
		vHeadRot.y = vOldRot.y;
	}
	//�C��̊p�x����(�㉺)
	float Angle_Limit_UP = (20.0f * DX_PI_F / 180.0f);
	if (vHeadRot.x < 0.0f || vHeadRot.x > Angle_Limit_UP)
	{
		vHeadRot.x = vOldRot.x;
	}

	SetMousePoint(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2);

	//�L�����N�^�[�̉�]
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

	//�L�����N�^�[�̈ړ�
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
	vHeadPos.x = m_vPos.x;
	vHeadPos.z = m_vPos.z;

	//���͂����L�[���ƃv���C���[�̊p�x����A�ړ����x�����߂�
	vSpeed.x = sin(m_vRot.y) * fSpd;
	vSpeed.z = cos(m_vRot.y) * fSpd;
	//�ړ����x�����݂̍��W�ɉ��Z����
	NextPos.x += vSpeed.x;
	NextPos.z += vSpeed.z;


	if (CInput::IsKeyPush(KEY_INPUT_SPACE))
	{
		//�e�̈ʒu����
		VECTOR BulletPos = VGet(0.0f, 0.0f, -30.0f);

		//���x�̓v���C���[�Ɠ������@�ňړ����������߂�
		const float SHOT_SPEED = 5.0f;
		VECTOR vSpd;
		
		vSpd.x = sinf(vHeadRot.y) * -SHOT_SPEED;
		vSpd.z = cosf(vHeadRot.y) * -SHOT_SPEED;
		vSpd.y = 0.0f;

		//===================�s��ɂ��e�̔��ˈʒu�ύX==============================
		
		//�@���W�����_�ɖ߂��s����쐬
		MATRIX mRevPosition = MGetTranslate(VScale(vHeadPos, -1.0f));
		//�A���_���W���猳�̍��W�ɖ߂��s����쐬
		MATRIX mPosition = MGetTranslate(vHeadPos);

		//�B�e�̔��ˈʒu�Ɉړ�����s�������
		MATRIX BulletMat = MGetTranslate(BulletPos);

		//�CX����]����
		MATRIX rotX = MGetRotX(vHeadRot.x);

		//�DY����]����
		MATRIX rotY = MGetRotY(vHeadRot.y);

		//�E���_���W����ړ��ʂ𑝂₷
		MATRIX matrix = MMult(mRevPosition, BulletMat);

		//�F��]�s��v�Z
		/* X -> Y -> Z�̏��ԂŌv�Z*/
		matrix = MMult(matrix, rotX);
		matrix = MMult(matrix, rotY);

		//�G���̈ʒu�ɖ߂�
		matrix = MMult(matrix, mPosition);

		//�H���߂��s������W�ɔ��f
		BulletPos = VTransform(vHeadPos, matrix);


		//===================�s��ɂ��e�̔��ˈʒu�ύX==============================

		cShotManager.RequestPlayerShot(BulletPos, vSpd, 0.0f);

		vHeadPos.x -= (vSpd.x * 0.5f);
		vHeadPos.z -= (vSpd.z * 0.5f);

		TEST_BULLETPOS = BulletPos;
	}

	

	//�����Ă�������`�F�b�N
	CheckDir();
}

//�v���C���[�̂߂荞�ݏC��
void CPlayer::SetPos(VECTOR NewPos)
{
	NextPos = NewPos;
}


//�����Ă�������`�F�b�N
void CPlayer::CheckDir()
{
	if (NextPos.x > m_vPos.x)
	{
		//�E�ɓ����Ă���
		Dir[0] = true;
	}
	if (NextPos.x < m_vPos.x)
	{
		//���ɓ����Ă���
		Dir[1] = true;
	}
	if (NextPos.y > m_vPos.y)
	{
		//��ɓ����Ă���
		Dir[2] = true;
	}
	if (NextPos.y < m_vPos.y)
	{
		//���ɓ����Ă���
		Dir[3] = true;
	}
	if (NextPos.z > m_vPos.z)
	{
		//���ɓ����Ă���
		Dir[4] = true;
	}
	if (NextPos.z < m_vPos.z)
	{
		//��O�ɓ����Ă���
		Dir[5] = true;
	}

}