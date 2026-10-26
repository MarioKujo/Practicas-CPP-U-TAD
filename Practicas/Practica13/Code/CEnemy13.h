/*
CEnemy empieza con 30 de vida y su propio daño.
Attack recibe un CEntity&: sirve para atacar a un CPlayer o a otro CEnemy.
- daño
*/
#pragma once
#include "CEntity13.h"
namespace Practica13
{
	// ": public CEntity" significa que CEnemy hereda de CEntity: tiene sus miembros protected (m_pszNombre,
	// m_iX, m_iY, m_uVida) y sus funciones públicas (Move, TakeDamage, IsAlive, Print) sin escribirlos otra vez.
	// Solo hay que añadir lo que es propio de un enemigo
	class CEnemy : public CEntity
	{
	public:
		// El valor por defecto de _uVida (30) solo se escribe aquí, en el .h
		CEnemy(const char* _pszNombre, int _iX, int _iY, int _iDamage, unsigned int _uVida = 30);
		~CEnemy();
		void Attack(CEntity& _oObjetivo) const; // "&": referencia, es el objeto original y no una copia
	private:
		const int m_iDamage; // Daño que hace este enemigo en cada ataque
	};
}