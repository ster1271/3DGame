#pragma once
#include <DxLib.h>
#include "../SoundManager/SoundManager.h"

const int ENEMYRADIUS		(5);
const int MAX_LIFE			(3);


class CEnemyBase
{
private:
	VECTOR m_vPos;			//���W
	VECTOR m_vSpeed;		//�ړ����x
	int m_Life;				//�G�̃��C�t
	float m_Radius;			//���f���̔��a
	int m_iHndl;			//���f���n���h��
	bool m_isActive;		//�����t���O

	int HitCount;			//�e�̓��������񐔊i�[

public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CEnemyBase();
	~CEnemyBase();

	//������
	void Init();

	//�f�[�^���[�h
	void Load(int iMdlHndl);

	//�I������
	void Exit();

	//���t���[���Ăԏ���
	void Step();

	//�`�揈��
	void Draw();

	//���N�G�X�g
	bool RequestEnemy(const VECTOR& vPos, const VECTOR& vSpeed);

	//��������
	bool IsActive() { return m_isActive; }

	//���W�擾
	void GetPosition(VECTOR &vPos) { vPos = m_vPos; }

	//���f���̔��a�擾
	float GetRadius()
	{
		return m_Radius;
	}

	//�����蔻��̏���
	void HitCalc()
	{
		CSoundManager::Play(CSoundManager::SOUNDID_SE_EXPLORE);
		m_Life -= 1;
		m_vPos.z += 2.0f;
		HitCount++;

		//���C�t���Ȃ��Ȃ�����t���O������
		if (m_Life <= 0)
		{
			HitCount = 0;
			m_isActive = false;
		}
	}

};