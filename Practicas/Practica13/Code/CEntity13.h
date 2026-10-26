/*
Práctica 13 - Herencia
CEntity: clase base con lo que comparten jugadores y enemigos (nombre, posición y vida).

CEntity con los miembros protected; la vida no baja de 0.
Los constructores llaman al de CEntity. Con un printf en constructores y destructores: ¿en qué orden salen?

- Primero CEntity y luego el hijo que sea (CEnemy o CPlayer)

¿Qué deja de compilar si los miembros de CEntity son private?

- De CPlayer: AddScore() y Heal(); de CEnemy: Attack(). Es decir, cualquier mención en las
  clases hijas a los atributos (pszNombre, iX, iY, uVida), que dejarían de ser accesibles.
*/
#pragma once
#include <iostream>
namespace Practica13
{
	class CEntity
	{
	public:
		CEntity(const char* _pszNombre, int _iX, int _iY, unsigned int _uVida);
		~CEntity();
		void Move(int _iDX, int _iDY);
		void TakeDamage(int _iDamage);
		bool IsAlive() const; // "const" al final: promete que esta función no modifica el objeto, solo lo lee
		void Print() const;
	protected:
		// protected: accesible desde CEntity y sus clases hijas (CPlayer, CEnemy), pero no desde main
		const char* pszNombre; // Puntero: guarda la dirección de memoria donde empieza el texto, no una copia del texto
		int iX;
		int iY;
		unsigned int uVida; // unsigned: nunca es negativo
	};
}