#include "CEntity13.h"
#include "CEnemy13.h"
#include "CPlayer13.h"
#include <iostream>
int main()
{
	// Los objetos se crean en la pila: se destruyen solos al acabar main, en orden inverso al de creación.
	Practica13::CPlayer oPlayer("Heroe", 0, 0);
	Practica13::CEnemy oOrc("Orco", 5, 0, 25);
	Practica13::CEnemy oGoblin("Trasgo", 8, 3, 15);

	oPlayer.Move(2, 1);

	// Attack recibe una referencia: el daño se aplica al oPlayer original, no a una copia suya
	oOrc.Attack(oPlayer);
	oOrc.Attack(oPlayer);
	oPlayer.Print();

	oGoblin.Attack(oOrc);
	oGoblin.Attack(oOrc);
	if (!oOrc.IsAlive())
	{
		oPlayer.AddScore(10);
	}
}