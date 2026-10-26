#include "CPlayer13.h"
#include <cstdio>

namespace Practica13
{
	// Igual que en CEnemy: primero se construye la parte CEntity y luego m_uPuntos
	CPlayer::CPlayer(const char* _pszNombre, int _iX, int _iY, unsigned int _uVida)
		: CEntity(_pszNombre, _iX, _iY, _uVida)
		, m_uPuntos(0)
	{
		printf("Constructor de CPlayer\n");
	}

	CPlayer::~CPlayer()
	{
		printf("Destructor de CPlayer\n");
	}

	void CPlayer::AddScore(int _iPuntos)
	{
		printf("%d puntos agregados a %s\n", _iPuntos, m_pszNombre);
		m_uPuntos += _iPuntos;
	}

	void CPlayer::Heal(int _iCantidad)
	{
		printf("%d vida curada a %s\n", _iCantidad, m_pszNombre);
		m_uVida += _iCantidad;
		if (m_uVida > 100) // La vida máxima del jugador es 100
		{
			m_uVida = 100;
		}
	}
}