/*
CPlayer empieza con 100 de vida y tiene Heal(iAmount) (máximo 100);
- puntos
AddScore() Heal()
*/
#pragma once
#include "CEntity13.h"
namespace Practica13
{
	// Hereda de CEntity igual que CEnemy (ver CEnemy13.h para la explicación)
	class CPlayer : public CEntity
	{
	public:
		// El valor por defecto de _uVida (100) solo se escribe aquí, en el .h
		CPlayer(const char* _pszNombre, int _iX, int _iY, unsigned int _uVida = 100);
		~CPlayer();
		void AddScore(int _iPuntos);
		void Heal(int _iCantidad);
	private:
		unsigned int m_uPuntos; // Puntuación del jugador
	};
}