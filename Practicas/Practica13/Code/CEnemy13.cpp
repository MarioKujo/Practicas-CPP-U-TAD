#include "CEnemy13.h"

namespace Practica13
{
	// Primero se construye la parte CEntity (la llamamos en la lista de inicialización) y luego el atributo propio,
	// iDamage
	CEnemy::CEnemy(const char* _pszNombre, int _iX, int _iY, int _iDamage, unsigned int _uVida)
		: CEntity(_pszNombre, _iX, _iY, _uVida), iDamage(_iDamage)
	{
		printf("Constructor de CEnemy\n");
	}

	CEnemy::~CEnemy()
	{
		printf("Destructor de CEnemy\n");
	}

	void CEnemy::Attack(CEntity& _oObjetivo)
	{
		// _oObjetivo es una referencia: otro nombre para el objeto original (CPlayer u otro CEnemy), sin copiarlo.
		// No podemos tocar _oObjetivo.uVida directamente: una clase hija solo accede a los miembros protected
		// de sí misma, no a los de otro objeto declarado como CEntity. Por eso se llama a TakeDamage().
		_oObjetivo.TakeDamage(iDamage);
		printf("%s ha hecho %d de damage.\n", pszNombre, iDamage);
	}
}