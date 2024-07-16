#include "DxLib.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "../Input/Input.h"

#define TITLE_PATH		("Data/Title/Title.png")

//-------------------------------------
//�R���X�g���N�^
//-------------------------------------
CTitleScene::CTitleScene()
{
	//�Ƃ肠�����������Ɉړ�������
	eSceneID = TITLE_SCENE_INIT;
}
//-------------------------------------
//�f�X�g���N�^
//-------------------------------------
CTitleScene::~CTitleScene()
{
	Exit();
}

//-------------------------------------
//������
//-------------------------------------
void CTitleScene::Init()
{
	memset(&TitleHndl, -1, sizeof(TitleHndl));
	Trans = Null;

	eSceneID = TITLE_SCENE_LAOD;
}

//-------------------------------------
//���[�h
//-------------------------------------
void CTitleScene::Load()
{
	TitleHndl = LoadGraph(TITLE_PATH);

	eSceneID = TITLE_SCENE_LOOP;
}


//-------------------------------------
//���[�v���鏈��
//-------------------------------------
int CTitleScene::Loop()
{
	int iRet = eSceneID == TITLE_SCENE_END ? 1 : 0;

	void (CTitleScene:: * TitleScene[])() = { &CTitleScene::Init, &CTitleScene::Load, &CTitleScene::Step, &CTitleScene::Exit };
	(this->*TitleScene[eSceneID])();

	return iRet;
}


//-------------------------------------
//���g�̏���
//-------------------------------------
void CTitleScene::Step()
{
	if (CInput::IsKeyPush(KEY_INPUT_RETURN))
	{
		eSceneID = TITLE_SCENE_END;
	}
}

//-------------------------------------
//�`�揈��
//-------------------------------------
void CTitleScene::Draw()
{
	DrawGraph(0, 0, TitleHndl, true);


	//DrawString(0, 0, "�^�C�g����ʂł�", GetColor(255, 255, 255));
	//DrawString(0, 15, "Enter�ŃV�[���ړ�", GetColor(255, 255, 255));

}

//-------------------------------------
//�㏈��1
//-------------------------------------
void CTitleScene::Exit()
{
	if (TitleHndl != -1)
	{
		DeleteGraph(TitleHndl);
	} 
	eSceneID = TITLE_SCENE_INIT;
}
