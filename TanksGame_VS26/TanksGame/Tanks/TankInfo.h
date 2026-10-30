#pragma once

#include "Direction.h"

class CTank;
class CBullet;

class CTankInfo
{
public:
	CTank* pTank = nullptr;
	int iX = 0;
	int iY = 0;
	int iHealth = 0;
	EDirection eDirection = EDirection::Down;
	CBullet* pBullet = nullptr;
	bool bExploding = false;
	// Render
	int iSkin = 0;
	int iMovingTicks = 0;
	// Ticks left of the hit flash
	int iHitFlashTicks = 0;
};
