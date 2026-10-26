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
	class CPlayer : public CEntity
	{
	public:
		CPlayer(const char* _pszNombre, int _iX, int _iY, unsigned int _uVida = 100);

		// "override" le dice al compilador que esta función sustituye a una virtual de la base: si la firma
		// no coincide, da error en vez de crear una función distinta sin avisar. Con override el "virtual"
		// sobra, pero se deja porque el profe lo recomienda. Solo se escribe en el .h, no en el .cpp
		virtual ~CPlayer() override;
		virtual void Update() override;
		virtual void Print() const override;

		void AddScore(int _iPuntos);
		void Heal(int _iCantidad);
	private:
		unsigned int m_uPuntos;
	};
}