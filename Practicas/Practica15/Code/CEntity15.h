/*
Update() virtual en CEntity; Print() también virtual. Cada derivada los redefine con override.

Mismas convenciones de nombres que en la práctica 13 (m_ = miembro, _ = parámetro). Prefijos nuevos: p = puntero,
a = array.
*/
#pragma once
#include <iostream>
namespace Practica15
{
	// Es la CEntity de la práctica 13, pero ahora con funciones virtuales para que cada hija se comporte a su manera
	// aunque se use a través de un CEntity* (ver práctica 14 para saber cómo funciona por dentro)
	class CEntity
	{
	public:
		CEntity(const char* _pszNombre, int _iX, int _iY, unsigned int _uVida);

		// virtual: sin él, delete a través de un CEntity* solo ejecutaría este destructor y no el de la hija
		virtual ~CEntity();

		// "= 0": virtual pura. No tiene cuerpo y cada hija está obligada a escribir la suya,
		// así que no se pueden crear objetos de CEntity directamente (es abstracta)
		virtual void Update() = 0;
		virtual void Print() const = 0;

		// Estas no son virtuales: todas las hijas las usan tal cual
		void Move(int _iNuevaX, int _iNuevaY); // Coloca la entidad en esa posición (no suma, la sustituye)
		void TakeDamage(int _iDamage);
		bool IsAlive() const;
	protected:
		const char* const m_pszNombre;
		int m_iX;
		int m_iY;
		unsigned int m_uVida;
	};
}