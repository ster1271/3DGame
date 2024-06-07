#include "CollisionManager.h"
#include "../CollisionManager/Collision/Collision.h"

//“G‚Æ‚Ì“–‚½‚è”»’è
 void CCollisionManager::CheckHitShotToEnemy(CEnemyManager& cEnemyManager, CShotManager& cShotManager)
{
	 for (int shotIndex = 0; shotIndex < PL_SHOT_NUM; shotIndex++)
	 {
		 //’eî•ñ‚ðŽæ“¾‚µA”­ŽË‚³‚ê‚Ä‚¢‚È‚¯‚ê‚ÎŽŸ‚Ö
		 //shotManager‚©‚çCShot‚ðŽæ“¾‚µ‚Ä‚¢‚é
		 //ƒvƒŒƒGƒCƒ„[‚Ì’eî•ñ‚ð‚Æ‚Á‚Ä‚­‚é
		 CShot& cPShot = cShotManager.GetPlayerShot(shotIndex);
		 if (!cPShot.IsActive()) continue;

		 for (int enemyIndex = 0; enemyIndex < ENEMY_NUM; enemyIndex++)
		 {
			 //ƒGƒlƒ~[‚Ìî•ñ‚ð‚Æ‚Á‚Ä‚­‚é
			 CEnemyBase& cEnemy = cEnemyManager.GetEnemy(enemyIndex);
			 if (!cEnemy.IsActive()) continue;

			 //V‚µ‚¢•Ï”‚ð’Ç‰Á
			 VECTOR vShotPos, vEnemyPos;
			 float fShotRadius, fEnemyRadius;

			 //‚»‚ê‚¼‚ê‚ÌÀ•W‚ðŽæ“¾‚µ•Ï”‚É“ü‚ê‚é
			 cPShot.GetPosition(vShotPos);
			 cEnemy.GetPosition(vEnemyPos);
			 //‚»‚ê‚¼‚ê‚Ì”¼Œa‚ðŽæ“¾‚µ•Ï”‚É“ü‚ê‚é
			 fShotRadius = cPShot.GetRadius();
			 fEnemyRadius = cEnemy.GetRadius();

			 //“G‚Ì•û‚Í“–‚½‚è”»’è‚Ì’†S‚ð”¼Œa•‚‚©‚¹‚é
			 vEnemyPos.y += fEnemyRadius;

			 //‹…‚Æ‹…‚Ì“–‚½‚è”»’è
			 if (CCollision::CheckHitSphereToSphere(vShotPos, fShotRadius, vEnemyPos, fEnemyRadius))
			 {
				 //‚±‚±‚Ü‚Å‚­‚ê‚Î“–‚½‚Á‚½
				 cEnemy.HitCalc();
				 cPShot.HitCalc();
			 }
		 }
	 }
}

 