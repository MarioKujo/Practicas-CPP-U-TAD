/*
▸ Update() virtual en CEntity; Print() también virtual. Cada derivada los redefine con override.
Attack recibe un CEntity&: sirve para atacar a un CPlayer o a otro CEnemy.
 CEnemy empieza con 30 de vida y su propio daño.
Los constructores llaman al de CEntity. Con un printf en constructores y destructores: ¿en qué orden salen?
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
		CEnemy(const char* _nombre, int _iX, int _iY, int _iDamage, unsigned int _uVida = 30);
		virtual ~CEnemy() override;
		void SetTarget(CEntity* other);
		virtual void Update() override;
		virtual void Print() const override;
		void Attack(CEntity& other);
	protected:
		CEntity* target = nullptr;
		int iDamage;
	};
}