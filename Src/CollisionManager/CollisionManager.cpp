#include "DxLib.h"
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

		 //めり込み量を格納する変数を生成
		 VECTOR Puls = VGet(0.0f, 0.0f, 0.0f);


		 //
		 ///*X軸の当たり判定*/
		 ////右から当たった時
		 //if (cPlayer.GetGapPositionX() > 0.0f)
		 //{
			//Puls.x = //(物体の中心X座標 + Xサイズ(半分)) - (プレイヤーの中心X座標 - Xサイズ(半分))	
		 //}
		 ////左から当たった時
		 //else
		 //{ 
			// Puls.x = //(物体の中心X座標 - Xサイズ(半分)) - (プレイヤーの中心X座標 + Xサイズ(半分))
		 //}


		 ///*Y軸の当たり判定*/
		 ////上から
		 //if (cPlayer.GetGapPositionY() < 0.0f)
		 //{
			// Puls.y = //(物体の中心Y座標 + Yサイズ(半分)) - (プレイヤーの中心Y座標 - Yサイズ(半分))
		 //}
		 ////下から当たった時
		 //else
		 //{
			// Puls.y = //(物体の中心Y座標 - Yサイズ(半分)) - (プレイヤーの中心Y座標 + Yサイズ(半分))
		 //}


		 ///*Z軸の当たり判定*/
		 ////手前から
		 //if (cPlayer.GetGapPositionZ() > 0.0f)
		 //{
			// Puls.z = //(物体の中心Z座標 + Zサイズ(半分)) - (プレイヤーの中心Z座標 - Zサイズ(半分))
		 //}
		 ////奥から
		 //else
		 //{
			// Puls.z = //(物体の中心Z座標 - Zサイズ(半分)) - (プレイヤーの中心Z座標 + Zサイズ(半分))
		 //}
		 //
		 
		 //最後にめり込んだ分を座標に加算する
		 cPlayer.SetPos(Puls);
	 }
 }

