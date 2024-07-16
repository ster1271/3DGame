#include "target.h"

static const char TARGET_PATH[] = { "Data/target/target.x" };

//�R���X�g���N�^
CTarget::CTarget()
{
	for (int targetIndex = 0; targetIndex < TARGET_NUM; targetIndex++)
	{
		//�Ƃ肠����-1�����Ă���
		ImgHndl[targetIndex] = -1;
		//�t���O�����ׂ�false�ɂ���
		IsActive[targetIndex] = false;
		//�����_���ŏꏊ��ݒ�
		Pos[targetIndex] = VGet(0.0f, 0.0f, 0.0f);
		//�������W�i�[���Ă���
		FixPos[targetIndex] = Pos[targetIndex];
		//�X�s�[�h�����ꂼ��ς���
		Speed[targetIndex] = VGet(0.0f, 0.0f, 0.0f);
	}
	Scale = VGet(0.0f, 0.0f, 0.0f);
	Rot = VGet(0.0f, 0.0f, 0.0f);
	Radius = 0.0f;
	TargetCount = TARGET_NUM;
}

//������
void CTarget::Init()
{
	for (int targetIndex = 0; targetIndex < TARGET_NUM; targetIndex++)
	{
		//�Ƃ肠����-1�����Ă���
		ImgHndl[targetIndex] = -1;
		//�t���O�����ׂ�true�ɂ���
		IsActive[targetIndex] = true;
		//�����_���ŏꏊ��ݒ�
		Pos[targetIndex] = VGet((float)GetRand(100.0f)-50.0f, (float)GetRand(20.0f)+ 10.0f, (float)GetRand(400.0f) + 200.0f);
		//�������W�i�[���Ă���
		FixPos[targetIndex] = Pos[targetIndex];
		//�X�s�[�h�����ꂼ��ς���
		Speed[targetIndex] = VGet((float)GetRand(3.0f), (float)GetRand(3.0f), (float)GetRand(3.0f));
	}
	Scale = VGet(0.1f, 0.1f, 0.1f);
	Rot = VGet(DX_PI_F / 2, 0.0f, 0.0f);
	Radius = RADIUS;
	TargetCount = TARGET_NUM;
}


//�㏈��
void CTarget::Exit()
{
	for (int targetIndex = 0; targetIndex < TARGET_NUM; targetIndex++)
	{
		ImgHndl[targetIndex] = -1;
		IsActive[targetIndex] = false;
		//���ׂ�0.0f�ɂ���
		Pos[targetIndex] = VGet(0.0f, 0.0f, 0.0f);
		//���ׂ�0.0f�ɂ���
		FixPos[targetIndex] = VGet(0.0f, 0.0f, 0.0f);
		//���ׂ�0.0f�ɂ���
		Speed[targetIndex] = VGet(0.0f, 0.0f, 0.0f);
	}
	Scale = VGet(0.0f, 0.0f, 0.0f);
}

//���f���ǂݍ���
void CTarget::Load()
{
	for (int targetIndex = 0; targetIndex < TARGET_NUM; targetIndex++)
	{
		ImgHndl[targetIndex] = MV1LoadModel(TARGET_PATH);
	}
}

//���f���`��
void CTarget::Draw()
{
	for (int targetIndex = 0; targetIndex < TARGET_NUM; targetIndex++)
	{
		if (IsActive[targetIndex] == true)
		{
			MV1DrawModel(ImgHndl[targetIndex]);
			//DrawSphere3D(Pos[targetIndex], Radius, 16, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);
		}
	}

}

//���t���[���s������
void CTarget::Step()
{
	//�ړ��͈�
	VECTOR Renge = VGet(100.0f, 100.0f, 100.0f);


	for (int targetIndex = 0; targetIndex < TARGET_NUM; targetIndex++)
	{
		Pos[targetIndex].x += Speed[targetIndex].x;
		//�ݒ�l���傫���Ȃ�΃X�s�[�h�l��ύX����
		if (Pos[targetIndex].x > FixPos[targetIndex].x + Renge.x)
		{
			Speed[targetIndex] = VScale(Speed[targetIndex], -1.0f);
		}
		//�ݒ�l��菬�����Ȃ�΃X�s�[�h�l��ύX����
		else if (Pos[targetIndex].x < FixPos[targetIndex].x - Renge.x)
		{
			Speed[targetIndex] = VScale(Speed[targetIndex], -1.0f);
		}
	}
}

void CTarget::UpDate()
{
	//���W�E�X�P�[���E��]�l�̃A�b�v�f�[�g
	for (int targetIndex = 0; targetIndex < TARGET_NUM; targetIndex++)
	{
		MV1SetPosition(ImgHndl[targetIndex], Pos[targetIndex]);
		MV1SetRotationXYZ(ImgHndl[targetIndex], Rot);
		MV1SetScale(ImgHndl[targetIndex], Scale);
	}
}