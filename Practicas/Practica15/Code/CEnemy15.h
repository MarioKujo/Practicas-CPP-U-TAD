/*
Update() virtual en CEntity; Print() también virtual. Cada derivada los redefine con override.
Attack recibe un CEntity&: sirve para atacar a un CPlayer o a otro CEnemy.
CEnemy empieza con 30 de vida y su propio daño.
- daño
Attack(CEntity&)
*/
#pragma once
#include "CEntity15.h"
#include <iostream>
namespace Practica15
{
	class CEnemy :public CEntity
	{
	public:
		CEnemy(const char* _pszNombre, int _iX, int _iY, int _iDamage, unsigned int _uVida = 30);
		virtual ~CEnemy() override;
		void SetTarget(CEntity* _pObjetivo); // Recibe un puntero: la dirección de memoria del objetivo
		virtual void Update() override;
		virtual void Print() const override;
		void Attack(CEntity& _oObjetivo);
	protected:
		// protected (y no private) para que CTurret, que hereda de CEnemy, también pueda usarlos
		CEntity* pObjetivo = nullptr; // nullptr = "no apunta a nada" hasta que se llame a SetTarget
		int iDamage;
	};
}