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
 void CCollisionManager::HitToObject(CPlayer& cPlayer, VECTOR ObjectPos, VECTOR ObjectSize)
 {
	 bool CheckDir[6] = { false, false, false, false, false, false };
	 for (int Index = 0; Index < 6; Index++)
	 {
		 CheckDir[Index] = cPlayer.GetDir(Index);
	 }
		

	 VECTOR NextPos = cPlayer.GetNextPos();			//プレイヤーの座標
	 VECTOR PlayerPos = cPlayer.GetPosition();		//プレイヤーの座標

	 VECTOR vPlayerSize = VGet(40.0f, 50.0f, 40.0f);	//プレイヤーのサイズ
	 VECTOR P_HarfSize = VScale(vPlayerSize, 0.5f);		//プレイヤーのサイズ(半分)

	 VECTOR	vObjectPos = ObjectPos;						//オブジェクトの座標
	 VECTOR vObjectSize = ObjectSize;					//オブジェクトのサイズ
	 VECTOR HarfSize = VScale(vObjectSize, 0.5f);		//オブジェクトのサイズ(半分)


	 NextPos.y = PlayerPos.y;
	 NextPos.z = PlayerPos.z;
	 /*X軸の当たり判定*/
	 if (CCollision::CheckHitBoxToBox(NextPos, vPlayerSize, vObjectPos, vObjectSize))
	 {

		 //めり込み量を格納する変数を生成
		 float Overlap = 0.0f;
		 
		 //右から当たった時
		 if (CheckDir[1] == true)
		 {
			Overlap = (vObjectPos.x + HarfSize.x) - (NextPos.x - P_HarfSize.x);
			NextPos.x += Overlap;
		 }
		 //左から当たった時
		 if(CheckDir[0] == true)
		 { 
			Overlap = (vObjectPos.x - HarfSize.x) - (NextPos.x + P_HarfSize.x);
			NextPos.x += Overlap;
		 }

		 //最後にめり込んだ分を座標に更新する
		 cPlayer.SetPos(NextPos);

	 }

	 NextPos.x = PlayerPos.x;
	 NextPos.z = PlayerPos.z;
	 /*Y軸の当たり判定*/
	 if (CCollision::CheckHitBoxToBox(NextPos, vPlayerSize, vObjectPos, vObjectSize))
	 {
		 //めり込み量を格納する変数を生成
		 float Overlap = 0.0f;

		 //上から
		 if (CheckDir[3] == true)
		 {
			 Overlap = (vObjectPos.y + HarfSize.y) - (NextPos.y - P_HarfSize.y);
			 NextPos.y += Overlap;
		 }
		 //下から当たった時
		 if (CheckDir[2] == true)
		 {
			 Overlap = (vObjectPos.y - HarfSize.y) - (NextPos.y + P_HarfSize.y);
			 NextPos.y += Overlap;
		 }

		 //最後にめり込んだ分を座標に更新する
		 cPlayer.SetPos(NextPos);
	 }

	 NextPos.x = PlayerPos.x;
	 NextPos.y = PlayerPos.y;
	 /*Z軸の当たり判定*/
	 if (CCollision::CheckHitBoxToBox(NextPos, vPlayerSize, vObjectPos, vObjectSize))
	 {
		 //めり込み量を格納する変数を生成
		 float Overlap = 0.0f;


		 //手前から
		 if (CheckDir[5] == true)
		 {
			 Overlap = (vObjectPos.z + HarfSize.z) - (NextPos.z - P_HarfSize.z);
			 NextPos.z += Overlap;
		 }
		 //奥から
		 if (CheckDir[4] == true)
		 {
			 Overlap = (vObjectPos.z - HarfSize.z) - (NextPos.z + P_HarfSize.z);
			 NextPos.z += Overlap;
		 }

		 //最後にめり込んだ分を座標に更新する
		 cPlayer.SetPos(NextPos);

	 }
 }

