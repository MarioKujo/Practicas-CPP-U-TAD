#include "CEntity13.h"
#include "CEnemy13.h"
#include "CPlayer13.h"
#include <iostream>
int main()
{
	Practica13::CPlayer oPlayer("Heroe", 0, 0);
	Practica13::CEnemy oOrc("Orco", 5, 0, 25);
	Practica13::CEnemy oGoblin("Trasgo", 8, 3, 15);
	oPlayer.Move(2, 1);
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