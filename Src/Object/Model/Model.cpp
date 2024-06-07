#include "Model.h"
#include "math.h"

#define IP	(3.14159265f)

//�R���X�g���N�^
CModel::CModel()
{
	memset(&m_sAnimeData, 0, sizeof(ANIM_DATA));
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vRot, 0, sizeof(VECTOR));
	memset(&m_vScale, 0, sizeof(VECTOR));
	memset(&m_OldPos, 0, sizeof(VECTOR));
	MousePosX = MousePosY = 0;


	m_iHndl = -1;

}

//�f�X�g���N�^
 CModel::~CModel()
{
	 Exit();
}

//������
 void CModel::Init()
 {
	 Exit();
	 m_vPos = VGet(0.0f, 0.0f, 0.0f);
	 m_vRot = VGet(0.0f, 0.0f, 0.0f);
	 m_vScale = VGet(0.1f, 0.1f, 0.1f);
	 memset(&m_sAnimeData, 0, sizeof(m_sAnimeData));
	 memset(&m_OldPos, 0, sizeof(VECTOR));
	 MousePosX = MousePosY = 0;
	 m_sAnimeData.m_iHndl = -1;
	 m_sAnimeData.m_AnimeId = -1;
 }

//�I������
 void CModel::Exit()
 {
	 DeleteModel();
 }

//�X�V����
void CModel::Update()
{
	if (m_iHndl == -1)
	{
		return;		//���f���̓ǂݍ��ݎ��s
	}

	MV1SetPosition(m_iHndl, m_vPos);
	MV1SetRotationXYZ(m_iHndl, m_vRot);
	MV1SetScale(m_iHndl, m_vScale);

	UpdateAnime();
}

//���f���`��
void CModel::Draw()
{
	if (m_iHndl == -1)
	{
		return;
	}

	MV1DrawModel(m_iHndl);

	
	//DrawLine3D(m_vPos);
	
 }


//�摜�ǂݍ��݊֘A
//���f���̒ʏ탍�[�h
bool CModel::LoadModel(const char* pFileName)
{
	if (m_iHndl != -1)
	{
		return false;	//���f���̓ǂݍ��ݍς�
	}

	m_iHndl = MV1LoadModel(pFileName);
	if (m_iHndl == -1)
	{
		return false;	//���f���̓ǂݍ��ݎ��s
	}

	return true;
}

//���f���̃R�s�[���[�h
bool CModel::DuplicateModel(int iSrcHndl)
{
	if (m_iHndl != -1)
	{
		return false;	//���f���̓ǂݍ��ݍς�
	}

	m_iHndl = MV1DuplicateModel(iSrcHndl);
	if (m_iHndl == -1)
	{
		return false;	//�ǂݍ��ݎ��s
	}

	return true;
}

//���f���f�[�^�폜
void CModel::DeleteModel()
{
	if (m_iHndl == -1)
	{
		return;
	}

	MV1DeleteModel(m_iHndl);
	m_iHndl = -1;
}

//�A�j�����N�G�X�g
void CModel::Reqest(int iAnimeID, float iAnimeSpd, int iAnimeHundl, bool NameChech)
{
	//�A�j���폜
	DetachAnime();

	//�A�j���Đ�&�e��f�[�^���Z�b�g
	m_sAnimeData.m_iHndl = MV1AttachAnim(m_iHndl, iAnimeID, iAnimeHundl, NameChech);
	m_sAnimeData.m_AnimeId = iAnimeID;
	m_sAnimeData.m_MaxAnimeTime = MV1GetAnimTotalTime(m_iHndl, m_sAnimeData.m_iHndl);
	m_sAnimeData.m_AnimeTime = 0.0f;
	m_sAnimeData.m_AddTime = iAnimeSpd;
	m_sAnimeData.m_iState = ANIMSTATE_NORMAL;
}

//���[�v�A�j�����N�G�X�g
//�A�j���[�V�������ŏI�t���[���ɂȂ�����ŏ��ɖ߂�
void CModel::ReqestLoop(int iAnimeID, float iAnimeSpd, int iAnimeHundl, bool NameChech)
{
	Reqest(iAnimeID, iAnimeSpd, iAnimeHundl, NameChech);
	//�����������[�v�ɕς���
	m_sAnimeData.m_iState = ANIMESTATE_LOOP;
}

//�G���h���[�v���N�G�X�g
//�A�j���[�V�������ŏI�t���[���ɂȂ����炻�̂܂܎~�܂�
void CModel::RequestEndLoop(int iAnimeID, float iAnimeSpd, int iAnimeHundl, bool NameChech)
{
	Reqest(iAnimeID, iAnimeSpd, iAnimeHundl, NameChech);
	//���������G���h���[�v�ɕς���
	m_sAnimeData.m_iState = ANIMESTATE_END;
}

//���S�ɃA�j���[�V�������f�^�b�`
void CModel::DetachAnime()
{
	if (m_sAnimeData.m_iHndl != -1)
	{
		MV1DetachAnim(m_iHndl, m_sAnimeData.m_iHndl);
		m_sAnimeData.m_iHndl = -1;
	}
}




//�A�j���A�b�v�f�[�g
//�X�V�����͖��t���[���Ăяo��
void CModel::UpdateAnime()
{

	if (m_sAnimeData.m_iHndl == -1)
	{
		//�A�j���[�V�������Đ�����Ă��Ȃ�
		return;
	}

	//�A�j���[�V�������x�X�V
	m_sAnimeData.m_AnimeTime += m_sAnimeData.m_AddTime;

	if (m_sAnimeData.m_AnimeTime >= m_sAnimeData.m_MaxAnimeTime)
	{
		//�ŏI�t���[���܂ŗ�����A��Ԃɍ��킹�ē����ς���
		switch (m_sAnimeData.m_iState)
		{
		case ANIMSTATE_NORMAL:
			DetachAnime();
			m_sAnimeData.m_MaxAnimeTime = 0.0f;
			m_sAnimeData.m_AnimeTime = 0.0f;
			m_sAnimeData.m_AddTime = 0.0f;
			return;
			//���[�v�͍ŏ��ɖ߂邾��

		case ANIMESTATE_LOOP:
			m_sAnimeData.m_AnimeTime = 0.0f;
			break;
			//�G���h���[�v�͍Ō�Ŏ~�߂�
			
		case ANIMESTATE_END:
			m_sAnimeData.m_AnimeTime = m_sAnimeData.m_MaxAnimeTime;
			break;

		default:
			break;
		}
	}

	//�Đ����Ԑݒ�
	MV1SetAttachAnimTime(m_iHndl, m_sAnimeData.m_iHndl, m_sAnimeData.m_AnimeTime);
}
