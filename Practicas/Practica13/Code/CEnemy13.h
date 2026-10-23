/*
Attack recibe un CEntity&: sirve para atacar a un CPlayer o a otro CEnemy.
 CEnemy empieza con 30 de vida y su propio daño.
Los constructores llaman al de CEntity. Con un printf en constructores y destructores: ¿en qué orden salen?
- daño
Attack(CEntity&)
*/
#pragma once
#include "CEntity13.h"
#include <iostream>
namespace Practica13
{
	// Gracias a que CEntity tiene sus miembros protected, CEnemy recibe nombre, iX, iY, uVida sin tener que declararlos
	// aquí, además de las funciones públicas de CEntity (Move, TakeDamage, IsAlive, Print)
	class CEnemy :public CEntity
	{
	public:
		CEnemy(const char* _nombre, int _iX, int _iY, int _iDamage, unsigned int _uVida = 30);
		~CEnemy();
		void Attack(CEntity& other);
	private:
		int iDamage;
	};
}