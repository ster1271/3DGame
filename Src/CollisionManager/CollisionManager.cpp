#include "CollisionManager.h"
#include "../CollisionManager/Collision/Collision.h"

//敵との当たり判定
 void CCollisionManager::CheckHitShotToEnemy(CEnemyManager& cEnemyManager, CShotManager& cShotManager)
{
	 for (int shotIndex = 0; shotIndex < PL_SHOT_NUM; shotIndex++)
	 {
		 //弾情報を取得し、発射されていなければ次へ
		 //shotManagerからCShotを取得している
		 //プレエイヤーの弾情報をとってくる
		 CShot& cPShot = cShotManager.GetPlayerShot(shotIndex);
		 if (!cPShot.IsActive()) continue;

		 for (int enemyIndex = 0; enemyIndex < ENEMY_NUM; enemyIndex++)
		 {
			 //エネミーの情報をとってくる
			 CEnemyBase& cEnemy = cEnemyManager.GetEnemy(enemyIndex);
			 if (!cEnemy.IsActive()) continue;

			 //新しい変数を追加
			 VECTOR vShotPos, vEnemyPos;
			 float fShotRadius, fEnemyRadius;

			 //それぞれの座標を取得し変数に入れる
			 cPShot.GetPosition(vShotPos);
			 cEnemy.GetPosition(vEnemyPos);
			 //それぞれの半径を取得し変数に入れる
			 fShotRadius = cPShot.GetRadius();
			 fEnemyRadius = cEnemy.GetRadius();

			 //敵の方は当たり判定の中心を半径浮かせる
			 vEnemyPos.y += fEnemyRadius;

			 //球と球の当たり判定
			 if (CCollision::CheckHitSphereToSphere(vShotPos, fShotRadius, vEnemyPos, fEnemyRadius))
			 {
				 //ここまでくれば当たった
				 cEnemy.HitCalc();
				 cPShot.HitCalc();
			 }
		 }
	 }
}


 //物体との当たり判定
 void CCollisionManager::HitToObject(CPlayer& cPlayer)
 {
	 if (CCollision::CheckHitBoxToBox(cPlayer.GetPosition(), VGet(40.0f, 50.0f, 40.0f), VGet(0.0f, 30.0f, 100.0f), VGet(20.0f, 20.0f, 20.0f)))
	 {

	 }
 }

 /*
 //Xの当たり判定
 void PLAYER::PulsX(int PosX, float Width)
 {
	 //左からの当たり判定
	 if (dir == IsLeft)
	 {
		 float puls = 0.0f;
		 puls = (Pos.x + 32.0f) - PosX;
		 Pos.x -= puls;
	 }
	 //右からの当たり判定
	 else if (dir == IsRight)
	 {
		 float puls = 0.0f;
		 puls = (PosX + Width) - (Pos.x - 32.0f);
		 Pos.x += puls;
	 }
 }
 //Yの当たり判定
 void PLAYER::PulsY(int PosY, float Height)
 {
	 //上方向からの当たり判定
	 if (YSpeed > 0.0f)
	 {
		 float puls = 0.0f;
		 puls = (Pos.y + 32.0f) - PosY;
		 Pos.y -= puls;
		 YSpeed = 0.0f;
		 JumpCount = 0;
		 IsJump = false;
	 }
	 //下方向からの当たり判定
	 else if (YSpeed < 0.0f)
	 {
		 float puls = 0.0f;
		 puls = (PosY + Height) - (Pos.y - 32.0f);
		 Pos.y += puls;
		 YSpeed = -0.5f;
	 }
 }
 */