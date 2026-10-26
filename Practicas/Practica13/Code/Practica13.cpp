#include "CEntity13.h"
#include "CEnemy13.h"
#include "CPlayer13.h"
#include <cstdio>
#include <iostream>
int main()
{
	// Los objetos se crean en la pila: se destruyen solos al acabar main, en orden inverso al de creación
	// (oGoblin, oOrc y oPlayer), y cada uno destruye primero su parte hija y después su parte CEntity
	Practica13::CPlayer oPlayer("Heroe", 0, 0);
	Practica13::CEnemy oOrc("Orco", 5, 0, 25);
	Practica13::CEnemy oGoblin("Trasgo", 8, 3, 15);

	oPlayer.Move(2, 1);

	// Attack recibe una referencia: el daño se aplica al oPlayer original, no a una copia
	oOrc.Attack(oPlayer);
	oOrc.Attack(oPlayer);
	oPlayer.Print();

	// El orco tiene 30 de vida y el trasgo hace 15 por ataque: tras dos ataques queda en 0
	oGoblin.Attack(oOrc);
	oGoblin.Attack(oOrc);
	if (!oOrc.IsAlive())
	{
		oPlayer.AddScore(10);
	}
}