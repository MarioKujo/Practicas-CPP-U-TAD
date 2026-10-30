#pragma once

#include <string>

#include "../Direction.h"
#include "../Action.h"

class CBullet;
class CTankInfo;

class CTank
{
public:
	// _iColor: color index (0-15, like the console colors)
	CTank(std::string _sName, int _iX, int _iY, int _iColor);

	virtual void Update() = 0;

	// Direction the tank looks at. Turning is free: the tank moves and shoots in this direction
	EDirection eDesiredDirection = EDirection::Down;
	// Desired action: move forward or shoot in eDesiredDirection
	EAction eDesiredAction = EAction::None;

	// Name
	std::string GetName() const;
	// Color
	int GetColor() const;
	// Initial Position
	int GetPosInitialX() const;
	int GetPosInitialY() const;
	// Position (in pixels, center of the tank)
	int GetPosX() const;
	int GetPosY() const;
	void GetPos(int& iX_, int& iY_) const;
	// Current direction
	EDirection GetDirection() const;
	void SetTankInfoRef(const CTankInfo* _pTankInfo);
	// Bullet
	const CBullet* GetBullet() const;
	// To be removed?
	bool ToBeRemoved() const;
	// Exploding
	void UpdateExploding();
	bool IsExploding() const;
	int GetExplodingFrame() const;
	// Health
	int GetHealth() const;
	bool IsDead() const;

private:
	std::string m_sName = "Default";
	int m_iColor = 1;
	int m_iInitialX;
	int m_iInitialY;
	const CTankInfo* m_pTankInfo = nullptr;
	int m_iExplodingFrame = 0;
};
