#pragma once

#include "../Shot/ShotManager.h"
#include "../Enemy/EnemyManager.h"
#include "../Player/Player.h"


class CCollisionManager
{
public:
	//“G‚Æ‚Ì“–‚½‚è”»’è
	static void CheckHitShotToEnemy(CEnemyManager& cEnemyManager, CShotManager& cShotManager);

	//•¨‘Ì‚Æ‚Ì“–‚½‚è”»’è
	static void HitToObject(CPlayer& cPlayer, VECTOR ObjectPos, VECTOR ObjectSize);
};
