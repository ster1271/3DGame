#pragma once
#include "../Input/Input.h"
#include "PlayScene.h"
#include "TitleScene.h"
#include "ResultScene.h"
#include "../SoundManager/SoundManager.h"

class SceneManager
{
private:
	enum tagSCENE
	{
		SCENE_TITLE,	//�^�C�g�����
		SCENE_PLAY,		//�Q�[����
		SCENE_RESULT,	//���U���g���

		SCENE_NUM
	};

	CPlayScene cPlayScene;
	CTitleScene cTitleScene;
	CResultScene cResultScene;
	tagSCENE eSceneID;			//�V�[���ۑ�

public:
	//�R���X�g���N�^�E�f�X�g���N�^
	SceneManager();
	~SceneManager();

	//�J��Ԃ��s������
	void Loop();

	//�`�揈��
	void Draw();

};