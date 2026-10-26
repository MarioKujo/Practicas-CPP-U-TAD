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
#include <crtdbg.h> // Solo existe en Visual Studio
int main()
{
	// Al cerrar el programa, Visual Studio avisa en la ventana Salida si algún new se quedó sin su delete
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// new crea el objeto en el heap y devuelve su dirección, que se guarda en un puntero
	Practica15::CEnemy* const pOrc = new Practica15::CEnemy("Orco", 10, 0, 10);
	Practica15::CTurret* const pTurret = new Practica15::CTurret("Torreta", 5, 2, 5);
	Practica15::CPlayer* const pPlayer = new Practica15::CPlayer("Heroe", 0, 0);

	pOrc->SetTarget(pPlayer); // -> es como el punto, pero para acceder a través de un puntero
	pTurret->SetTarget(pPlayer);

	// Array de punteros a la clase base: guarda a la vez un CPlayer, un CEnemy y un CTurret.
	// Un CPlayer* se convierte solo a CEntity* porque CPlayer ES una CEntity
	Practica15::CEntity* const apEntities[] = { pPlayer, pOrc, pTurret };
	for (int iTurno = 1; iTurno <= 3; ++iTurno)
	{
		// Aquí está el polimorfismo: el código no sabe de qué tipo es cada pEntity,
		// y cada llamada ejecuta la versión de la clase real del objeto (consulta su vtable, ver práctica 14)
		for (Practica15::CEntity* const pEntity : apEntities)
			pEntity->Update();
		for (Practica15::CEntity* const pEntity : apEntities)
			pEntity->Print();
	}

	// Todo lo creado con new se libera con delete. Como ~CEntity es virtual, cada delete
	// ejecuta primero el destructor de la clase real y después el de sus bases
	for (Practica15::CEntity* pEntity : apEntities)
		delete pEntity;
}