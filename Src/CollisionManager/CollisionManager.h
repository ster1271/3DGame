#pragma once

#include "../Shot/ShotManager.h"
#include "../Enemy/EnemyManager.h"


class CCollisionManager
{
public:
	//�G�Ƃ̓����蔻��
	static void CheckHitShotToEnemy(CEnemyManager& cEnemyManager, CShotManager& cShotManager);
};
