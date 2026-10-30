#pragma once

#include "Direction.h"

class CTank;

class CBullet
{
public:
	short iX;
	short iY;
	EDirection eDirection;
	// Tank that shot the bullet (it can't hit itself)
	const CTank* pOwner = nullptr;

	bool CollisionCheck(const CTank*& pCollidingTank_);
};

