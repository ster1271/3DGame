#include "target.h"

static const char TARGET_PATH[] = { "Data/target/target.x" };

//������
void CTarget::Init()
{
	for (int i = 0; i < MAX_NUM; i++)
	{
		ImgHndl[i] = -1;
		Pos[i] = VGet(GetRand(100.0f), GetRand(20.0f), GetRand(100.0f));
	}

	Scale = VGet(0.3f, 0.3f, 0.03f);
}

//���f���ǂݍ���
void CTarget::Load()
{
	for (int i = 0; i < MAX_NUM; i++)
	{
		ImgHndl[i] = MV1LoadModel(TARGET_PATH);
	}
}

//���f���`��
void CTarget::Draw()
{

}

//���t���[���s������
void CTarget::Step()
{

}