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
	 bool CheckDir[6];
	 for (int Index = 0; Index < 6; Index++)
	 {
		 CheckDir[Index] = cPlayer.GetDir(Index);
	 }
	
	
	 VECTOR vPlayerPos = cPlayer.GetNextPos();			//プレイヤーの座標
	 VECTOR vPlayerSize = VGet(40.0f, 50.0f, 40.0f);	//プレイヤーのサイズ
	 VECTOR P_HarfSize = VScale(vPlayerSize, 0.5f);		//プレイヤーのサイズ(半分)

	 VECTOR	vObjectPos = VGet(0.0f, 30.0f, 100.0f);		//オブジェクトの座標
	 VECTOR vObjectSize = VGet(20.0f, 20.0f, 20.0f);	//オブジェクトのサイズ
	 VECTOR HarfSize = VScale(vObjectSize, 0.5f);		//オブジェクトのサイズ(半分)


	 if (CCollision::CheckHitBoxToBox(vPlayerPos, vPlayerSize, vObjectPos, vObjectSize))
	 {

		 //めり込み量を格納する変数を生成
		 VECTOR Puls = VGet(0.0f, 0.0f, 0.0f);
		 
		 /*X軸の当たり判定*/
		 //右から当たった時
		 if (CheckDir[1] == true)
		 {
			Puls.x = (vObjectPos.x + HarfSize.x) - (vPlayerPos.x - P_HarfSize.x);
			vPlayerPos.x += Puls.x;
		 }
		 //左から当たった時
		 if(CheckDir[0] == true)
		 { 
		    Puls.x = (vObjectPos.x - HarfSize.x) - (vPlayerPos.x + P_HarfSize.x);
			vPlayerPos.x += Puls.x;
		 }


		 /*Y軸の当たり判定*/
		 //上から
		 if (CheckDir[3] == true)
		 {
			Puls.y = (vObjectPos.y + HarfSize.y) - (vPlayerPos.y - P_HarfSize.y);
			vPlayerPos.y += Puls.y;
		 }
		 //下から当たった時
		 if (CheckDir[2] == true)
		 {
		    Puls.y = (vObjectPos.y - HarfSize.y) - (vPlayerPos.y + P_HarfSize.y);
			vPlayerPos.y += Puls.y;
		 }


		 /*Z軸の当たり判定*/
		 //手前から
		 if (CheckDir[5] == true)
		 {
			 Puls.z = (vObjectPos.z + HarfSize.z) - (vPlayerPos.z - P_HarfSize.z);
			 vPlayerPos.z += Puls.z;
		 }
		 //奥から
		 if (CheckDir[4] == true)
		 {
			 Puls.z = (vObjectPos.z - HarfSize.z) - (vPlayerPos.z + P_HarfSize.z);
			 vPlayerPos.z += Puls.z;
		 }
		 

		 //最後にめり込んだ分を座標に更新する
		 cPlayer.SetPos(vPlayerPos);


	 }
 }

