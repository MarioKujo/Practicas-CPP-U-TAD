#include "Bullet.h"

#include "Tanks/Tank.h"
#include "TanksManager.h"
#include "Map.h"

bool CBullet::CollisionCheck(const CTank*& pCollidingTank_)
{
	pCollidingTank_ = nullptr;
	// Check bullet againt tanks
	for(const CTank* pTank : CTanksManager::GetInstance().GetTanks())
	{
		if (pTank != pOwner && CTanksManager::IsInsideTank(iX, iY, pTank->GetPosX(), pTank->GetPosY()))
		{
			pCollidingTank_ = pTank;
			return true;
		}
	}
	// Check bullet against map
	if (CTanksManager::GetInstance().GetMap().CheckBulletCollision(this))
	{
		return true;
	}
	return false;
}
