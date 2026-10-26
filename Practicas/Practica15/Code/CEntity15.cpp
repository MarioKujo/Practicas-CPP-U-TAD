#include "CEntity15.h"
namespace Practica15
{
	CEntity::CEntity(const char* _pszNombre, int _iX, int _iY, unsigned int _uVida)
		:pszNombre(_pszNombre)
		, iX(_iX)
		, iY(_iY)
		, uVida(_uVida)
	{
	}

	CEntity::~CEntity()
	{
	}

	void CEntity::Move(int _iDX, int _iDY)
	{
		// Asigna la posición, no la suma: por eso las hijas pasan "iX + 1" o "iX - 1" para avanzar o retroceder
		iX = _iDX;
		iY = _iDY;
	}

	void CEntity::TakeDamage(int _iDamage)
	{
		uVida -= _iDamage;
	}

	bool CEntity::IsAlive() const
	{
		bool bIsAlive = uVida > 0;
		printf("%s %s vivo\n", pszNombre, bIsAlive ? "sigue" : "no sigue");
		return bIsAlive;
	}
}