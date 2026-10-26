/*
Práctica 15 - Polimorfismo
Update() virtual en CEntity; Print() también virtual. Cada derivada los redefine con override.

Mismas convenciones de nombres que en la práctica 13. Prefijos nuevos: p = puntero, t = tabla (array).
*/
#pragma once
#include <iostream>
namespace Practica15
{
	class CEntity
	{
	public:
		CEntity(const char* _pszNombre, int _iX, int _iY, unsigned int _uVida);
		virtual ~CEntity(); // virtual: necesario para que delete a través de un CEntity* llame también al destructor de
		// la hija
		virtual void Update() = 0; // "= 0": virtual pura, no tiene cuerpo y obliga a las hijas a hacer override
		void Move(int _iDX, int _iDY);
		void TakeDamage(int _iDamage);
		bool IsAlive() const;
		virtual void Print() const = 0; // Virtual pura: cada hija decide cómo se imprime
	protected:
		const char* pszNombre;
		int iX;
		int iY;
		unsigned int uVida;
	};
}