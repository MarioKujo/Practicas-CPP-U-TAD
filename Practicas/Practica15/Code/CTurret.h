/*
Update() virtual en CEntity; Print() también virtual. Cada derivada los redefine con override.
CTurret hereda de CEnemy (50 de vida, daño 5): no se mueve, solo ataca. CEnemy recibe la vida en el constructor.
*/
#pragma once
#include "CEnemy15.h"
namespace Practica15
{
	// Herencia de dos niveles: CTurret hereda de CEnemy, que hereda de CEntity
	class CTurret : public CEnemy
	{
	public:
		CTurret(const char* _pszNombre, int _iX, int _iY, int _iDamage = 5, unsigned int _uVida = 50);
		virtual ~CTurret() override; // Sustituye al de CEnemy, que a su vez sustituía al de CEntity: es válido
		virtual void Update() override;
		// No redefine Print(): usa el de CEnemy, que ya sirve
	};
}