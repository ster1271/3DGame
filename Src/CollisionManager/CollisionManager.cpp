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

 