/*
CPlayer empieza con 100 de vida y tiene Heal(iAmount) (máximo 100);
Los constructores llaman al de CEntity. Con un printf en constructores y destructores: ¿en qué orden salen?
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
		CPlayer(const char* _nombre, int _iX, int _iY, unsigned int _uVida = 100);
		virtual ~CPlayer() override; // <-- virtual no hace falta aquí, con solo poner override es suficiente, pero el
		// profe recomienda ponerlo. Además, override es sólo en el .h, en el .cpp hay que tratarlo como una función
		// normal
		virtual void Update() override;
		virtual void Print() const override;
		void AddScore(int _puntos);
		void Heal(int _iAmount);
	private:
		unsigned int puntos;
	};
}