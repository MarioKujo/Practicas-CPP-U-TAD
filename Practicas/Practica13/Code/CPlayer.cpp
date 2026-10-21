#include "CPlayer.h"

CPlayer::CPlayer(const char* _nombre, int _iX, int _iY, unsigned int _uVida):CEntityVirtual(_nombre, _iX, _iY, _uVida), puntos(0)
{
	printf("Constructor de CPlayer\n");
}

CPlayer::~CPlayer()
{
	printf("Destructor de CPlayer\n");
}

void CPlayer::AddScore(int _iPuntos)
{
	printf("%d puntos agregados a %s\n", _iPuntos, nombre);
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
