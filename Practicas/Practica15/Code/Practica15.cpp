/*
CPlayer se mueve (1, 0) y suma un punto; CEnemy se mueve (-1, 0) y ataca a su objetivo.
CTurret hereda de CEnemy (50 de vida, daño 5): no se mueve, solo ataca. CEnemy recibe la vida en el constructor.
Todas en una tabla de CEntity*; cada turno, Update() y Print() de todas sin saber su tipo.
delete por CEntity*: ¿qué pasa con y sin destructor virtual?

- Sin destructor virtual, 'delete pEntity' sobre un 'CEntity*' que apunta a una hija es comportamiento indefinido:
normalmente solo se ejecuta '~CEntity', así que lo que reserve la hija (por ejemplo, un nombre con 'new char[]')
se pierde en una fuga. Con 'virtual ~CEntity()', 'delete' sigue la vtable y destruye de la clase más derivada
a la base ('~CTurret', '~CEnemy', '~CEntity').
*/
#include <iostream>
#include "CEnemy15.h"
#include "CPlayer15.h"
#include "CTurret.h"
#include <crtdbg.h>
int main()
{
	// Al terminar el programa, Visual Studio avisa en la ventana de salida si algún "new" se quedó sin su "delete"
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// "new" crea el objeto en el heap y devuelve su dirección de memoria, que guardamos en un puntero
	Practica15::CEnemy* pOrc = new Practica15::CEnemy("Orco", 10, 0, 10);
	Practica15::CTurret* pTurret = new Practica15::CTurret("Torreta", 5, 2, 5);
	Practica15::CPlayer* pPlayer = new Practica15::CPlayer("Heroe", 0, 0);

	pOrc->SetTarget(pPlayer);    // "->" es como "." pero a través de un puntero
	pTurret->SetTarget(pPlayer);

	// Tabla de punteros a la clase base: guarda a la vez un CPlayer, un CEnemy y un CTurret
	Practica15::CEntity* tpEntities[] = { pPlayer, pOrc, pTurret };
	for (int iTurn = 1; iTurn <= 3; ++iTurn)
	{
		// Recorre la tabla: pEntity va tomando cada dirección guardada en ella
		for (Practica15::CEntity* pEntity : tpEntities)
			pEntity->Update(); // ¿cuál? la de su tipo
		for (Practica15::CEntity* pEntity : tpEntities)
			pEntity->Print();
	}
	// Todo lo creado con "new" hay que liberarlo con "delete"
	for (Practica15::CEntity* pEntity : tpEntities)
		delete pEntity; // ¿destructor virtual?
}