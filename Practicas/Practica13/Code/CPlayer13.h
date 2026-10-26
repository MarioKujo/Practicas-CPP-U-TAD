/*
CPlayer empieza con 100 de vida y tiene Heal(iAmount) (máximo 100);
- puntos
AddScore() Heal()
*/
#pragma once
#include "CEntity13.h"
#include <iostream>
namespace Practica13
{
	// ":public CEntity" significa que CPlayer hereda de CEntity. Gracias a que los miembros de CEntity
	// son protected, CPlayer tiene pszNombre, iX, iY y uVida sin declararlos otra vez, además de las
	// funciones públicas de CEntity (Move, TakeDamage, IsAlive, Print).
	class CPlayer :public CEntity
	{
	public:
		// El valor por defecto de _uVida (100) solo se escribe aquí, en el .h
		CPlayer(const char* _pszNombre, int _iX, int _iY, unsigned int _uVida = 100);
		~CPlayer();
		void AddScore(int _iPuntos);
		void Heal(int _iCantidad);
	private:
		unsigned int uPuntos;
	};
}