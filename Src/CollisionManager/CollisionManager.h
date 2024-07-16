#pragma once

#include "../Shot/ShotManager.h"
#include "../Enemy/EnemyManager.h"
#include "../target/target.h"
#include "../Player/Player.h"
#include "../Object/Box/Box.h"


class CCollisionManager
{
public:
	//�G�Ƃ̓����蔻��
	static void CheckHitShotToEnemy(CEnemyManager& cEnemyManager, CShotManager& cShotManager);

	//�I�Ƃ̓����蔻��
	static void CheckHitShotToTarget(CTarget& cTarget, CShotManager& cShotManager);

	//���̂Ƃ̓����蔻��
	static void HitToObject(CPlayer& cPlayer, CBox& cBox);
};
