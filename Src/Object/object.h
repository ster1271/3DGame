#pragma once
#include <DxLib.h>

class CObject
{

public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CObject();
	~CObject();

protected:
	//���W
	VECTOR cPos;

	//��]�l
	VECTOR cRotate;

	//�n���h��
	int iHndl;
};
