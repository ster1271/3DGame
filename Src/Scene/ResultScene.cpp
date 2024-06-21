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

	eSceneID = RESULT_SCENE_LAOD;
}

//-------------------------------------
//���[�h
//-------------------------------------
void CResultScene::Load()
{
	ResultHndl = LoadGraph(RESULT_PATH);

	eSceneID = RESULT_SCENE_LOOP;
}


//-------------------------------------
//���[�v���鏈��
//-------------------------------------
int CResultScene::Loop()
{
	//�V�[��ID��RESULT_SCENE_END�Ȃ�1�����łȂ����0��Ԃ�
	int iRet = eSceneID == RESULT_SCENE_END ? 1 : 0;

	//�֐��|�C���^���쐬
	void (CResultScene:: * ResultScene[])() = { &CResultScene::Init, &CResultScene::Load, &CResultScene::Step, &CResultScene::Exit };
	(this->*ResultScene[eSceneID])();

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
