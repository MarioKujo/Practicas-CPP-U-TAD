/*
CPlayer empieza con 100 de vida y tiene Heal(iAmount) (máximo 100);
Los constructores llaman al de CEntity. Con un printf en constructores y destructores: ¿en qué orden salen?
- puntos
AddScore() Heal()
*/
#pragma once
#include "CEntity13.h"
#include <iostream>
namespace Practica13
{
	class CPlayer :public CEntity
	{
	public:
		CPlayer(const char* _nombre, int _iX, int _iY, unsigned int _uVida = 100);
		~CPlayer();
		void AddScore(int _puntos);
		void Heal(int _iAmount);
	private:
		unsigned int puntos;
	};
}