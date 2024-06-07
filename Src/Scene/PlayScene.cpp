#include "PlayScene.h"
#include "../Input/Input.h"
#include "../SoundManager/SoundManager.h"


//��`�֘A----------------------------------

//------------------------------------------


//------------------------------------------
//�R���X�g���N�^
//------------------------------------------
CPlayScene::CPlayScene()
{
	//�ЂƂ܂��������ɂ��Ă���
	eSceneID = PLAY_SCENE_INIT;
}


//------------------------------------------
//�f�X�g���N�^
//------------------------------------------
CPlayScene::~CPlayScene()
{
	//�O�̈�
	Exit();
}

//------------------------------------------
//���t���[���Ăԏ���
//------------------------------------------
int CPlayScene::Loop()
{
	int iRet = 0;
	switch (eSceneID)
	{
	case PLAY_SCENE_INIT:
		Init();
		eSceneID = PLAY_SCENE_LAOD;
		break;

	case PLAY_SCENE_LAOD:
		Load();
		CSoundManager::Play(CSoundManager::SOUNDID_BGM, DX_PLAYTYPE_LOOP);
		eSceneID = PLAY_SCENE_LOOP;
		break;

	case PLAY_SCENE_LOOP:
		Step();
		break;

	case PLAY_SCENE_END:
		Exit();
		eSceneID = PLAY_SCENE_INIT;
		iRet = 1;
		break;

	default:
		break;
	}

	return iRet;
}


//-----------------------------------
//�X�V����
//-----------------------------------
void CPlayScene::Draw()
{
	if (eSceneID == PLAY_SCENE_LOOP)
	{
		cSky.Draw();
		cGround.Draw();
		cPlayer.Draw();
		cEnemyManager.Draw();
		cShotManager.Draw();
		cCameraManager.Draw();

	}
}


//-----------------------------------
//������
//-----------------------------------
void CPlayScene::Init()
{
	//�J����������
	cCameraManager.Init();
	cCameraManager.SetNearFar(5.0f, 5000.0f);
	//�v���C���[������
	cPlayer.Init();
	//�G������
	cEnemyManager.Init();
	//�t�B�[���h������
	cGround.Init();
	//�V��������
	cSky.Init();
	//�e������
	cShotManager.Init();

}


//-----------------------------------
//�I������
//-----------------------------------
void CPlayScene::Exit()
{
	cCameraManager.Exit();
	cPlayer.Exit();
	cEnemyManager.Exit();
	cShotManager.Exit();
}


//-----------------------------------
//�f�[�^���[�h
//-----------------------------------
void CPlayScene::Load()
{
	cPlayer.Load();
	cEnemyManager.Load();
	cShotManager.Load();
}


//-----------------------------------
//���t���[���Ăԏ���
//-----------------------------------
void CPlayScene::Step()
{
	if (CInput::IsKeyPush(KEY_INPUT_RETURN))
	{
		eSceneID = PLAY_SCENE_END;
	}

	//�V������
	cSky.Step(cPlayer.GetPosition(), cPlayer.GetRotateY());
	cSky.Loop();

	//�v���C���[�X�V����
	if (cCameraManager.GetCameraID() == CCameraManager::CAMERA_ID_PALY)
	{
		cPlayer.Step(cShotManager);
		cPlayer.Update();
		cEnemyManager.Step();
		cShotManager.Step();

		//�����蔻��
		CCollisionManager::CheckHitShotToEnemy(cEnemyManager, cShotManager);
	}

	//�J�����̐؂�ւ�����
	if (CInput::IsKeyPush(KEY_INPUT_C))
	{
		cCameraManager.ChangeCamera(CCameraManager::CAMERA_ID_DEBUG);
	}
	else if (CInput::IsKeyPush(KEY_INPUT_V))
	{
		cCameraManager.ChangeCamera(CCameraManager::CAMERA_ID_PALY);
	}
	//�J�����X�V����
	cCameraManager.Step(cPlayer.GetPosition(), cPlayer.GetRotateY());

}
