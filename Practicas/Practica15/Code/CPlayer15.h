/*
CPlayer empieza con 100 de vida y tiene Heal(iAmount) (máximo 100);
- puntos
AddScore() Heal()
*/
#pragma once
#include "CEntity15.h"
#include <iostream>
namespace Practica15
{
	class CPlayer :public CEntity
	{
	public:
		CPlayer(const char* _pszNombre, int _iX, int _iY, unsigned int _uVida = 100);
		virtual ~CPlayer() override; // "virtual" aquí no hace falta (con override basta), pero el profe recomienda
		// ponerlo. Ojo: override solo se escribe en el .h; en el .cpp la función se define como una normal.
		virtual void Update() override;
		virtual void Print() const override;
		void AddScore(int _iPuntos);
		void Heal(int _iCantidad);
	private:
		unsigned int uPuntos;
	};
}