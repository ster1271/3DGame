#include "ShotManager.h"
#include "../SoundManager/SoundManager.h"

//��`
static const char PLSHOT_MODEL_PATH[] = { "Data/shot/plshot.x" };

//------------------------------------
//�R���X�g���N�^
//------------------------------------
CShotManager::CShotManager()
{

}


//------------------------------------
//�f�X�g���N�^
//------------------------------------
CShotManager::~CShotManager()
{

}


//------------------------------------
//������
//------------------------------------
void CShotManager::Init()
{
	for (int i = 0; i < PL_SHOT_NUM; i++)
	{
		cPlayerShot[i].Init();
	}
}


//------------------------------------
//���[�h
//------------------------------------
void CShotManager::Load()
{
	//�I���W�i�����f���̓ǂݍ���
	int iHndl = MV1LoadModel(PLSHOT_MODEL_PATH);
	//���f���̕���
	for (int i = 0; i < PL_SHOT_NUM; i++)
	{
		cPlayerShot[i].Load(iHndl);
	}
	MV1DeleteModel(iHndl);
}


//------------------------------------
//�I������
//------------------------------------
void CShotManager::Exit()
{
	for (int i = 0; i < PL_SHOT_NUM; i++)
	{
		cPlayerShot[i].Exit();
	}
}

//------------------------------------
//���t���[���Ăԏ���
//------------------------------------
void CShotManager::Step()
{
	for (int i = 0; i < PL_SHOT_NUM; i++)
	{
		cPlayerShot[i].Step();
	}

	
}


//------------------------------------
//�X�V����
//------------------------------------
void CShotManager::Draw()
{
	for (int i = 0; i < PL_SHOT_NUM; i++)
	{
		cPlayerShot[i].Draw();
	}
}


//------------------------------------
//�v���C���[�̃V���b�g���N�G�X�g
//------------------------------------
void CShotManager::RequestPlayerShot(const VECTOR& vPos, const VECTOR& vSpeed)
{
	for (int i = 0; i < PL_SHOT_NUM; i++)
	{
		if (cPlayerShot[i].RequestShot(vPos, vSpeed))
		{
			CSoundManager::Play(CSoundManager::SOUNDID_SE_PLSHOT);
			break;
		}
	}
}

