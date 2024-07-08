#pragma once
#include <DxLib.h>
#include <math.h>
#include "../Object/Model/Model.h"
#include "../Shot/ShotManager.h"
#include "../Input/Input.h"
#include "../MyLibrary/MyLibrary.h"
#include "../Draw3D/Draw3D.h"

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

	int HeadHndl;			//�����̃��f��
	VECTOR vHeadPos;		//�����̍��W
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

	//�����Ă�������`�F�b�N
	void CheckDir(bool *Dir);

	//���W�擾
	inline VECTOR GetPosition() { return m_vPos; }

	//NextPos�擾
	inline VECTOR GetNextPos() { return NextPos; }

	//Y���p�x�擾
	inline VECTOR GetRotate() { return m_vRot; }

	//Y���p�x�擾

	inline float GetRotateY() { return m_vRot.y; }
	

	//�v���C���[�̍X�V���W�擾
	void SetPosX(VECTOR NewPos);
	//�v���C���[�̍X�V���W�擾
	void SetPosY(VECTOR NewPos);
	//�v���C���[�̍X�V���W�擾
	void SetPosZ(VECTOR NewPos);


};
