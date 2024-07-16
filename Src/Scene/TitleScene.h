#pragma once

class CTitleScene
{
private:
	enum tagTITLE_SCENE
	{
		TITLE_SCENE_INIT,
		TITLE_SCENE_LAOD,
		TITLE_SCENE_LOOP,
		TITLE_SCENE_END,

		TITLE_SCENE_NUM
	};

	tagTITLE_SCENE eSceneID;

	int TitleHndl;

	enum TRANSPARENCY
	{
		Null,
		TransTrue,
		Transfalse,
	};

	TRANSPARENCY Trans;

public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CTitleScene();
	~CTitleScene();

	//������
	void Init();

	//�ǂݍ���
	void Load();

	//���[�v����
	int Loop();

	//���g�̏���
	void Step();

	//�`�揈��
	void Draw();

	//�㏈��
	void Exit();

};
