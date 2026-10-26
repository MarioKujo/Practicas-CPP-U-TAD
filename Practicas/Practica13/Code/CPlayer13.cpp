#include "CPlayer13.h"

namespace Practica13
{
	// Primero se construye la parte CEntity (la llamamos en la lista de inicialización) y luego el atributo propio,
	// uPuntos
	CPlayer::CPlayer(const char* _pszNombre, int _iX, int _iY, unsigned int _uVida)
		: CEntity(_pszNombre, _iX, _iY, _uVida)
		, uPuntos(0)
	{
		printf("Constructor de CPlayer\n");
	}

	CPlayer::~CPlayer()
	{
		printf("Destructor de CPlayer\n");
	}

	void CPlayer::AddScore(int _iPuntos)
	{
		printf("%d puntos agregados a %s\n", _iPuntos, pszNombre);
		uPuntos += _iPuntos;
	}

	void CPlayer::Heal(int _iCantidad)
	{
		printf("%d vida curada a %s\n", _iCantidad, pszNombre);
		uVida += _iCantidad;
		// La vida máxima del jugador es 100
		if (uVida > 100)
		{
			uVida = 100;
		}
	}
}