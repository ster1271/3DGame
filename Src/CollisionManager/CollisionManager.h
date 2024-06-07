#pragma once

#include "../Shot/ShotManager.h"
#include "../Enemy/EnemyManager.h"


class CCollisionManager
{
public:
	//“G‚Æ‚Ì“–‚½‚è”»’è
	static void CheckHitShotToEnemy(CEnemyManager& cEnemyManager, CShotManager& cShotManager);
};
