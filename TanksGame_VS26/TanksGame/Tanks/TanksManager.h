#pragma once

#include <vector>
#include <list>
#include "ISingleton.h"
#include "Tanks/Tank.h"
#include "Map.h"

class CBullet;

class CTanksManager : public ISingleton<CTanksManager>
{
public:
	static const int s_iInitialTankHealth = 6;
	// Pixels the tank and the bullet move each tick
	static const int s_iTankSpeed = 3;
	static const int s_iBulletSpeed = 6;
	// Tanks are squares of s_iTankSize pixels centered in their position
	static const int s_iTankSize = 14;
	static const int s_iTankHalfSize = s_iTankSize / 2;
	// Ticks each animation frame lasts
	static const int s_iTankAnimationFrameTicks = 3;
	static const int s_iExplosionFrameTicks = 4;
	// When a tank is hit it blinks in white during s_iHitFlashTicks (changing every s_iHitFlashBlinkTicks)
	static const int s_iHitFlashTicks = 12;
	static const int s_iHitFlashBlinkTicks = 2;
	// Maximum number of tanks in the game
	static const int s_iMaxTanks = 16;
	// Info panel at the right of the map: columns of s_iHudRows tanks
	static const int s_iHudRows = 8;
	static const int s_iHudColumnWidth = 106;
	// Game speed
	static const int s_iTicksPerSecond = 30;
	// After s_iCannonsStartSeconds two cannons appear outside the map (one at the top, one at the bottom),
	// moving from side to side s_iCannonSpeed pixels each tick and shooting inside every s_iCannonShootTicks
	static const int s_iCannonsStartSeconds = 60;
	static const int s_iCannonSpeed = 2;
	static const int s_iCannonShootTicks = 10;
	// Height of the bands above and below the map where the cannons move
	static const int s_iCannonBandSize = 12;

	CTanksManager();
	~CTanksManager();

	// To get all tanks (alive or not)
	const std::vector<const CTank*>& GetAllTanks() { return m_tAllTanks; }
	// To get all alive tanks
	const std::list<const CTank*>& GetTanks() { return m_tTanks; }
	// To get the map
	const CMap& GetMap() { return m_oMap; }
	// To get all the bullets in game (from tanks and cannons). Cannon bullets have no owner (pOwner == nullptr)
	const std::list<const CBullet*>& GetBullets() { return m_tBullets; }
	// Game time in ticks (s_iTicksPerSecond each second)
	int GetTicks() const { return m_iTicks; }
	// Are the cannons out?
	bool AreCannonsActive() const;

	// Add tank to the manager
	void AddTank(CTank* _pTank);
	// Update the manager (one tick)
	void Update();
	// Draw the game
	void Render() const;
	// Size in pixels of the window (map, cannon bands and info panel)
	int GetWindowWidth() const;
	int GetWindowHeight() const;

	// Is the point (_iX, _iY) inside a tank placed at (_iTankX, _iTankY)?
	static bool IsInsideTank(int _iX, int _iY, int _iTankX, int _iTankY);

private:
	void TryMoveTank(CTankInfo* _pTankInfo);

	bool TryFireBullet(CTankInfo* _pTankInfo);
	void ProcessTankImpact(const CTank* _pTank);
	// Moves the bullet one pixel (if allowed) and checks the collisions. On collision the bullet is deleted and set to nullptr
	void UpdateBullet(CBullet*& _pBullet, bool _bAllowMovement);
	void UpdateCannons(std::vector<const CBullet*>& tBulletsSpawned_);
	void RemoveDeadTanks();

	void RenderHud() const;
	int GetHudWidth() const;

	bool IsGameFinished() const;

private:
	std::vector<const CTank*> m_tAllTanks;
	std::list<const CTank*> m_tTanks;
	CMap m_oMap;

	std::vector<CTankInfo*> m_tTankInfos;

	struct SCannon
	{
		int iX = 0;
		// Center of the cannon (outside the map)
		int iY = 0;
		// Pixels to move each tick (negative: to the left)
		int iStep = 0;
		// Direction it shoots (inside the map)
		EDirection eDirection = EDirection::Down;
	};
	std::vector<SCannon> m_tCannons;
	std::list<CBullet*> m_tCannonBullets;
	std::list<const CBullet*> m_tBullets;
	int m_iTicks = 0;
};
