/*
CEntity: clase base con lo que comparten jugadores y enemigos (nombre, posición y vida).

CEntity con los miembros protected; la vida no baja de 0.
Los constructores llaman al de CEntity. Con un printf en constructores y destructores: ¿en qué orden salen?

- Primero CEntity y luego el hijo que sea (CEnemy o CPlayer). Al destruir sale al revés: primero el hijo y
	luego CEntity.

¿Qué deja de compilar si los miembros de CEntity son private?

- Todo lo que use esos miembros desde las clases hijas: AddScore() y Heal() en CPlayer (usan m_pszNombre y
	m_uVida) y Attack() en CEnemy (usa m_pszNombre).
*/
#pragma once
namespace Practica13
{
	// Herencia: CEntity es la clase "general" y CPlayer y CEnemy son versiones más concretas que reciben
	// todo lo suyo sin reescribirlo (ver CEnemy13.h)
	class CEntity
	{
	public:
		CEntity(const char* _pszNombre, int _iX, int _iY, unsigned int _uVida);
		~CEntity();
		void Move(int _iNuevaX, int _iNuevaY); // Coloca la entidad en esa posición (no suma, la sustituye)
		void TakeDamage(int _iDamage);
		bool IsAlive() const; // "const" al final: promete que la función no modifica el objeto, solo lo lee
		void Print() const;
	protected:
		// protected: lo ven CEntity y sus hijas (CPlayer, CEnemy), pero no el código de fuera (como main)
		const char* const m_pszNombre; // Guarda la dirección donde empieza el texto, no una copia del texto. Es no dueño (apunta a
		// literales)
		int m_iX;
		int m_iY;
		unsigned int m_uVida; // unsigned: nunca es negativo
	};
}