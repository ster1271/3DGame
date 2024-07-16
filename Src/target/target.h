#pragma once
#include "../Object/object.h"

#define TARGET_NUM		(15)
#define RADIUS		(10)

class CTarget :public CObject
{
private:
	int ImgHndl[TARGET_NUM];

	VECTOR Pos[TARGET_NUM];
	VECTOR FixPos[TARGET_NUM];
	VECTOR Speed[TARGET_NUM];
	VECTOR Rot;
	VECTOR Scale;
	float Radius;

	bool IsActive[TARGET_NUM];
	int TargetCount;

public:
	//�R���X�g���N�^
	CTarget();

	//������
	void Init();

	//���f���ǂݍ���
	void Load();

	//�㏈��
	void Exit();

	//���f���`��
	void Draw();

	//���t���[���s������
	void Step();
	void UpDate();

	//�I���W�擾
	VECTOR GetPos(int TargetIndex)
	{
		return Pos[TargetIndex];
	}
	//�t���O�擾
	bool GetActive(int TargetIndex)
	{
		return IsActive[TargetIndex];
	}

	//���a�擾
	float GetRadius()
	{
		return Radius;
	}

	//�J�E���g�擾
	int GetCount()
	{
		return TargetCount;
	}

	//�t���O��܂�
	void SetActive(int TargetIndex)
	{
		//�t���O��܂�
		IsActive[TargetIndex] = false;
		//�J�E���g�����炷
		TargetCount--;
		if (TargetCount < 0)
		{
			TargetCount = 0;
		}
	}
};
