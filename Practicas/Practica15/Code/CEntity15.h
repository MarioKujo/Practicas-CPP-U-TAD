/*
▸ Update() virtual en CEntity; Print() también virtual. Cada derivada los redefine con override.
*/
#pragma once
#include <iostream>
namespace Practica15
{
	class CEntity
	{
	public:
		CEntity(const char* _nombre, int _iX, int _iY, unsigned int _uVida);
		virtual ~CEntity();
		virtual void Update() = 0;
		void Move(int iDX, int iDY);
		void TakeDamage(int iDamage);
		bool IsAlive() const;
		virtual void Print() const = 0;
	protected:
		const char* nombre;
		int iX;
		int iY;
		unsigned int uVida;
	};
}