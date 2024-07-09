#pragma once
#include "vector"
#include "../Model/Model.h"

const int MAX_NUM = 20;

class CBox : public CModel
{
private:
	int iHndlCopy[MAX_NUM];		//���f���̃R�s�[
	VECTOR m_Pos[MAX_NUM];

public:
	void Init();

	//���f���̓ǂݍ���
	void Load();

	//���f���̕`��
	void Draw();

	//���f���̔j��
	void Exit();

	//���f���̍X�V
	void Update();



};
