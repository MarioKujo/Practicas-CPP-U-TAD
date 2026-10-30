#include "MakuTank.h"

#include <algorithm>
#include <climits>
#include <cstdlib>

#include "../TanksManager.h"
#include "../Bullet.h"
#include "../Map.h"

namespace
{
	const int s_iHorizon = 14;          // ticks simulated ahead
	const int s_iAimTolerance = 4;      // max lateral error (px) to shoot
	const int s_iMaxShotDistance = 170; // don't waste the bullet from too far
	const int s_iDangerTolerance = 9;   // lateral error at which an enemy can hit me
	const int s_iDangerRange = 140;     // only worry about enemies closer than this
	const int s_iExposureCost = 25;
	const int s_iWallComfort = 28;      // keep this far from the walls if possible
	const int s_iHysteresisBonus = 6;
	const int s_iSafeDistance = 42; // below this I can't dodge a bullet from an armed enemy

	void DirToStep(EDirection _eDir, int& iDX_, int& iDY_)
	{
		iDX_ = 0;
		iDY_ = 0;
		switch (_eDir)
		{
			case EDirection::Up:
			{
				iDY_ = -1;
				break;
			}
			case EDirection::Down:
			{
				iDY_ = 1;
				break;
			}
			case EDirection::Left:
			{
				iDX_ = -1;
				break;
			}
			case EDirection::Right:
			{
				iDX_ = 1;
				break;
			}
			default:
			{
				break;
			}
		}
	}
}

MakuTank::MakuTank(int _iX, int _iY, int _iColor)
	: CTank("Maku", _iX, _iY, _iColor)
{
}

// Simulates the next ticks following the plan, with the same order as the engine:
// first the tank moves, then the bullets advance pixel by pixel
MakuTank::SResult MakuTank::Simulate(const SPlan& _rPlan)
{
	const CMap& rMap = CTanksManager::GetInstance().GetMap();

	m_tSimThreats = m_tThreats; // reuses the vector's memory

	int iX = GetPosX();
	int iY = GetPosY();
	int iHits = 0;

	int iStepX, iStepY;
	DirToStep(_rPlan.eDir, iStepX, iStepY);

	for (int iTick = 0; iTick < s_iHorizon; ++iTick)
	{
		// My movement
		if (iTick >= _rPlan.iLead && iTick < _rPlan.iLead + _rPlan.iMoveTicks)
		{
			for (int i = 0; i < CTanksManager::s_iTankSpeed; ++i)
			{
				const int iNewX = iX + iStepX;
				const int iNewY = iY + iStepY;
				if (!rMap.MoveCheck(this, iNewX, iNewY))
				{
					break;
				}
				bool bBlocked = false;
				for (const SEnemy& rEnemy : m_tEnemies)
				{
					if (abs(rEnemy.iX - iNewX) < CTanksManager::s_iTankSize &&
						abs(rEnemy.iY - iNewY) < CTanksManager::s_iTankSize)
					{
						bBlocked = true;
						break;
					}
				}
				if (bBlocked)
				{
					break;
				}
				iX = iNewX;
				iY = iNewY;
			}
		}

		// Bullets
		for (int iStep = 0; iStep < CTanksManager::s_iBulletSpeed; ++iStep)
		{
			for (SSimBullet& rBullet : m_tSimThreats)
			{
				if (!rBullet.bAlive)
				{
					continue;
				}
				rBullet.iX += rBullet.iDX;
				rBullet.iY += rBullet.iDY;
				if (rMap.IsWall(rBullet.iX, rBullet.iY))
				{
					rBullet.bAlive = false;
				}
				else if (CTanksManager::IsInsideTank(rBullet.iX, rBullet.iY, iX, iY))
				{
					rBullet.bAlive = false;
					++iHits;
				}
			}
		}
	}

	return { iHits, iX, iY };
}

// Heuristic cost of ending at (_iX, _iY). Lower is better
int MakuTank::PositionCost(int _iX, int _iY, bool _bCanShoot) const
{
	const CMap& rMap = CTanksManager::GetInstance().GetMap();
	int iCost = 0;

	// Stay away from walls (less room to dodge)
	const int iWallDist = std::min(std::min(_iX, rMap.GetWidth() - 1 - _iX),
		std::min(_iY, rMap.GetHeight() - 1 - _iY));
	if (iWallDist < s_iWallComfort)
	{
		iCost += (s_iWallComfort - iWallDist) * 2;
	}

	int iPull = INT_MAX;
	for (const SEnemy& rEnemy : m_tEnemies)
	{
		const int iDX = abs(rEnemy.iX - _iX);
		const int iDY = abs(rEnemy.iY - _iY);
		const int iLateral = std::min(iDX, iDY);
		const int iAlong = std::max(iDX, iDY);

		// Don't stand in the line of someone who can shoot me
		if (rEnemy.bCanShoot && iLateral <= s_iDangerTolerance && iAlong <= s_iDangerRange)
		{
			iCost += s_iExposureCost;
		}

		// Too close to ANY enemy (armed or not): he may approach or reload while I can't dodge
		if (iAlong < s_iSafeDistance)
		{
			const int iWeight = rEnemy.bCanShoot ? 3 : 2;
			iCost += (s_iSafeDistance - iAlong) * iWeight;
		}

		// Go after enemies, with no bonus for getting closer than the safe distance
		if (_bCanShoot || !rEnemy.bCanShoot)
		{
			iPull = std::min(iPull, iLateral * 3 + std::max(iAlong, s_iSafeDistance) / 4);
		}
	}
	if (iPull != INT_MAX)
	{
		iCost += iPull;
	}
	else
	{
		// Nothing to chase: drift to the center
		const int iCenterX = rMap.GetWidth() / 2;
		const int iCenterY = rMap.GetHeight() / 2;
		iCost += (abs(_iX - iCenterX) + abs(_iY - iCenterY)) / 8;
	}

	return iCost;
}

void MakuTank::Update()
{
	CTanksManager& rManager = CTanksManager::GetInstance();
	const bool bCanShoot = (GetBullet() == nullptr);
	const int iMyX = GetPosX();
	const int iMyY = GetPosY();

	// 1) Gather enemies
	m_tEnemies.clear();
	for (const CTank* pTank : rManager.GetTanks())
	{
		if (pTank == this || pTank->IsDead() || pTank->IsExploding())
		{
			continue;
		}
		m_tEnemies.push_back({ pTank->GetPosX(), pTank->GetPosY(), pTank->GetBullet() == nullptr });
	}

	// 2) Gather bullets that can hurt me (other tanks' and cannons')
	m_tThreats.clear();
	for (const CBullet* pBullet : rManager.GetBullets())
	{
		if (pBullet->pOwner == this)
		{
			continue;
		}
		SSimBullet oBullet;
		oBullet.iX = pBullet->iX;
		oBullet.iY = pBullet->iY;
		DirToStep(pBullet->eDirection, oBullet.iDX, oBullet.iDY);
		oBullet.bAlive = true;
		m_tThreats.push_back(oBullet);
	}

	// 3) Is there an enemy I can shoot right now? (nearest one aligned)
	bool bHasShot = false;
	EDirection eShotDir = EDirection::Down;
	if (bCanShoot)
	{
		int iBestDist = INT_MAX;
		for (const SEnemy& rEnemy : m_tEnemies)
		{
			const int iDX = rEnemy.iX - iMyX;
			const int iDY = rEnemy.iY - iMyY;
			if (abs(iDX) <= s_iAimTolerance && abs(iDY) <= s_iMaxShotDistance && abs(iDY) < iBestDist)
			{
				iBestDist = abs(iDY);
				eShotDir = iDY > 0 ? EDirection::Down : EDirection::Up;
				bHasShot = true;
			}
			else if (abs(iDY) <= s_iAimTolerance && abs(iDX) <= s_iMaxShotDistance && abs(iDX) < iBestDist)
			{
				iBestDist = abs(iDX);
				eShotDir = iDX > 0 ? EDirection::Right : EDirection::Left;
				bHasShot = true;
			}
		}
	}

	// 4) Evaluate plans
	static const EDirection s_aDirs[4] = { EDirection::Up, EDirection::Down, EDirection::Left, EDirection::Right };
	static const int s_aMoveTicks[] = { 1, 2, 3, 4, 6, 8, 12 };

	int iMinMoveHits = INT_MAX;  // best case if I move/stand this tick
	int iMinShootHits = INT_MAX; // best case if I shoot this tick (and act afterwards)
	int iBestScore = INT_MAX;
	SPlan oBestPlan = { 0, m_ePrevDir, 0 };

	auto lambdaEvaluate = [&](const SPlan& _rPlan)
		{
			const SResult oResult = Simulate(_rPlan);
			if (_rPlan.iLead > 0)
			{
				iMinShootHits = std::min(iMinShootHits, oResult.iHits);
				return;
			}
			iMinMoveHits = std::min(iMinMoveHits, oResult.iHits);

			int iScore = oResult.iHits * 1000 + PositionCost(oResult.iX, oResult.iY, bCanShoot);
			if (m_bPrevMoved && _rPlan.iMoveTicks > 0 && _rPlan.eDir == m_ePrevDir)
			{
				iScore -= s_iHysteresisBonus; // keep going, avoids jitter
			}
			if (iScore < iBestScore)
			{
				iBestScore = iScore;
				oBestPlan = _rPlan;
			}
		};

	lambdaEvaluate(SPlan{ 0, m_ePrevDir, 0 });
	if (bHasShot)
	{
		lambdaEvaluate(SPlan{ 1, m_ePrevDir, 0 });
	}
	for (EDirection eDir : s_aDirs)
	{
		for (int iMoveTicks : s_aMoveTicks)
		{
			lambdaEvaluate(SPlan{ 0, eDir, iMoveTicks });
			if (bHasShot)
			{
				lambdaEvaluate(SPlan{ 1, eDir, iMoveTicks });
			}
		}
	}

	// 5) Decide: shoot if it doesn't cost me more hits than the best alternative
	if (bHasShot && iMinShootHits <= iMinMoveHits)
	{
		eDesiredDirection = eShotDir;
		eDesiredAction = EAction::Shoot;
		m_bPrevMoved = false;
		return;
	}

	if (oBestPlan.iMoveTicks > 0)
	{
		eDesiredDirection = oBestPlan.eDir;
		eDesiredAction = EAction::Move;
		m_ePrevDir = oBestPlan.eDir;
		m_bPrevMoved = true;
	}
	else
	{
		eDesiredAction = EAction::None;
		m_bPrevMoved = false;
	}
}