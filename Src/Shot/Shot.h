#pragma once
#include <DxLib.h>

const int SHOTRADIUS	(1);

class CShot
{
private:
	VECTOR m_vPos;			//���W
	VECTOR m_vSpeed;		//�ړ����x
	float m_Radius;			//���f���̔��a
	int iHndl;				//���f���̃n���h��
	bool isActive;			//�����t���O


public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CShot();
	~CShot();

	//������
	void Init();

	//�f�[�^���[�h
	void Load(int iMdlHndl);

	//�I������
	void Exit();

	//���t���[���Ăԏ���
	void Step();

	//�`�揈��
	void Draw();

	//���N�G�X�g
	//m_vPos		�F �������W
	//m_vSpeed	�F �ړ����x(�����x�N�g����)
	//return	�F true = ���N�G�X�g����, false = ���s
	bool RequestShot(const VECTOR& m_vPos, const VECTOR& m_vSpeed);

	//��������
	//return �@�F true = ����, false = ���s
	bool IsActive() { return isActive; }

	//���W�擾
	VECTOR GetPosition(VECTOR& vPos)
	{
		return vPos = m_vPos;
	}


	//���f���̔��a�擾
	float GetRadius()
	{
		return m_Radius;
	}

	//�����蔻��̏���
	void HitCalc()
	{
		//����������t���O������
		isActive = false;
	}
};