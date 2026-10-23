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
		virtual ~CEntity(); // <-- Necesario, virtual para que llame también a los destructores de las derivadas
		virtual void Update() = 0; // <-- Así obligas a que las derivadas le hagan override
		void Move(int iDX, int iDY);
		void TakeDamage(int iDamage);
		bool IsAlive() const;
		virtual void Print() const = 0; // <-- Así obligas a que las derivadas le hagan override
	protected:
		const char* nombre;
		int iX;
		int iY;
		unsigned int uVida;
	};
}