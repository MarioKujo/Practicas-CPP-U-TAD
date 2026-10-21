#include "CEnemy.h"

CEnemy::CEnemy(const char* _nombre, int _iX, int _iY, int _iDamage, unsigned int _uVida):CEntityVirtual(_nombre, _iX, _iY, _uVida), iDamage(_iDamage)
{
	printf("Constructor de CEnemy\n");
}

CEnemy::~CEnemy()
{
	printf("Destructor de CEnemy\n");
}

void CEnemy::Attack(CEntityVirtual& other)
{
	other.TakeDamage(iDamage);
	printf("%s ha hecho %d de damage.\n", nombre, iDamage);
}
