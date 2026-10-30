#include "Tank.h"

#include "../Bullet.h"
#include "../TankInfo.h"
#include "../TanksManager.h"
#include "../Renderer.h"

CTank::CTank(std::string _sName, int _iX, int _iY, int _iColor)
{
	m_sName = _sName;
	m_iInitialX = _iX;
	m_iInitialY = _iY;
	m_iColor = _iColor;
}

std::string CTank::GetName() const
{
	return m_sName;
}

int CTank::GetColor() const
{
	return m_iColor;
}

int CTank::GetPosInitialX() const
{
	return m_iInitialX;
}

int CTank::GetPosInitialY() const
{
	return m_iInitialY;
}

int CTank::GetPosX() const
{
	return m_pTankInfo->iX;
}

int CTank::GetPosY() const
{
	return m_pTankInfo->iY;
}

void CTank::GetPos(int& iX_, int& iY_) const
{
	iX_ = m_pTankInfo->iX;
	iY_ = m_pTankInfo->iY;
}

EDirection CTank::GetDirection() const
{
	return m_pTankInfo->eDirection;
}

void CTank::SetTankInfoRef(const CTankInfo* _pTankInfo)
{
	m_pTankInfo = _pTankInfo;
}

const CBullet* CTank::GetBullet() const
{
	return m_pTankInfo->pBullet;
}

bool CTank::ToBeRemoved() const
{
	if (m_iExplodingFrame > CRenderer::s_iExplosionFrames * CTanksManager::s_iExplosionFrameTicks)
	{
		return true;
	}
	return false;
}

void CTank::UpdateExploding()
{
	m_iExplodingFrame++;
}

bool CTank::IsExploding() const
{
	return m_iExplodingFrame > 0;
}

int CTank::GetExplodingFrame() const
{
	return m_iExplodingFrame;
}

int CTank::GetHealth() const
{
	return m_pTankInfo->iHealth;
}

bool CTank::IsDead() const
{
	return m_pTankInfo->iHealth <= 0;
}
