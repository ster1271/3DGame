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
 void CCollisionManager::HitToObject(CPlayer& cPlayer)
 {
	 bool CheckDir[6];
	 for (int Index = 0; Index < 6; Index++)
	 {
		 CheckDir[Index] = cPlayer.GetDir(Index);
	 }
	
	
	 VECTOR vPlayerPos = cPlayer.GetNextPos();			//�v���C���[�̍��W
	 VECTOR vPlayerSize = VGet(40.0f, 50.0f, 40.0f);	//�v���C���[�̃T�C�Y
	 VECTOR P_HarfSize = VScale(vPlayerSize, 0.5f);		//�v���C���[�̃T�C�Y(����)

	 VECTOR	vObjectPos = VGet(0.0f, 30.0f, 100.0f);		//�I�u�W�F�N�g�̍��W
	 VECTOR vObjectSize = VGet(20.0f, 20.0f, 20.0f);	//�I�u�W�F�N�g�̃T�C�Y
	 VECTOR HarfSize = VScale(vObjectSize, 0.5f);		//�I�u�W�F�N�g�̃T�C�Y(����)


	 if (CCollision::CheckHitBoxToBox(vPlayerPos, vPlayerSize, vObjectPos, vObjectSize))
	 {

		 //�߂荞�ݗʂ��i�[����ϐ��𐶐�
		 VECTOR Puls = VGet(0.0f, 0.0f, 0.0f);
		 
		 /*X���̓����蔻��*/
		 //�E���瓖��������
		 if (CheckDir[1] == true)
		 {
			Puls.x = (vObjectPos.x + HarfSize.x) - (vPlayerPos.x - P_HarfSize.x);
			vPlayerPos.x += Puls.x;
		 }
		 //�����瓖��������
		 if(CheckDir[0] == true)
		 { 
		    Puls.x = (vObjectPos.x - HarfSize.x) - (vPlayerPos.x + P_HarfSize.x);
			vPlayerPos.x += Puls.x;
		 }


		 /*Y���̓����蔻��*/
		 //�ォ��
		 if (CheckDir[3] == true)
		 {
			Puls.y = (vObjectPos.y + HarfSize.y) - (vPlayerPos.y - P_HarfSize.y);
			vPlayerPos.y += Puls.y;
		 }
		 //�����瓖��������
		 if (CheckDir[2] == true)
		 {
		    Puls.y = (vObjectPos.y - HarfSize.y) - (vPlayerPos.y + P_HarfSize.y);
			vPlayerPos.y += Puls.y;
		 }


		 /*Z���̓����蔻��*/
		 //��O����
		 if (CheckDir[5] == true)
		 {
			 Puls.z = (vObjectPos.z + HarfSize.z) - (vPlayerPos.z - P_HarfSize.z);
			 vPlayerPos.z += Puls.z;
		 }
		 //������
		 if (CheckDir[4] == true)
		 {
			 Puls.z = (vObjectPos.z - HarfSize.z) - (vPlayerPos.z + P_HarfSize.z);
			 vPlayerPos.z += Puls.z;
		 }
		 

		 //�Ō�ɂ߂荞�񂾕������W�ɍX�V����
		 cPlayer.SetPos(vPlayerPos);


	 }
 }

