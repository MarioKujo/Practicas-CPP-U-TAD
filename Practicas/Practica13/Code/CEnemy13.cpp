#include "CEnemy13.h"

// Se explica solo, la verdad

namespace Practica13
{
	CEnemy::CEnemy(const char* _nombre, int _iX, int _iY, int _iDamage, unsigned int _uVida) :CEntity(_nombre, _iX, _iY, _uVida), iDamage(_iDamage)
	{
		printf("Constructor de CEnemy\n");
	}

	CEnemy::~CEnemy()
	{
		printf("Destructor de CEnemy\n");
	}

	void CEnemy::Attack(CEntity& other)
	{
		other.TakeDamage(iDamage); // other es un CEntity&: una clase derivada solo puede acceder a los miembros
		// protegidos a través de objetos de su propio tipo (CEnemy), no de la base. Por eso se usa TakeDamage().
		printf("%s ha hecho %d de damage.\n", nombre, iDamage);
	}
}