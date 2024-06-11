#pragma once

#include "../Shot/ShotManager.h"
#include "../Enemy/EnemyManager.h"
#include "../Player/Player.h"


class CCollisionManager
{
public:
	//敵との当たり判定
	static void CheckHitShotToEnemy(CEnemyManager& cEnemyManager, CShotManager& cShotManager);

	//物体との当たり判定
	static void HitToObject(CPlayer& cPlayer);
};
