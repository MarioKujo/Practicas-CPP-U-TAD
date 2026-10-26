/*
CPlayer se mueve (1, 0) y suma un punto;
*/
#include "CPlayer15.h"
#include <cstdio>
namespace Practica15
{
	CPlayer::CPlayer(const char* _pszNombre, int _iX, int _iY, unsigned int _uVida)
		: CEntity(_pszNombre, _iX, _iY, _uVida)
		, m_uPuntos(0)
	{
	}

	CPlayer::~CPlayer()
	{
	}

	void CPlayer::Update()
	{
		Move(m_iX + 1, m_iY); // Una casilla a la derecha, en la misma fila
		AddScore(1);
	}

	void CPlayer::Print() const
	{
		printf("%s en (%d, %d) con %u de vida, %u puntos\n", m_pszNombre, m_iX, m_iY, m_uVida, m_uPuntos);
	}

	void CPlayer::AddScore(int _iPuntos)
	{
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