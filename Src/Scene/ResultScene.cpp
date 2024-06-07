#include "DxLib.h"
#include "SceneManager.h"
#include "ResultScene.h"
#include "../Input/Input.h"

#define RESULT_PATH		("")

//-------------------------------------
//�R���X�g���N�^
//-------------------------------------
CResultScene::CResultScene()
{
	//�Ƃ肠�����������Ɉړ�������
	eSceneID = RESULT_SCENE_INIT;
}
//-------------------------------------
//�f�X�g���N�^
//-------------------------------------
CResultScene::~CResultScene()
{
	Exit();
}

//-------------------------------------
//������
//-------------------------------------
void CResultScene::Init()
{
	memset(&ResultHndl, -1, sizeof(ResultHndl));
}

//-------------------------------------
//���[�h
//-------------------------------------
void CResultScene::Load()
{
	ResultHndl = LoadGraph(RESULT_PATH);
}


//-------------------------------------
//���[�v���鏈��
//-------------------------------------
int CResultScene::Loop()
{
	int iRet = 0;
	switch (eSceneID)
	{
	case RESULT_SCENE_INIT:
		Init();
		eSceneID = RESULT_SCENE_LAOD;
		break;

	case RESULT_SCENE_LAOD:
		Load();
		eSceneID = RESULT_SCENE_LOOP;
		break;

	case RESULT_SCENE_LOOP:
		Step();
		Draw();
		break;

	case RESULT_SCENE_END:
		Exit();
		iRet = 1;
		break;


	default:
		break;
	}

	return iRet;
}


//-------------------------------------
//���g�̏���
//-------------------------------------
void CResultScene::Step()
{
	if (CInput::IsKeyPush(KEY_INPUT_RETURN))
	{
		eSceneID = RESULT_SCENE_END;
	}
}

//-------------------------------------
//�`�揈��
//-------------------------------------
void CResultScene::Draw()
{
	//DrawGraph(0, 0, ResultHndl, true);

	
	DrawBox(0, 0, 1280, 720, GetColor(255, 0, 0), true);
	

	DrawString(0, 0, "���U���g��ʂł�", GetColor(255, 255, 255));
	DrawString(0, 15, "Enter�ŃV�[���ړ�", GetColor(255, 255, 255));

}

//-------------------------------------
//�㏈��1
//-------------------------------------
void CResultScene::Exit()
{
	if (ResultHndl != -1)
	{
		DeleteGraph(ResultHndl);
	}
}
