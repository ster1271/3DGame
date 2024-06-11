#pragma once
#include <DxLib.h>
#include "../Shot/ShotManager.h"
#include "../Object/Model/Model.h"

class CPlayer : public CModel
{
private:
	//�v���C���[�̏��
	enum tagPlayerState
	{
		PLAYER_STATE_NORMAL,	//�ҋ@�E������
		PLAYER_STATE_JUMP,		//�W�����v��

		PLAYER_STATE_NUM
	};

	int HeadHndl;
	VECTOR vHeadRot;		//�����̉�]

	VECTOR vSpeed;			//�ړ����x
	tagPlayerState eState;	//�v���C���[�̏��

public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CPlayer();
	~CPlayer();

	//������
	void Init();
	void Init(VECTOR vPos, VECTOR vRot);

	//�f�[�^�֘A�̃��[�h
	void Load();

	//�f�[�^�֘A�̔j��
	void Delete();

	//�I������
	void Exit();

	//�`�揈��
	void Draw();

	//�X�V����
	void Update();

	//���t���[���Ăԏ���
	void Step(CShotManager& cShotManager);

	//���W�擾
	inline VECTOR GetPosition() { return m_vPos; }
	//Y���p�x�擾
	inline float GetRotateY() { return m_vRot.y; }

};
