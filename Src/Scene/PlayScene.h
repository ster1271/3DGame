#pragma once
#include <DxLib.h>

#include "../Camera/CameraManager.h"
#include "../Player/Player.h"
#include "../Object/Ground/Ground.h"
#include "../Object/Sky/Sky.h"
#include "../Shot/ShotManager.h"
#include "../Enemy/EnemyManager.h"
#include "../CollisionManager/CollisionManager.h"

class CPlayScene
{
private:
	enum tagPLAY_SCENE
	{
		PLAY_SCENE_INIT,
		PLAY_SCENE_LAOD,
		PLAY_SCENE_LOOP,
		PLAY_SCENE_END,

		PLAY_SCENE_NUM
	};

	CCameraManager cCameraManager;			//�J�����}�l�[�W���[
	CPlayer cPlayer;						//�v���C���[
	tagPLAY_SCENE eSceneID;					//�V�[���ۑ�
	CGround cGround;						//�t�B�[���h
	CSky cSky;								//�V��
	CShotManager cShotManager;				//�e�}�l�[�W���[
	CEnemyManager cEnemyManager;			//�G�}�l�[�W���[

public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CPlayScene();
	~CPlayScene();

	//�J��Ԃ��s������
	int Loop();

	//�`�揈��
	void Draw();

private:
	//������
	void Init(void);

	//�I������
	void Exit();

	//�f�[�^���[�h
	void Load();

	//���t���[���Ăԏ���
	void Step();

};