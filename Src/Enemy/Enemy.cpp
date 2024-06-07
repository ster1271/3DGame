#include"Enemy.h"
#include <math.h>

//--------------------------------------
//�R���X�g���N�^
//--------------------------------------
CEnemyBase::CEnemyBase()
{
	//�ЂƂ܂�������
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vSpeed, 0, sizeof(VECTOR));
	m_iHndl = -1;
	m_Life = MAX_LIFE;
	m_isActive = false;
	HitCount = 0;
	m_Radius = 0;
}

//--------------------------------------
//�f�X�g���N�^
//--------------------------------------
CEnemyBase::~CEnemyBase()
{
	//�{���͕K�v�Ȃ����O�̂���
	Exit();
}

//--------------------------------------
//������
//--------------------------------------
void CEnemyBase::Init()
{
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vSpeed, 0, sizeof(VECTOR));
	m_iHndl = -1;
	m_isActive = false;
	m_Radius = ENEMYRADIUS;
}

//--------------------------------------
//�I������
//--------------------------------------
void CEnemyBase::Exit()
{
	//���f���n���h�����
	if (m_iHndl != -1)
	{
		MV1DeleteModel(m_iHndl);
		m_iHndl = -1;
	}
}

//--------------------------------------
//�f�[�^���[�h
//--------------------------------------

void CEnemyBase::Load(int iMdlHndl)
{
	if (m_iHndl == -1)
	{
		m_iHndl = MV1DuplicateModel(iMdlHndl);
		MV1SetScale(m_iHndl, VGet(5.0f, 5.0f, 5.0f));
	}
}


//--------------------------------------
//�`�揈��
//--------------------------------------
void CEnemyBase::Draw()
{
	if (m_isActive)
	{
		MV1DrawModel(m_iHndl);
		VECTOR vPos = m_vPos;
		vPos.y += m_Radius;

		//�f�o�b�N�p---------------------------------------------------------------------
		int R, G, B;
		B = 255;
		R = G = 0;


		switch (HitCount)
		{
		//�����������ĂȂ��Ƃ�
		case 0:
			break;
			B = 255;
			R = G = 0;
		//��񓖂������Ƃ�
		case 1:
			G = 255;
			R = B = 0;

			break;
		//��񓖂������Ƃ�
		case 2:
			R = 255;
			G = B = 0;

			break;

		default:
			break;
		}
		DrawSphere3D(vPos, m_Radius, 16, GetColor(R, G, B), GetColor(R, G, B), false);
		//�f�o�b�N�p---------------------------------------------------------------------
	}

}


//--------------------------------------
//���N�G�X�g
//--------------------------------------
bool CEnemyBase::RequestEnemy(const VECTOR &vPos, const VECTOR &vSpeed)
{
	//���łɏo�����Ă���
	if (m_isActive)
	{
		return false;
	}

	m_vPos = vPos;
	m_vSpeed = vSpeed;
	m_isActive = true;

	//��x���W�X�V���Ă���
	MV1SetPosition(m_iHndl, m_vPos);
	return true;
}

//--------------------------------------
//���t���[���Ăԏ���
//--------------------------------------
void CEnemyBase::Step()
{
	if (!m_isActive)
	{
		return;
	}

	//���W�ɑ��x�����Z
	m_vPos = VAdd(m_vPos, m_vSpeed);
	//���͈͂𒴂��������
	float fLength = 300.0f;
	if (m_vPos.x > fLength || m_vPos.x < -fLength
		|| m_vPos.z > fLength || m_vPos.z < -fLength)
	{
		m_isActive = false;
	}

	//���W�X�V
	MV1SetPosition(m_iHndl, m_vPos);
}




