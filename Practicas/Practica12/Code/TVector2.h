/*
▸ TVector2 con float x, y públicos; TVector2() deja (0, 0) y TVector2(x, y).
▸ Métodos: +=, -= y *= (por un float). Retornan TVector2&.
▸ No miembro: + y - entre vectores, * con float en los dos órdenes, - unario, == y !=; operator<<.
▸ Pista: implementar + con +=. ¿Por qué 2.0f * v no puede ser método?
▸ Además: añadir operator= a la TList de la práctica 11 (regla de tres).
*/
#pragma once
#include <iostream>

class TVector2
{
public:
	float x;
	float y;

	TVector2(float _fX = 0.0f, float _fY = 0.0f);

	TVector2& operator+=(const TVector2& _other);
	TVector2& operator-=(const TVector2& _other);
	TVector2& operator*=(float fValue);
};

TVector2 operator+(TVector2 _v1, const TVector2& _v2);
TVector2 operator-(TVector2 _v1, const TVector2& _v2);
TVector2 operator-(const TVector2& _v1);
TVector2 operator*(TVector2 _v1, float _f1);
TVector2 operator*(float _f1, TVector2 _v1);
std::ostream& operator<<(std::ostream& os, const TVector2& _v1);
bool operator==(const TVector2& _v1, const TVector2& _v2);
bool operator!=(const TVector2& _v1, const TVector2& _v2);