#include "Box.h"

static const char BOX_PATH[] = { "Data/Box/Box1.x" };

CBox::CBox()
{
	for (int i = 0; i < MAX_NUM; i++)
	{
		iHndlCopy[i] = 0;						//���f���̃R�s�[
		m_Pos[i] = VGet(0.0f,0.0f, 0.0f);		//�{�b�N�X�̍��W
		IsActive[i] = false;
	}
	m_Size = VGet(0.0f,0.0f, 0.0f);				//�{�b�N�X�̃T�C�Y
}

void CBox::Init()
{
	int L_Count = 0;
	int F_Count = 0;
	//�E�̕�
	for (int R_BoxNum = 0; R_BoxNum < MAX_NUM / 4; R_BoxNum++)
	{
		iHndlCopy[R_BoxNum] = -1;
		m_Pos[R_BoxNum] = VGet(300.0f, 30.0f, (50.0f * R_BoxNum) + 100.0f);
		IsActive[R_BoxNum] = true;
	}
	//���̕�
	for (int L_BoxNum = MAX_NUM / 4; L_BoxNum < MAX_NUM / 2; L_BoxNum++)
	{
		iHndlCopy[L_BoxNum] = -1;
		m_Pos[L_BoxNum] = VGet(-300.0f, 30.0f, (50.0f * L_Count) + 100.0f);
		IsActive[L_BoxNum] = true;
		L_Count++;
	}
	//��O�̕�
	for (int F_BoxNum = MAX_NUM / 2; F_BoxNum < 75; F_BoxNum++)
	{
		iHndlCopy[F_BoxNum] = -1;
		m_Pos[F_BoxNum] = VGet((50.0f * F_Count) - 300.0f, 30.0f, 50.0f * (MAX_NUM / 4));
		IsActive[F_BoxNum] = true;
		F_Count++;
	}

	//���̕�

	m_vScale = VGet(0.3f, 0.3f, 0.3f);
	m_Size = VGet(60.0f, 60.0f, 60.0f);
}

void CBox::Load()
{
	//�I���W�i�����f���̓ǂݍ���
	m_iHndl = MV1LoadModel(BOX_PATH);


	//�R�s�[�̓ǂݍ���
	for (int i = 0; i < MAX_NUM; i++)
	{
		iHndlCopy[i] = MV1DuplicateModel(m_iHndl);
	}
}

//���f���̔j��
void CBox::Exit()
{
	//�R�s�[�̍폜
	for (int i = 0; i < MAX_NUM; i++)
	{
		MV1DeleteModel(iHndlCopy[i]);
	}

	//�I���W�i���̍폜
	DeleteModel();
}


//���f���̕`��
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

//���f���̍X�V
void CBox::Update()
{
	for (int i = 0; i < MAX_NUM; i++)
	{
		MV1SetPosition(iHndlCopy[i], m_Pos[i]);
		MV1SetRotationXYZ(iHndlCopy[i], VGet(0.0f, 0.0f, 0.0f));
		MV1SetScale(iHndlCopy[i], m_vScale);
	}
}



