#include "CEntity13.h"
namespace Practica13
{
	// Después de los ":" va la lista de inicialización: da valor a los atributos
	// en el momento de crear el objeto, antes de ejecutar el cuerpo del constructor.
	CEntity::CEntity(const char* _pszNombre, int _iX, int _iY, unsigned int _uVida)
		: pszNombre(_pszNombre)
		, iX(_iX)
		, iY(_iY)
		, uVida(_uVida)
	{
		printf("Constructor de CEntity\n");
	}

	CEntity::~CEntity()
	{
		printf("Destructor de CEntity\n");
	}

	void CEntity::Move(int _iDX, int _iDY)
	{
		// Ojo: asigna la posición directamente, no la suma a la anterior
		iX = _iDX;
		iY = _iDY;
		printf("%s se ha movido a (%d, %d)\n", pszNombre, iX, iY); // %s = texto, %d = entero
	}

	void CEntity::TakeDamage(int _iDamage)
	{
		printf("%s ha recibido %d de damage.\n", pszNombre, _iDamage);
		uVida -= _iDamage;
	}

	bool CEntity::IsAlive() const
	{
		bool bIsAlive = uVida > 0;

		printf("%s %s vivo\n", pszNombre, bIsAlive ? "sigue" : "no sigue");
		return bIsAlive;
	}

	void CEntity::Print() const
	{
		printf("%s en (%d, %d) con %u de vida\n", pszNombre, iX, iY, uVida); // %u = entero sin signo
	}
}