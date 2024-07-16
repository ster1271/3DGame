#pragma once

#include "../Shot/ShotManager.h"
#include "../Enemy/EnemyManager.h"
#include "../target/target.h"
#include "../Player/Player.h"
#include "../Object/Box/Box.h"


class CCollisionManager
{
public:
	//“G‚Æ‚Ì“–‚½‚è”»’è
	static void CheckHitShotToEnemy(CEnemyManager& cEnemyManager, CShotManager& cShotManager);

	//“I‚Æ‚Ì“–‚½‚è”»’è
	static void CheckHitShotToTarget(CTarget& cTarget, CShotManager& cShotManager);

	//•¨‘Ì‚Æ‚Ì“–‚½‚è”»’è
	static void HitToObject(CPlayer& cPlayer, CBox& cBox);
};
