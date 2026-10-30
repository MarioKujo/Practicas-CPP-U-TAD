#pragma once

class CTank;
class CBullet;

// Map in pixels, surrounded by walls
class CMap
{
public:
	virtual int GetHeight() const;
	virtual int GetWidth() const;
	virtual int GetWallThickness() const;

	bool IsWall(int _iX, int _iY) const;
	bool MoveCheck(CTank* _pMovingTank, int _iX, int _iY) const;
	bool CheckBulletCollision(CBullet* _pBullet) const;

	void Render() const;
};
