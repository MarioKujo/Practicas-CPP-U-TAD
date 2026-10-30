#pragma once

#include <vector>
#include "Tank.h"

class MakuTank : public CTank
{
public:
	MakuTank(int _iX, int _iY, int _iColor);

	void Update() override;

private:
	struct SEnemy
	{
		int iX;
		int iY;
		bool bCanShoot; // its bullet is not in the air
	};

	struct SSimBullet
	{
		int iX;
		int iY;
		int iDX;
		int iDY;
		bool bAlive;
	};

	// Wait iLead ticks, then move iMoveTicks in eDir, then stand still
	struct SPlan
	{
		int iLead;
		EDirection eDir;
		int iMoveTicks;
	};

	struct SResult
	{
		int iHits;
		int iX;
		int iY;
	};

	SResult Simulate(const SPlan& _rPlan);
	int PositionCost(int _iX, int _iY, bool _bCanShoot) const;

	std::vector<SEnemy> m_tEnemies;
	std::vector<SSimBullet> m_tThreats;
	std::vector<SSimBullet> m_tSimThreats;

	EDirection m_ePrevDir = EDirection::Down;
	bool m_bPrevMoved = false;
};