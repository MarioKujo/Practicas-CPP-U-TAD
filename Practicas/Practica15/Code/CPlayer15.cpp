/*
CPlayer se mueve (1, 0) y suma un punto;
*/
#include "CPlayer15.h"
namespace Practica15
{
	CPlayer::CPlayer(const char* _pszNombre, int _iX, int _iY, unsigned int _uVida) :CEntity(_pszNombre, _iX, _iY, _uVida), uPuntos(0)
	{
	}

	CPlayer::~CPlayer()
	{
	}

	void CPlayer::Update()
	{
		Move(iX + 1, 0); // Se mueve una casilla a la derecha
		AddScore(1);
	}

	void CPlayer::Print() const
	{
		printf("%s en (%d, %d) con %u de vida, %d puntos\n", pszNombre, iX, iY, uVida, uPuntos);
	}

	void CPlayer::AddScore(int _iPuntos)
	{
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