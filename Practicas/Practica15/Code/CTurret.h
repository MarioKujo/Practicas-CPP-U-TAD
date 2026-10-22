/*
▸ Update() virtual en CEntity; Print() también virtual. Cada derivada los redefine con override.
▸ CTurret hereda de CEnemy (50 de vida, daño 5): no se mueve, solo ataca. CEnemy recibe la vida en el constructor.
*/
#pragma once
#include "CEntity15.h"
#include "CEnemy15.h"
namespace Practica15
{
	class CTurret : public CEnemy
	{
	public:
		CTurret(const char* _nombre, int _iX, int _iY, int _iDamage = 5, unsigned int _uVida = 50);
		virtual ~CTurret() override;
		virtual void Update() override;
	};
}