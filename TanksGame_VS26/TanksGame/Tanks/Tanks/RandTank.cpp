#include "RandTank.h"

#include "../TanksManager.h"

CRandTank::CRandTank(int _iX, int _iY, int _iColor)
  : CTank("RandTank", _iX, _iY, _iColor)
{
}

void CRandTank::Update()
{
	eDesiredAction = EAction::Move;

	// Change direction from time to time
	if (rand() % 15 == 0)
	{
		eDesiredDirection = static_cast<EDirection>(rand() % static_cast<int>(EDirection::Count));
	}

	if (GetBullet() == nullptr)
	{
		eDesiredAction = EAction::Shoot;
	}
}
