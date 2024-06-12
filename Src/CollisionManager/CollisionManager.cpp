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
	 if (CCollision::CheckHitBoxToBox(cPlayer.GetPosition(), VGet(40.0f, 50.0f, 40.0f), VGet(0.0f, 30.0f, 100.0f), VGet(20.0f, 20.0f, 20.0f)))
	 {

	 }
 }

 /*
 //X�̓����蔻��
 void PLAYER::PulsX(int PosX, float Width)
 {
	 //������̓����蔻��
	 if (dir == IsLeft)
	 {
		 float puls = 0.0f;
		 puls = (Pos.x + 32.0f) - PosX;
		 Pos.x -= puls;
	 }
	 //�E����̓����蔻��
	 else if (dir == IsRight)
	 {
		 float puls = 0.0f;
		 puls = (PosX + Width) - (Pos.x - 32.0f);
		 Pos.x += puls;
	 }
 }
 //Y�̓����蔻��
 void PLAYER::PulsY(int PosY, float Height)
 {
	 //���������̓����蔻��
	 if (YSpeed > 0.0f)
	 {
		 float puls = 0.0f;
		 puls = (Pos.y + 32.0f) - PosY;
		 Pos.y -= puls;
		 YSpeed = 0.0f;
		 JumpCount = 0;
		 IsJump = false;
	 }
	 //����������̓����蔻��
	 else if (YSpeed < 0.0f)
	 {
		 float puls = 0.0f;
		 puls = (PosY + Height) - (Pos.y - 32.0f);
		 Pos.y += puls;
		 YSpeed = -0.5f;
	 }
 }
 */