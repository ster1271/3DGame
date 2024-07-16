#pragma once

#include "../Shot/ShotManager.h"
#include "../Enemy/EnemyManager.h"
#include "../target/target.h"
#include "../Player/Player.h"
#include "../Object/Box/Box.h"


class CCollisionManager
{
public:
	//敵との当たり判定
	static void CheckHitShotToEnemy(CEnemyManager& cEnemyManager, CShotManager& cShotManager);

	//的との当たり判定
	static void CheckHitShotToTarget(CTarget& cTarget, CShotManager& cShotManager);

	//物体との当たり判定
	static void HitToObject(CPlayer& cPlayer, CBox& cBox);
};
