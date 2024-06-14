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

	//���W�̃Y��
	VECTOR PosGap;

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

	//X���W�擾
	inline float GetPositionX() { return m_vPos.x; }

	//Y���W�擾
	inline float GetPositionY() { return m_vPos.y; }

	//Z���W�擾
	inline float GetPositionY() { return m_vPos.z; }

	//�����擾(X)
	inline float GetGapPositionX() { return PosGap.x; }

	//�����擾(Y)
	inline float GetGapPositionY() { return PosGap.y; }

	//�����擾(Z)
	inline float GetGapPositionZ() { return PosGap.y; }

	//�v���C���[�̂߂荞�ݏC��
	void SetPos(VECTOR GAP);

};
