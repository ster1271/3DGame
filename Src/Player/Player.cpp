#include "Player.h"


//��`�֘A
static const char MODEL_PATH[] = { "Data/il/�������邽��.pmx" };
static const char PLAYER_MODEL_PATH[] = { "Data/Tank/Tank.x" };					//�t�@�C����
static const char PLAYER_MODEL_FOUND_PATH[] = { "Data/Tank/tank_M.x" };		//�^���N�̃t�@�C����(�{��)
static const char PLAYER_MODEL_HEAD_PATH[] = { "Data/Tank/tank_H.x" };		//�^���N�̃t�@�C����(��)

static const float ROTATE_SPEED = 0.05f;							//�v���C���[�̉�]���x
static const float MOVE_SPEED = 0.5f;								//�v���C���[�̈ړ����x


//----------------------------
//�R���X�g���N�^
//----------------------------
CPlayer::CPlayer()
{

	//����������
	memset(&vSpeed, 0, sizeof(VECTOR));
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
	eState = PLAYER_STATE_NORMAL;

}

//----------------------------
//�f�[�^�֘A�̃��[�h
//----------------------------
void CPlayer::Load()
{
	LoadModel(PLAYER_MODEL_FOUND_PATH);
	HeadHndl = MV1LoadModel(PLAYER_MODEL_HEAD_PATH);
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

	MV1SetPosition(HeadHndl, m_vPos);
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

	//�}�E�X����(��)
	VECTOR OldMousePos = VGet(MousePosX, MousePosY, 0.0f);

	/*SetMousePoint(0, 0);*/
	GetMousePoint(&MousePosX, &MousePosY);
	VECTOR MousePos = VGet(MousePosX, MousePosY, 0.0f);

	VECTOR Move = MyMath::SubVec(MousePos, OldMousePos);
	Move = MyMath::Scale(Move, 0.001f);

	vHeadRot.y += Move.x;

	//�L�����N�^�[�̉�]
	if (CInput::IsKeyKeep(KEY_INPUT_A))
	{
		m_vRot.y -= 0.05f;
	}
	else if (CInput::IsKeyKeep(KEY_INPUT_D))
	{
		m_vRot.y += 0.05f;
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

	//���͂����L�[���ƃv���C���[�̊p�x����A�ړ����x�����߂�
	vSpeed.x = sin(m_vRot.y) * fSpd;
	vSpeed.z = cos(m_vRot.y) * fSpd;
	//�ړ����x�����݂̍��W�ɉ��Z����
	NextPos.x += vSpeed.x;
	NextPos.z += vSpeed.z;


	if (CInput::IsKeyPush(KEY_INPUT_SPACE))
	{
		//��Ԃ̑ł��o��������o��悤�ɍ��W��ύX����
		VECTOR BulletPos = m_vPos;

		//���ˈʒu���W
		VECTOR SetPos = BulletPos;
		SetPos.z = -70.0f;
		SetPos.y = 5.0f;
		SetPos.x = 0.0f;


		//���x�̓v���C���[�Ɠ������@�ňړ����������߂�
		const float SHOT_SPEED = 5.0f;
		VECTOR vSpd;
		
		vSpd.x = sinf(m_vRot.y) * -SHOT_SPEED;
		vSpd.z = cosf(m_vRot.y) * -SHOT_SPEED;
		vSpd.y = 0.0f;

		//===================�s��ɂ��e�̔��ˈʒu�ύX==============================
		
		//�@���W�����_�ɖ߂��s����쐬
		MATRIX mCenter = MGetTranslate(VScale(BulletPos, -1.0f));
		//�A���_���W���猳�̍��W�ɖ߂��s����쐬
		MATRIX mPosition = MGetTranslate(BulletPos);

		//�B�e�̈ʒu�Ɉړ�����s�������
		MATRIX mMove = MGetIdent();
		mMove = MGetTranslate(SetPos); 

		//�CX����]����
		MATRIX rotX = MGetRotX(m_vRot.x);

		//�DY����]����
		MATRIX rotY = MGetRotY(m_vRot.y);

		/* X -> Y -> Z�̏��ԂŌv�Z*/
		
		//�E���_���W����ړ��ʂ𑝂₷
		MATRIX matrix = MMult(mCenter, mMove);

		//�F��]�s��v�Z
		matrix = MMult(matrix, rotX);
		matrix = MMult(matrix, rotY);

		//�G���̈ʒu�ɖ߂�
		matrix = MMult(matrix, mPosition);

		//�H���߂��s������W�ɔ��f
		BulletPos = VTransform(BulletPos, matrix);


		//===================�s��ɂ��e�̔��ˈʒu�ύX==============================

		cShotManager.RequestPlayerShot(BulletPos, vSpd);
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