/*
CEnemy empieza con 30 de vida y su propio daño.
Attack recibe un CEntity&: sirve para atacar a un CPlayer o a otro CEnemy.
- daño
*/
#pragma once
#include "CEntity13.h"
#include <iostream>
namespace Practica13
{
	// ":public CEntity" significa que CEnemy hereda de CEntity. Gracias a que los miembros de CEntity
	// son protected, CEnemy tiene pszNombre, iX, iY y uVida sin declararlos otra vez, además de las
	// funciones públicas de CEntity (Move, TakeDamage, IsAlive, Print).
	class CEnemy :public CEntity
	{
	public:
		// El valor por defecto de _uVida (30) solo se escribe aquí, en el .h
		CEnemy(const char* _pszNombre, int _iX, int _iY, int _iDamage, unsigned int _uVida = 30);
		~CEnemy();
		void Attack(CEntity& _oObjetivo); // "&": referencia, el objeto original (no una copia)
	private:
		int iDamage;
	};
}