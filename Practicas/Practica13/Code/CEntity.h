/*
* # nombre, x, y, vida
Move(iDX, iDY)
TakeDamage(iDamage)
IsAlive() Print()
▸ CEntity con los miembros protected; la vida no baja de 0.
Los constructores llaman al de CEntity. Con un printf en constructores y destructores: ¿en qué orden salen?

Primero CEntity y luego el hijo que sea (CEnemy o CPlayer)

¿Qué deja de compilar si los miembros de CEntity son private?

De CPlayer: AddScore() y Heal(), de CEnemy Attack(), es decir, cualquier mención a los artributos privados de la clase (nombre, iX, iY, uVida)
*/
#pragma once
#include <iostream>
class CEntityVirtual
{
public:
	CEntityVirtual(const char* _nombre, int _iX, int _iY, unsigned int _uVida);
	~CEntityVirtual();
	void Move(int iDX, int iDY);
	void TakeDamage(int iDamage);
	bool IsAlive() const;
	void Print() const;
protected:
	const char* nombre;
	int iX;
	int iY;
	unsigned int uVida;
};