#include "CEntity15.h"
namespace Practica15
{
	CEntity::CEntity(const char* _nombre, int _iX, int _iY, unsigned int _uVida) :nombre(_nombre), iX(_iX), iY(_iY), uVida(_uVida)
	{
	}

	CEntity::~CEntity()
	{
	}

	void CEntity::Move(int iDX, int iDY)
	{
		iX = iDX;
		iY = iDY;
	}

	void CEntity::TakeDamage(int iDamage)
	{
		uVida -= iDamage;
	}

	bool CEntity::IsAlive() const
	{
		bool isAlive = uVida > 0;
		printf("%s %s vivo\n", nombre, isAlive ? "sigue" : "no sigue");
		return uVida > 0;
	}
}