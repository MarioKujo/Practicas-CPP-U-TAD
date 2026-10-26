#include "CTurret.h"
namespace Practica15
{
	CTurret::CTurret(const char* _pszNombre, int _iX, int _iY, int _iDamage, unsigned int _uVida)
		: CEnemy(_pszNombre, _iX, _iY, _iDamage, _uVida)
	{
	}

	CTurret::~CTurret()
	{
	}

	void CTurret::Update()
	{
		Attack(*pObjetivo); // A diferencia de CEnemy, no se mueve: solo ataca
	}
}