#include "DxLib.h"
#include "CollisionManager.h"
#include "../CollisionManager/Collision/Collision.h"

//�G�Ƃ̓����蔻��
 void CCollisionManager::CheckHitShotToEnemy(CEnemyManager& cEnemyManager, CShotManager& cShotManager)
{
	 for (int shotIndex = 0; shotIndex < PL_SHOT_NUM; shotIndex++)
	 {
		 //�e�����擾���A���˂���Ă��Ȃ���Ύ���
		 //shotManager����CShot���擾���Ă���
		 //�v���G�C���[�̒e�����Ƃ��Ă���
		 CShot& cPShot = cShotManager.GetPlayerShot(shotIndex);
		 if (!cPShot.IsActive()) continue;

		 for (int enemyIndex = 0; enemyIndex < ENEMY_NUM; enemyIndex++)
		 {
			 //�G�l�~�[�̏����Ƃ��Ă���
			 CEnemyBase& cEnemy = cEnemyManager.GetEnemy(enemyIndex);
			 if (!cEnemy.IsActive()) continue;

			 //�V�����ϐ���ǉ�
			 VECTOR vShotPos, vEnemyPos;
			 float fShotRadius, fEnemyRadius;

			 //���ꂼ��̍��W���擾���ϐ��ɓ����
			 cPShot.GetPosition(vShotPos);
			 cEnemy.GetPosition(vEnemyPos);
			 //���ꂼ��̔��a���擾���ϐ��ɓ����
			 fShotRadius = cPShot.GetRadius();
			 fEnemyRadius = cEnemy.GetRadius();

			 //�G�̕��͓����蔻��̒��S�𔼌a��������
			 vEnemyPos.y += fEnemyRadius;

			 //���Ƌ��̓����蔻��
			 if (CCollision::CheckHitSphereToSphere(vShotPos, fShotRadius, vEnemyPos, fEnemyRadius))
			 {
				 //�����܂ł���Γ�������
				 cEnemy.HitCalc();
				 cPShot.HitCalc();
			 }
		 }
	 }
}


 //���̂Ƃ̓����蔻��
 void CCollisionManager::HitToObject(CPlayer& cPlayer, VECTOR ObjectPos, VECTOR ObjectSize)
 {
	 bool CheckDir[6] = { false, false, false, false, false, false };
	 for (int Index = 0; Index < 6; Index++)
	 {
		 CheckDir[Index] = cPlayer.GetDir(Index);
	 }
		

	 VECTOR NextPos = cPlayer.GetNextPos();			//�v���C���[�̍��W
	 VECTOR PlayerPos = cPlayer.GetPosition();		//�v���C���[�̍��W

	 VECTOR vPlayerSize = VGet(40.0f, 50.0f, 40.0f);	//�v���C���[�̃T�C�Y
	 VECTOR P_HarfSize = VScale(vPlayerSize, 0.5f);		//�v���C���[�̃T�C�Y(����)

	 VECTOR	vObjectPos = ObjectPos;						//�I�u�W�F�N�g�̍��W
	 VECTOR vObjectSize = ObjectSize;					//�I�u�W�F�N�g�̃T�C�Y
	 VECTOR HarfSize = VScale(vObjectSize, 0.5f);		//�I�u�W�F�N�g�̃T�C�Y(����)


	 NextPos.y = PlayerPos.y;
	 NextPos.z = PlayerPos.z;
	 /*X���̓����蔻��*/
	 if (CCollision::CheckHitBoxToBox(NextPos, vPlayerSize, vObjectPos, vObjectSize))
	 {

		 //�߂荞�ݗʂ��i�[����ϐ��𐶐�
		 float Overlap = 0.0f;
		 
		 //�E���瓖��������
		 if (CheckDir[1] == true)
		 {
			Overlap = (vObjectPos.x + HarfSize.x) - (NextPos.x - P_HarfSize.x);
			NextPos.x += Overlap;
		 }
		 //�����瓖��������
		 if(CheckDir[0] == true)
		 { 
			Overlap = (vObjectPos.x - HarfSize.x) - (NextPos.x + P_HarfSize.x);
			NextPos.x += Overlap;
		 }

		 //�Ō�ɂ߂荞�񂾕������W�ɍX�V����
		 cPlayer.SetPos(NextPos);

	 }

	 NextPos.x = PlayerPos.x;
	 NextPos.z = PlayerPos.z;
	 /*Y���̓����蔻��*/
	 if (CCollision::CheckHitBoxToBox(NextPos, vPlayerSize, vObjectPos, vObjectSize))
	 {
		 //�߂荞�ݗʂ��i�[����ϐ��𐶐�
		 float Overlap = 0.0f;

		 //�ォ��
		 if (CheckDir[3] == true)
		 {
			 Overlap = (vObjectPos.y + HarfSize.y) - (NextPos.y - P_HarfSize.y);
			 NextPos.y += Overlap;
		 }
		 //�����瓖��������
		 if (CheckDir[2] == true)
		 {
			 Overlap = (vObjectPos.y - HarfSize.y) - (NextPos.y + P_HarfSize.y);
			 NextPos.y += Overlap;
		 }

		 //�Ō�ɂ߂荞�񂾕������W�ɍX�V����
		 cPlayer.SetPos(NextPos);
	 }

	 NextPos.x = PlayerPos.x;
	 NextPos.y = PlayerPos.y;
	 /*Z���̓����蔻��*/
	 if (CCollision::CheckHitBoxToBox(NextPos, vPlayerSize, vObjectPos, vObjectSize))
	 {
		 //�߂荞�ݗʂ��i�[����ϐ��𐶐�
		 float Overlap = 0.0f;


		 //��O����
		 if (CheckDir[5] == true)
		 {
			 Overlap = (vObjectPos.z + HarfSize.z) - (NextPos.z - P_HarfSize.z);
			 NextPos.z += Overlap;
		 }
		 //������
		 if (CheckDir[4] == true)
		 {
			 Overlap = (vObjectPos.z - HarfSize.z) - (NextPos.z + P_HarfSize.z);
			 NextPos.z += Overlap;
		 }

		 //�Ō�ɂ߂荞�񂾕������W�ɍX�V����
		 cPlayer.SetPos(NextPos);

	 }
 }

