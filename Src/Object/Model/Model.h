#pragma once
#include <DxLib.h>

#define ANIMSTATE_NORMAL	0
#define ANIMESTATE_LOOP		1
#define ANIMESTATE_END		2

class CModel
{
protected:
	//�A�j���֘A�̃f�[�^���܂Ƃ߂��\����
	typedef struct 
	{
		float m_MaxAnimeTime;	//�A�j���S�Đ�����
		float m_AnimeTime;		//�A�j���Đ�����
		float m_AddTime;		//�Đ����x
		int m_iHndl;			//�A�j���n���h��
		int m_AnimeId;			//�Đ����̃A�j��ID
		int m_iState;			//�A�j���̏��
	}ANIM_DATA;

	VECTOR m_vPos;				//���W
	VECTOR m_OldPos;			//�O���W
	VECTOR m_vRot;				//��]�p�x
	VECTOR m_vScale;			//�g��k����
	VECTOR m_HarfPos;			//�T�C�Y�̔����̍��W�x�N�g��
	ANIM_DATA m_sAnimeData;		//�A�j���Đ��֘A�f�[�^
	int MousePosX, MousePosY;	//�}�E�X���W
	int m_iHndl;				//���f���n���h��

public:
	CModel();
	virtual ~CModel();

	//������
	virtual void Init();

	//�I������
	virtual void Exit();

	//�X�V����
	virtual void Update();

	//���f���`��
	virtual void Draw();


	//�摜�ǂݍ��݊֘A
	//���f���̒ʏ탍�[�h
	bool LoadModel(const char* pFileName);

	//���f���̃R�s�[���[�h
	bool DuplicateModel(int iSrcHndl);

	//���f���f�[�^�폜
	void DeleteModel();


	//�A�j���[�V�����֘A�֐�

	//�A�j���A�b�v�f�[�g
	//�X�V�����͖��t���[���Ăяo��
	void UpdateAnime();

	//�A�j�����N�G�X�g
	// iAnimeID    : �A�^�b�`����A�j���ԍ�
	// iAnimeSpd   : �A�j���Đ����x
	// iAnimeHundl : �A�j���[�V�����������Ă��郂�f���̃n���h��(-1�Ȃ�΂��̃��f���̃A�j���g�p)
	// NameCheck   : �ʃ��f���̃A�j���[�V�������g�p����ꍇ�A���f���̃t���[��������v���ĂȂ��ꍇ
	//				 �A�j�����A�^�b�`���邩(iAnimeHundl = -1�̏ꍇ�͖���)
	void Reqest(int iAnimeID, float iAnimeSpd, int iAnimeHundl = -1, bool NameChech = false);

	//���[�v�A�j�����N�G�X�g
	//�A�j���[�V�������ŏI�t���[���ɂȂ�����ŏ��ɖ߂�
	void ReqestLoop(int iAnimeID, float iAnimeSpd, int iAnimeHundl = -1, bool NameChech = false);

	//�G���h���[�v���N�G�X�g
	//�A�j���[�V�������ŏI�t���[���ɂȂ����炻�̂܂܎~�܂�
	void RequestEndLoop(int iAnimeID, float iAnimeSpd, int iAnimeHundl = -1, bool NameChech = false);


private:
	//���S�ɃA�j���[�V�������f�^�b�`
	void DetachAnime();
};
