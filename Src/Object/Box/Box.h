#pragma once
#include "vector"
#include "../Model/Model.h"

const int MAX_NUM = 100;

class CBox : public CModel
{
private:
	int iHndlCopy[MAX_NUM];		//���f���̃R�s�[
	VECTOR m_Pos[MAX_NUM];		//�{�b�N�X�̍��W
	VECTOR m_Size;				//�{�b�N�X�̃T�C�Y
	bool IsActive[MAX_NUM];		//�{�b�N�X�t���O

public:
	CBox();

	void Init();

	//���f���̓ǂݍ���
	void Load();

	//���f���̕`��
	void Draw();

	//���f���̔j��
	void Exit();

	//���f���̍X�V
	void Update();

	//�{�b�N�X�̍��W�擾
	VECTOR GetPos(int BoxNum)
	{
		return m_Pos[BoxNum];
	}

	//�{�b�N�X�̃T�C�Y�擾
	VECTOR GetSize()
	{
		return m_Size;
	}

	//�{�b�N�X�̃T�C�Y�擾
	bool GetActive(int BoxNum)
	{
		return IsActive[BoxNum];
	}
};
