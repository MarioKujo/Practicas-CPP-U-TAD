#include "CEntity13.h"
namespace Practica13
{
	CEntity::CEntity(const char* _nombre, int _iX, int _iY, unsigned int _uVida) :nombre(_nombre), iX(_iX), iY(_iY), uVida(_uVida)
	{
		printf("Constructor de CEntity\n");
	}

	CEntity::~CEntity()
	{
		printf("Destructor de CEntity\n");
	}

	void CEntity::Move(int iDX, int iDY)
	{
		iX = iDX;
		iY = iDY;
		printf("%s se ha movido a (%d, %d)\n", nombre, iX, iY);
	}

	void CEntity::TakeDamage(int iDamage)
	{
		printf("%s ha recibido %d de damage.\n", nombre, iDamage);
		uVida -= iDamage;
	}

	bool CEntity::IsAlive() const
	{
		bool isAlive = uVida > 0;
		printf("%s %s vivo\n", nombre, isAlive ? "sigue" : "no sigue");
		return uVida > 0;
	}

	void CEntity::Print() const
	{
		printf("%s en (%d, %d) con %u de vida\n", nombre, iX, iY, uVida);
	}
}