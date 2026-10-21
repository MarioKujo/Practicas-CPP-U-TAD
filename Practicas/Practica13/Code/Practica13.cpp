#include "CEntity.h"
#include "CEnemy.h"
#include "CPlayer.h"
#include <iostream>
int main()
{
	CPlayer oPlayer("Heroe", 0, 0);
	CEnemy oOrc("Orco", 5, 0, 25);
	CEnemy oGoblin("Trasgo", 8, 3, 15);
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