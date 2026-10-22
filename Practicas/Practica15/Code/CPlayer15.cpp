/*
▸ CPlayer se mueve (1, 0) y suma un punto;
*/
#include "CPlayer15.h"
namespace Practica15
{
	CPlayer::CPlayer(const char* _nombre, int _iX, int _iY, unsigned int _uVida) :CEntity(_nombre, _iX, _iY, _uVida), puntos(0)
	{
	}

	CPlayer::~CPlayer()
	{
	}

	void CPlayer::Update()
	{
		Move(iX + 1, 0);
		AddScore(1);
	}

	void CPlayer::Print() const
	{
		printf("%s en (%d, %d) con %u de vida, %d puntos\n", nombre, iX, iY, uVida, puntos);
	}

	void CPlayer::AddScore(int _iPuntos)
	{
		puntos += _iPuntos;
	}

	void CPlayer::Heal(int _iAmount)
	{
		printf("%d vida curada a %s\n", _iAmount, nombre);
		uVida += _iAmount;
		if (uVida > 100)
		{
			uVida = 100;
		}
	}
}