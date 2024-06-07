#include "Shot.h"

//----------------------------------------
//�R���X�g���N�^
//----------------------------------------
CShot::CShot()
{
	//������
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vSpeed, 0, sizeof(VECTOR));
	iHndl = -1;
	isActive = false;
	m_Radius = 0;

}

//----------------------------------------
//�f�X�g���N�^
//----------------------------------------
CShot::~CShot()
{
	//�O�̂���
	Exit();
}

//----------------------------------------
//������
//----------------------------------------
void CShot::Init()
{
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vSpeed, 0, sizeof(VECTOR));
	iHndl = -1;
	isActive = false;
	m_Radius = SHOTRADIUS;

}


//----------------------------------------
//�I������
//----------------------------------------
void CShot::Exit()
{
	//���f���n���h�����
	if (iHndl != -1)
	{
		MV1DeleteModel(iHndl); 
		iHndl = -1;
	}
}


//----------------------------------------
//�f�[�^���[�h
//----------------------------------------
void CShot::Load(int iMdlHndl)
{
	if (iHndl == -1)
	{
		iHndl = MV1DuplicateModel(iMdlHndl);
	}
}


//----------------------------------------
//�`�揈��
//----------------------------------------
void CShot::Draw()
{
	if (isActive)
	{
		MV1DrawModel(iHndl);

		VECTOR vPos = m_vPos;
		
		/*DrawSphere3D(vPos, m_Radius, 16, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);*/

	}

}


//----------------------------------------
//���t���[���Ăԏ���
//----------------------------------------
void CShot::Step()
{
	if (!isActive) return;

	//���W�ɑ��x�����Z
	m_vPos = VAdd(m_vPos, m_vSpeed);
	//���͈͂𒴂��������
	float fLength =	300.0f;
	if (m_vPos.x > fLength || m_vPos.x < -fLength
		|| m_vPos.z > fLength || m_vPos.z < -fLength)
	{
		isActive = false;
	}

	//���W�X�V
	MV1SetPosition(iHndl, m_vPos);
	MV1SetScale(iHndl, VGet(3.0f, 3.0f, 3.0f));
}


//----------------------------------------
//���N�G�X�g
//----------------------------------------
bool CShot::RequestShot(const VECTOR &vPos, const VECTOR &vSpeed)
{
	//���łɔ��˂���Ă���
	if (isActive) return false;

	m_vPos = vPos;
	m_vSpeed = vSpeed;
	isActive = true;

	return true;
	
}

