#include "Sky.h"
#include <math.h>

//�R���X�g���N�^
CSky::CSky()
{

}

//�f�X�g���N�^
CSky::~CSky()
{

}

//������
void CSky::Init()
{
	cPos = VGet(0.0f, 0.0f, 0.0f);
	//iHndl = MV1LoadModel("Data/Sky/Sky.x");
	iHndl = MV1LoadModel("Data/Sky/���ꂢ�ȋ�(�E�ցE)_by���R.x");

	MV1SetPosition(iHndl, cPos);
	MV1SetScale(iHndl, VGet(1.0f, 1.0f, 1.0f));
}

//�`��
void CSky::Draw()
{
	MV1DrawModel(iHndl);
}

//�ʏ폈��
void CSky::Step(VECTOR vForcus, float fRot)
{
	cRotate.y += 0.0005f;

	VECTOR vDir;
	vDir.x = sinf(fRot) * 30.0f;
	vDir.z = cosf(fRot) * 30.0f;

	//���_�̍����͌Œ�
	vDir.y = 10.0f;

	SetSkyPos(vForcus, vDir);
}

//���[�v����
void CSky::Loop()
{
	MV1SetPosition(iHndl, cPos);
	MV1SetRotationXYZ(iHndl, cRotate);
}

//�ړ�����
void CSky::SetSkyPos(VECTOR vF, VECTOR dir)
{
	cPos = VAdd(vF, dir);
}