#include "Map.h"

#include "TanksManager.h"
#include "Bullet.h"
#include "Renderer.h"

namespace
{
	const unsigned int s_uFloorColor = 0xFF30343B;
	const unsigned int s_uFloorGridColor = 0xFF363A42;
	const unsigned int s_uWallColor = 0xFF7A808C;
	const unsigned int s_uWallBorderColor = 0xFF4A4E57;
	const int s_iFloorGridSize = 16;
}

int CMap::GetHeight() const
{
	return 224;
}

int CMap::GetWidth() const
{
	return 320;
}

int CMap::GetWallThickness() const
{
	return 4;
}

bool CMap::IsWall(int X, int Y) const
{
	const int iWall = GetWallThickness();
	if (X < iWall || X >= GetWidth() - iWall || Y < iWall || Y >= GetHeight() - iWall)
	{
		return true;
	}
	return false;
}

bool CMap::MoveCheck(CTank* _pMovingTank, int X, int Y) const
{
	// The tank is a square centered in (X, Y). The walls are only in the borders,
	// so checking two opposite corners is enough
	const int iLeft = X - CTanksManager::s_iTankHalfSize;
	const int iTop = Y - CTanksManager::s_iTankHalfSize;
	const int iRight = iLeft + CTanksManager::s_iTankSize - 1;
	const int iBottom = iTop + CTanksManager::s_iTankSize - 1;

	if (IsWall(iLeft, iTop) || IsWall(iRight, iBottom))
	{
		return false; // collision with border walls
	}

	return true;
}

bool CMap::CheckBulletCollision(CBullet* bullet) const
{
	return IsWall(bullet->iX, bullet->iY);
}

void CMap::Render() const
{
	CRenderer& rRenderer = CRenderer::GetInstance();
	const int iWidth = GetWidth();
	const int iHeight = GetHeight();
	const int iWall = GetWallThickness();

	// Floor
	rRenderer.DrawRect(0, 0, iWidth, iHeight, s_uFloorColor);
	for (int iX = iWall + s_iFloorGridSize; iX < iWidth - iWall; iX += s_iFloorGridSize)
	{
		rRenderer.DrawRect(iX, iWall, 1, iHeight - 2 * iWall, s_uFloorGridColor);
	}
	for (int iY = iWall + s_iFloorGridSize; iY < iHeight - iWall; iY += s_iFloorGridSize)
	{
		rRenderer.DrawRect(iWall, iY, iWidth - 2 * iWall, 1, s_uFloorGridColor);
	}

	// Walls
	rRenderer.DrawRect(0, 0, iWidth, iWall, s_uWallColor);
	rRenderer.DrawRect(0, iHeight - iWall, iWidth, iWall, s_uWallColor);
	rRenderer.DrawRect(0, 0, iWall, iHeight, s_uWallColor);
	rRenderer.DrawRect(iWidth - iWall, 0, iWall, iHeight, s_uWallColor);

	// Inner border of the walls
	rRenderer.DrawRect(iWall - 1, iWall - 1, iWidth - 2 * iWall + 2, 1, s_uWallBorderColor);
	rRenderer.DrawRect(iWall - 1, iHeight - iWall, iWidth - 2 * iWall + 2, 1, s_uWallBorderColor);
	rRenderer.DrawRect(iWall - 1, iWall - 1, 1, iHeight - 2 * iWall + 2, s_uWallBorderColor);
	rRenderer.DrawRect(iWidth - iWall, iWall - 1, 1, iHeight - 2 * iWall + 2, s_uWallBorderColor);
}
