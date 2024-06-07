#include "Tank_Head.h"
#include "../Input/Input.h"
#include <math.h>
#include "../MyLibrary/MyLibrary.h"

//��`�֘A
static const char PLAYER_MODEL_HEAD_PATH[] = { "Data/Tank/tank_Head.x" };	//�^���N�̃t�@�C����(��)
static const float ROTATE_SPEED = 0.05f;									//�v���C���[�̉�]���x
static const float MOVE_SPEED = 0.5f;										//�v���C���[�̈ړ����x


//----------------------------
//�R���X�g���N�^
//----------------------------
CTank_H::CTank_H()
{

	//����������
	memset(&vSpeed, 0, sizeof(VECTOR));
	eState = PLAYER_STATE_NORMAL;

}

//----------------------------
//�f�X�g���N�^
//----------------------------
CTank_H::~CTank_H()
{
	Delete();
	Exit();
}

//----------------------------
//������
//----------------------------
void CTank_H::Init()
{
	Init(VGet(0.0f, 10.0f, 0.0f), VGet(0.0f, DX_PI_F, 0.0f));
}

//----------------------------
//������
//----------------------------
void CTank_H::Init(VECTOR Pos, VECTOR Rot)
{
	CModel::Init();

	m_vPos = Pos;
	m_vRot = Rot;
	memset(&vSpeed, 0, sizeof(VECTOR));
	eState = PLAYER_STATE_NORMAL;


}

//----------------------------
//�f�[�^�֘A�̃��[�h
//----------------------------
void CTank_H::Load()
{
	LoadModel(PLAYER_MODEL_HEAD_PATH);
}

//----------------------------
//�f�[�^�֘A�̔j��
//----------------------------
void CTank_H::Delete()
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
void CTank_H::Exit()
{
	//�������J���Ȃǂ��L�q
	CModel::Exit();
}


//----------------------------
//���t���[���Ăԏ���
//----------------------------
void CTank_H::Step(CShotManager& cShotManager)
{
	VECTOR OldMousePos = VGet(MousePosX, MousePosY, 0.0f);

	GetMousePoint(&MousePosX, &MousePosY);
	VECTOR MousePos = VGet(MousePosX, MousePosY, 0.0f);

	VECTOR Move = MyMath::SubVec(MousePos, OldMousePos);
	Move = MyMath::Scale(Move, 0.01f);

	m_OldPos = m_vPos;

	//�L�����N�^�[�̉�]
	m_vRot.y -= Move.y;

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

	//���͂����L�[���ƃv���C���[�̊p�x����A�ړ����x�����߂�
	vSpeed.x = sin(m_vRot.y) * fSpd;
	vSpeed.z = cos(m_vRot.y) * fSpd;
	//�ړ����x�����݂̍��W�ɉ��Z����
	m_vPos.x += vSpeed.x;
	m_vPos.z += vSpeed.z;


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
}

