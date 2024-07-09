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
 void CCollisionManager::HitToObject(CPlayer& cPlayer, CBox& cBox)
 {
	 bool CheckDir[6] = { false, false, false, false, false, false };
	 cPlayer.CheckDir(CheckDir);
		

	 VECTOR NextPos = cPlayer.GetNextPos();				//プレイヤーの座標
	 VECTOR PlayerPos = cPlayer.GetPosition();			//プレイヤーの座標

	 VECTOR vPlayerSize = cPlayer.GetPlayerSize();		//プレイヤーのサイズ
	 VECTOR P_HarfSize = VScale(vPlayerSize, 0.5f);		//プレイヤーのサイズ(半分)

	 VECTOR	vObjectPos[MAX_NUM];
	 for (int BoxNum = 0; BoxNum < MAX_NUM; BoxNum++)
	 {
		 vObjectPos[BoxNum] = cBox.GetPos(BoxNum);						//オブジェクトの座標
	 }
	 VECTOR vObjectSize = cBox.GetSize();					//オブジェクトのサイズ
	 VECTOR HarfSize = VScale(vObjectSize, 0.5f);		//オブジェクトのサイズ(半分)

	 for (int BoxNum = 0; BoxNum < MAX_NUM; BoxNum++)
	 {
		 if (cBox.GetActive(BoxNum) == false)
		 {
			 continue;
		 }

		 /*X軸の当たり判定*/
		 PlayerPos.x = NextPos.x;
		 if (CCollision::CheckHitBoxToBox(PlayerPos, vPlayerSize, vObjectPos[BoxNum], vObjectSize))
		 {

			 //めり込み量を格納する変数を生成
			 float Overlap = 0.0f;

			 //右から当たった時
			 if (CheckDir[1] == true)
			 {
				 Overlap = (vObjectPos[BoxNum].x + HarfSize.x) - (NextPos.x - P_HarfSize.x);
				 NextPos.x += Overlap;
			 }
			 //左から当たった時
			 if (CheckDir[0] == true)
			 {
				 Overlap = (vObjectPos[BoxNum].x - HarfSize.x) - (NextPos.x + P_HarfSize.x);
				 NextPos.x += Overlap;
			 }
			 //最後にめり込んだ分を座標に更新する
			 cPlayer.SetPosX(NextPos);

		 }
	 }

	 for (int BoxNum = 0; BoxNum < MAX_NUM; BoxNum++)
	 {
		 if (cBox.GetActive(BoxNum) == false)
		 {
			 continue;
		 }
		 PlayerPos.x = cPlayer.GetNextPos().x;
		 PlayerPos.z = NextPos.z;
		 /*Z軸の当たり判定*/
		 if (CCollision::CheckHitBoxToBox(PlayerPos, vPlayerSize, vObjectPos[BoxNum], vObjectSize))
		 {
			 //めり込み量を格納する変数を生成
			 float Overlap = 0.0f;


			 //手前から
			 if (CheckDir[5] == true)
			 {
				 Overlap = (vObjectPos[BoxNum].z + HarfSize.z) - (NextPos.z - P_HarfSize.z);
				 NextPos.z += Overlap;
			 }
			 //奥から
			 if (CheckDir[4] == true)
			 {
				 Overlap = (vObjectPos[BoxNum].z - HarfSize.z) - (NextPos.z + P_HarfSize.z);
				 NextPos.z += Overlap;
			 }
			 //最後にめり込んだ分を座標に更新する
			 cPlayer.SetPosZ(NextPos);

		 }

		 NextPos.x = NextPos.x;
		 NextPos.z = PlayerPos.z;
	 }

	 for (int BoxNum = 0; BoxNum < MAX_NUM; BoxNum++)
	 {
		 if (cBox.GetActive(BoxNum) == false)
		 {
			 continue;
		 }
		 /*Y軸の当たり判定*/
		 if (CCollision::CheckHitBoxToBox(NextPos, vPlayerSize, vObjectPos[BoxNum], vObjectSize))
		 {
			 //めり込み量を格納する変数を生成
			 float Overlap = 0.0f;

			 //上から
			 if (CheckDir[3] == true)
			 {
				 Overlap = (vObjectPos[BoxNum].y + HarfSize.y) - (NextPos.y - P_HarfSize.y);
				 NextPos.y += Overlap;
			 }
			 //下から当たった時
			 if (CheckDir[2] == true)
			 {
				 Overlap = (vObjectPos[BoxNum].y - HarfSize.y) - (NextPos.y + P_HarfSize.y);
				 NextPos.y += Overlap;
			 }
			 //最後にめり込んだ分を座標に更新する
			 cPlayer.SetPosY(NextPos);
		 }
	 }
 }

