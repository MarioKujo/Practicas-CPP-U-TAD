#include "TanksManager.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include "Direction.h"
#include "Map.h"
#include "Bullet.h"
#include "TankInfo.h"
#include "Renderer.h"

namespace
{
	const unsigned int s_uHudColor = 0xFF1E2126;
	const unsigned int s_uHudEmptyHealthColor = 0xFF40444C;
	const unsigned int s_uTextColor = 0xFFFFFFFF;
	const unsigned int s_uBulletBorderColor = 0xFF000000;
	const unsigned int s_uWarningColor = 0xFFFF5A3C;
	const unsigned int s_uDimTextColor = 0xFF8A90A8;

	std::string FormatTime(int _iTicks)
	{
		const int iSeconds = _iTicks / CTanksManager::s_iTicksPerSecond;
		char sTime[16];
		snprintf(sTime, sizeof(sTime), "%d:%02d", iSeconds / 60, iSeconds % 60);
		return sTime;
	}
}

CTanksManager::CTanksManager()
{
	const int iWall = m_oMap.GetWallThickness();
	const int iCannonHalfHeight = CRenderer::s_iCannonSpriteHeight / 2;

	// Top left, shooting down
	SCannon oTopCannon;
	oTopCannon.iX = iWall;
	oTopCannon.iY = -iCannonHalfHeight;
	oTopCannon.iStep = s_iCannonSpeed;
	oTopCannon.eDirection = EDirection::Down;
	m_tCannons.push_back(oTopCannon);

	// Bottom right, shooting up
	SCannon oBottomCannon;
	oBottomCannon.iX = m_oMap.GetWidth() - iWall - 1;
	oBottomCannon.iY = m_oMap.GetHeight() + iCannonHalfHeight;
	oBottomCannon.iStep = -s_iCannonSpeed;
	oBottomCannon.eDirection = EDirection::Up;
	m_tCannons.push_back(oBottomCannon);
}

CTanksManager::~CTanksManager()
{
	for (CTankInfo* pTankInfo : m_tTankInfos)
	{
		delete pTankInfo->pTank;
		if (pTankInfo->pBullet)
		{
			delete pTankInfo->pBullet;
		}
		delete pTankInfo;
	}
	for (CBullet* pBullet : m_tCannonBullets)
	{
		delete pBullet;
	}
}

bool CTanksManager::AreCannonsActive() const
{
	return m_iTicks >= s_iCannonsStartSeconds * s_iTicksPerSecond;
}

void CTanksManager::Update()
{
	// The clock stops when the game is finished
	if (!IsGameFinished())
	{
		++m_iTicks;
	}

	// Update the exploding tanks and the hit flashes
	for (CTankInfo* pTankInfo : m_tTankInfos)
	{
		if (pTankInfo->bExploding && !pTankInfo->pTank->ToBeRemoved())
		{
			pTankInfo->pTank->UpdateExploding();
		}
		if (pTankInfo->iHitFlashTicks > 0)
		{
			--pTankInfo->iHitFlashTicks;
		}
	}

	// Bullets spawned this tick don't move until the next one
	std::vector<const CBullet*> tBulletsSpawnedThisTick;

	for (CTankInfo* pTankInfo : m_tTankInfos)
	{
		// Tank exploding (skip)
		if (pTankInfo->bExploding)
		{
			continue;
		}

		// Update tank
		pTankInfo->pTank->Update();

		// Turning is free: the tank always looks where it wants
		pTankInfo->eDirection = pTankInfo->pTank->eDesiredDirection;

		if (pTankInfo->pTank->eDesiredAction == EAction::Shoot &&
			pTankInfo->pTank->GetBullet())
		{
			pTankInfo->pTank->eDesiredAction = EAction::None;
		}

		// Shooting?
		if (pTankInfo->pTank->eDesiredAction == EAction::Shoot)
		{
			if (TryFireBullet(pTankInfo))
			{
				tBulletsSpawnedThisTick.push_back(pTankInfo->pBullet);
			}
		}
		// Move?
		else if (pTankInfo->pTank->eDesiredAction == EAction::Move)
		{
			TryMoveTank(pTankInfo);
		}
	}

	UpdateCannons(tBulletsSpawnedThisTick);

	// Move the bullets pixel by pixel to check all the collisions
	auto lambdaCanMove = [&tBulletsSpawnedThisTick](const CBullet* _pBullet)
	{
		return std::find(tBulletsSpawnedThisTick.begin(), tBulletsSpawnedThisTick.end(), _pBullet) == tBulletsSpawnedThisTick.end();
	};
	for (int iBulletIter = 0; iBulletIter < CTanksManager::s_iBulletSpeed; ++iBulletIter)
	{
		for (CTankInfo* pTankInfo : m_tTankInfos)
		{
			if (pTankInfo->pBullet)
			{
				UpdateBullet(pTankInfo->pBullet, lambdaCanMove(pTankInfo->pBullet));
			}
		}
		for (CBullet*& pBullet : m_tCannonBullets)
		{
			if (pBullet)
			{
				UpdateBullet(pBullet, lambdaCanMove(pBullet));
			}
		}
	}
	m_tCannonBullets.remove(nullptr);

	RemoveDeadTanks();
}

void CTanksManager::Render() const
{
	CRenderer& rRenderer = CRenderer::GetInstance();
	rRenderer.BeginFrame(s_uHudColor);
	// The map starts below the top cannon band
	rRenderer.SetOrigin(0, s_iCannonBandSize);

	m_oMap.Render();

	// Cannons
	if (AreCannonsActive())
	{
		for (const SCannon& rCannon : m_tCannons)
		{
			rRenderer.DrawCannon(CRenderer::s_iCannonColor, rCannon.eDirection, rCannon.iX, rCannon.iY);
		}
	}

	// First the exploding tanks to draw them in the back
	for (const CTankInfo* pTankInfo : m_tTankInfos)
	{
		const CTank* pTank = pTankInfo->pTank;
		if (pTankInfo->bExploding && !pTank->ToBeRemoved())
		{
			const int iFrame = std::max(0, pTank->GetExplodingFrame() - 1) / s_iExplosionFrameTicks;
			rRenderer.DrawExplosion(pTank->GetColor(), iFrame, pTankInfo->iX, pTankInfo->iY);
		}
	}

	// Tanks (animated only while moving)
	for (const CTankInfo* pTankInfo : m_tTankInfos)
	{
		if (!pTankInfo->bExploding)
		{
			const int iFrame = (pTankInfo->iMovingTicks / s_iTankAnimationFrameTicks) % CRenderer::s_iTankSpriteFrames;
			const bool bFlash = pTankInfo->iHitFlashTicks > 0 && ((pTankInfo->iHitFlashTicks - 1) / s_iHitFlashBlinkTicks) % 2 == 1;
			const int iColor = bFlash ? CRenderer::s_iFlashColor : pTankInfo->pTank->GetColor();
			rRenderer.DrawTank(pTankInfo->iSkin, iColor, pTankInfo->eDirection, iFrame, pTankInfo->iX, pTankInfo->iY);
		}
	}

	// Bullets
	for (const CBullet* pBullet : m_tBullets)
	{
		const int iColor = pBullet->pOwner ? pBullet->pOwner->GetColor() : CRenderer::s_iCannonColor;
		rRenderer.DrawRect(pBullet->iX - 2, pBullet->iY - 2, 4, 4, s_uBulletBorderColor);
		rRenderer.DrawRect(pBullet->iX - 1, pBullet->iY - 1, 2, 2, CRenderer::GetPaletteColor(iColor));
	}

	RenderHud();

	// Winner
	if (m_tTanks.size() <= 1)
	{
		const std::string sText = m_tTanks.empty() ? "DRAW" : m_tTanks.front()->GetName() + " WINS!";
		const unsigned int uColor = m_tTanks.empty() ? s_uTextColor : CRenderer::GetPaletteColor(m_tTanks.front()->GetColor());
		const int iCenterX = m_oMap.GetWidth() / 2;
		const int iCenterY = m_oMap.GetHeight() / 2;
		rRenderer.DrawRect(m_oMap.GetWallThickness(), iCenterY - 14, m_oMap.GetWidth() - 2 * m_oMap.GetWallThickness(), 28, 0xC0000000);
		rRenderer.RenderText(iCenterX, iCenterY - 9, sText, uColor, 14, true);
	}

	rRenderer.EndFrame();
}

void CTanksManager::RenderHud() const
{
	CRenderer& rRenderer = CRenderer::GetInstance();
	const int iHudX = m_oMap.GetWidth() + 6;
	// The HUD uses the whole window height (including the cannon bands)
	const int iHudY = -s_iCannonBandSize;

	rRenderer.RenderText(iHudX - 1, iHudY + 2, "TANKS", s_uTextColor, 10);

	// Clock
	const int iClockY = m_oMap.GetHeight() + s_iCannonBandSize - 26;
	rRenderer.RenderText(iHudX, iClockY, "TIME " + FormatTime(m_iTicks), s_uTextColor, 7);
	if (AreCannonsActive())
	{
		rRenderer.RenderText(iHudX, iClockY + 11, "CANNONS!", s_uWarningColor, 7);
	}
	else
	{
		const int iTicksLeft = s_iCannonsStartSeconds * s_iTicksPerSecond - m_iTicks + s_iTicksPerSecond - 1;
		rRenderer.RenderText(iHudX, iClockY + 11, "CANNONS IN " + FormatTime(iTicksLeft), s_uDimTextColor, 7);
	}

	for (size_t uIndex = 0; uIndex < m_tTankInfos.size(); ++uIndex)
	{
		const CTankInfo* pTankInfo = m_tTankInfos[uIndex];
		const CTank* pTank = pTankInfo->pTank;
		const bool bDead = pTank->IsDead();
		const int iColor = bDead ? CRenderer::s_iDeadColor : pTank->GetColor();
		const unsigned int uColor = CRenderer::GetPaletteColor(iColor);
		const int iX = iHudX + static_cast<int>(uIndex / s_iHudRows) * s_iHudColumnWidth;
		const int iY = iHudY + 22 + static_cast<int>(uIndex % s_iHudRows) * 24;

		rRenderer.DrawTank(pTankInfo->iSkin, iColor, EDirection::Up, 0, iX + s_iTankHalfSize, iY + s_iTankHalfSize);
		rRenderer.RenderText(iX + 17, iY - 2, pTank->GetName(), uColor, 7);
		if (bDead)
		{
			rRenderer.RenderText(iX + 17, iY + 6, "DEAD", uColor, 6);
		}
		else
		{
			for (int i = 0; i < s_iInitialTankHealth; ++i)
			{
				rRenderer.DrawRect(iX + 19 + i * 6, iY + 9, 4, 4, i < pTank->GetHealth() ? uColor : s_uHudEmptyHealthColor);
			}
		}
	}
}

int CTanksManager::GetHudWidth() const
{
	const int iColumns = std::max(1, (static_cast<int>(m_tTankInfos.size()) + s_iHudRows - 1) / s_iHudRows);
	return 6 + iColumns * s_iHudColumnWidth;
}

int CTanksManager::GetWindowWidth() const
{
	return m_oMap.GetWidth() + GetHudWidth();
}

int CTanksManager::GetWindowHeight() const
{
	return m_oMap.GetHeight() + 2 * s_iCannonBandSize;
}

void CTanksManager::AddTank(CTank* _pTank)
{
	if (m_tAllTanks.size() >= static_cast<size_t>(s_iMaxTanks))
	{
		printf("Too many tanks (max %d), %s not added\n", s_iMaxTanks, _pTank->GetName().c_str());
		delete _pTank;
		return;
	}
	if (std::find(m_tAllTanks.begin(), m_tAllTanks.end(), _pTank) == m_tAllTanks.end())
	{
		// Create tank info
		CTankInfo* pTankInfo = new CTankInfo();
		pTankInfo->pTank = _pTank;
		pTankInfo->iX = _pTank->GetPosInitialX();
		pTankInfo->iY = _pTank->GetPosInitialY();
		pTankInfo->iHealth = CTanksManager::s_iInitialTankHealth;
		pTankInfo->eDirection = _pTank->eDesiredDirection;
		pTankInfo->iSkin = static_cast<int>(m_tTankInfos.size()) % CRenderer::s_iTankSkins;
		_pTank->SetTankInfoRef(pTankInfo);

		m_tAllTanks.push_back(_pTank);
		m_tTanks.push_back(_pTank);
		m_tTankInfos.push_back(pTankInfo);
	}
}

bool CTanksManager::IsInsideTank(int _iX, int _iY, int _iTankX, int _iTankY)
{
	const int iLeft = _iTankX - s_iTankHalfSize;
	const int iTop = _iTankY - s_iTankHalfSize;
	return _iX >= iLeft && _iX < iLeft + s_iTankSize && _iY >= iTop && _iY < iTop + s_iTankSize;
}

void CTanksManager::TryMoveTank(CTankInfo* _pTankInfo)
{
	auto lambdaMoveCheck = [this](CTank* _pMovingTank, int X, int Y)
	{
		for (const CTank* pTank : m_tTanks)
		{
			if (pTank == _pMovingTank)
			{
				continue;
			}
			if (abs(pTank->GetPosX() - X) < s_iTankSize && abs(pTank->GetPosY() - Y) < s_iTankSize)
			{
				return false; // collision with another tank
			}
		}
		if (!m_oMap.MoveCheck(_pMovingTank, X, Y))
		{
			return false;
		}
		return true;
	};

	int iStepX = 0;
	int iStepY = 0;
	switch (_pTankInfo->eDirection)
	{
	case EDirection::Up: iStepY = -1; break;
	case EDirection::Down: iStepY = 1; break;
	case EDirection::Left: iStepX = -1; break;
	case EDirection::Right: iStepX = 1; break;
	default: return;
	}

	// Move pixel by pixel to get as close as possible to walls and tanks
	bool bMoved = false;
	for (int iStep = 0; iStep < s_iTankSpeed; ++iStep)
	{
		const int iX = _pTankInfo->iX + iStepX;
		const int iY = _pTankInfo->iY + iStepY;
		if (!lambdaMoveCheck(_pTankInfo->pTank, iX, iY))
		{
			break;
		}
		_pTankInfo->iX = iX;
		_pTankInfo->iY = iY;
		bMoved = true;
	}

	if (bMoved)
	{
		++_pTankInfo->iMovingTicks;
	}
}

bool CTanksManager::TryFireBullet(CTankInfo* _pTankInfo)
{
	if (_pTankInfo->pBullet == nullptr)
	{
		// Spawn the bullet just outside the tank, at the end of the cannon
		const int iBefore = -s_iTankHalfSize - 1;
		const int iAfter = s_iTankSize - s_iTankHalfSize;

		EDirection eDirection(_pTankInfo->eDirection);

		_pTankInfo->pBullet = new CBullet();
		_pTankInfo->pBullet->iX = static_cast<short>(_pTankInfo->iX + (eDirection == EDirection::Left ? iBefore : (eDirection == EDirection::Right ? iAfter : 0)));
		_pTankInfo->pBullet->iY = static_cast<short>(_pTankInfo->iY + (eDirection == EDirection::Up ? iBefore : (eDirection == EDirection::Down ? iAfter : 0)));
		_pTankInfo->pBullet->eDirection = eDirection;
		_pTankInfo->pBullet->pOwner = _pTankInfo->pTank;
		m_tBullets.push_back(_pTankInfo->pBullet);
		return true;
	}
	return false;
}

void CTanksManager::ProcessTankImpact(const CTank* _pTank)
{
	if (CTanksManager::GetInstance().IsGameFinished() || _pTank->IsDead())
	{
		return;
	}

	for (CTankInfo* pTankInfo : m_tTankInfos)
	{
		if (pTankInfo->pTank == _pTank)
		{
			if (pTankInfo->iHealth > 0)
			{
				--pTankInfo->iHealth;
				pTankInfo->iHitFlashTicks = s_iHitFlashTicks;

				if (pTankInfo->pTank->IsDead())
				{
					pTankInfo->bExploding = true;
				}
			}

			break;
		}
	}
}

void CTanksManager::UpdateBullet(CBullet*& _pBullet, bool _bAllowMovement)
{
	if (_pBullet)
	{
		if (_bAllowMovement)
		{
			switch (_pBullet->eDirection)
			{
			case EDirection::Up: _pBullet->iY--; break;
			case EDirection::Down: _pBullet->iY++; break;
			case EDirection::Left: _pBullet->iX--; break;
			case EDirection::Right: _pBullet->iX++; break;
			}
		}

		const CTank* pCollisionTank = nullptr;
		if (_pBullet->CollisionCheck(pCollisionTank))
		{
			if (pCollisionTank)
			{
				ProcessTankImpact(pCollisionTank);
			}
			m_tBullets.remove(_pBullet);
			delete _pBullet;
			_pBullet = nullptr;
		}
	}
}

void CTanksManager::UpdateCannons(std::vector<const CBullet*>& tBulletsSpawned_)
{
	if (!AreCannonsActive() || IsGameFinished())
	{
		return;
	}

	const int iWall = m_oMap.GetWallThickness();
	const int iMinX = iWall;
	const int iMaxX = m_oMap.GetWidth() - iWall - 1;
	const bool bShoot = (m_iTicks - s_iCannonsStartSeconds * s_iTicksPerSecond) % s_iCannonShootTicks == 0;

	for (SCannon& rCannon : m_tCannons)
	{
		// Ping-pong from side to side
		rCannon.iX += rCannon.iStep;
		if (rCannon.iX > iMaxX)
		{
			rCannon.iX = 2 * iMaxX - rCannon.iX;
			rCannon.iStep = -rCannon.iStep;
		}
		else if (rCannon.iX < iMinX)
		{
			rCannon.iX = 2 * iMinX - rCannon.iX;
			rCannon.iStep = -rCannon.iStep;
		}

		if (bShoot)
		{
			// Spawn the bullet in the first pixel inside the walls (where a tank can be)
			CBullet* pBullet = new CBullet();
			pBullet->iX = static_cast<short>(rCannon.iX);
			pBullet->iY = static_cast<short>(rCannon.eDirection == EDirection::Down ? iWall : m_oMap.GetHeight() - iWall - 1);
			pBullet->eDirection = rCannon.eDirection;
			pBullet->pOwner = nullptr;
			m_tBullets.push_back(pBullet);
			m_tCannonBullets.push_back(pBullet);
			tBulletsSpawned_.push_back(pBullet);
		}
	}
}

void CTanksManager::RemoveDeadTanks()
{
	m_tTanks.remove_if([](const CTank* _pTank)
	{
		return _pTank->ToBeRemoved();
	});
}

bool CTanksManager::IsGameFinished() const
{
	int iNumAlive(0);
	for (CTankInfo* pTankInfo : m_tTankInfos)
	{
		if (!pTankInfo->bExploding && !pTankInfo->pTank->IsExploding() && !pTankInfo->pTank->ToBeRemoved())
		{
			iNumAlive++;
		}
	}
	return iNumAlive <= 1;
}
