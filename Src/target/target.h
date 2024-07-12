#pragma once
#include "../Object/object.h"

#define MAX_NUM		(15)

class CTarget :public CObject
{
private:
	int ImgHndl[MAX_NUM];

	VECTOR Pos[MAX_NUM];
	VECTOR Scale;

public:
	//������
	void Init();

	//���f���ǂݍ���
	void Load();

	//���f���`��
	void Draw();

	//���t���[���s������
	void Step();
};
