#include "CEnemy15.h"
namespace Practica15
{
	CEnemy::CEnemy(const char* _pszNombre, int _iX, int _iY, int _iDamage, unsigned int _uVida)
		:CEntity(_pszNombre, _iX, _iY, _uVida)
		, iDamage(_iDamage)
	{
	}

	CEnemy::~CEnemy()
	{
	}

	void CEnemy::SetTarget(CEntity* _pObjetivo)
	{
		pObjetivo = _pObjetivo; // Guardamos la dirección, no una copia: el objetivo sigue siendo el objeto original
	}

	void CEnemy::Update()
	{
		Move(iX - 1, 0); // Se mueve una casilla a la izquierda
		// pObjetivo es un puntero (una dirección); con "*" accedemos al objeto al que apunta,
		// que es lo que espera Attack (una referencia a un objeto, no una dirección)
		Attack(*pObjetivo);
	}

	void CEnemy::Print() const
	{
		printf("%s en (%d, %d) con %u de vida, damage %d\n", pszNombre, iX, iY, uVida, iDamage);
	}

	void CEnemy::Attack(CEntity& _oObjetivo)
	{
		_oObjetivo.TakeDamage(iDamage);
	}
}