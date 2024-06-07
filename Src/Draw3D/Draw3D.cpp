#include "Draw3D.h"
#include "math.h"
#include "../MyLibrary/MyLibrary.h"

//3D�̃{�b�N�X�\���֐�
//��1�����F���W(���S�łȂ��Ă��悢)
//��2�����F�\���������{�b�N�X�̃T�C�Y
//��3�����F���S���W�łȂ����̃Y��(���łɒ��S�̎��͏����Ȃ��Ă悢)
void CDraw3D::DrawBox3D(VECTOR Pos, VECTOR Size, VECTOR Gap = { 0.0f, 0.0f, 0.0f })
{
	//�T�C�Y�̔������Ƃ�
	VECTOR HalfSize = VScale(Size, 0.5f);

	//���S���W�֕ύX����
	Pos = VAdd(Pos, Gap);

	/*��̖�*/
	//���ォ��E��(��O)
	DrawLine3D(VGet(Pos.x - HalfSize.x, Pos.y + HalfSize.y, Pos.z - HalfSize.z), VGet(Pos.x + HalfSize.x, Pos.y + HalfSize.y, Pos.z - HalfSize.z), GetColor(255, 0, 0));
}