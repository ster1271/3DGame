#pragma once

#include "../Shot/ShotManager.h"
#include "../Enemy/EnemyManager.h"


class CCollisionManager
{
public:
	//敵との当たり判定
	static void CheckHitShotToEnemy(CEnemyManager& cEnemyManager, CShotManager& cShotManager);
};
