#include "TVector2.h"

// Aquí no hay nada nuevo salvo los operadores. Lo único que conviene entender es cómo se apoyan unos en otros:
// los operadores + - * se escriben usando += -= *=, así la lógica de cada cuenta está en un solo sitio

TVector2::TVector2(float _fX, float _fY) : x(_fX), y(_fY) // Lista de inicialización: da valor a x e y al crearlo
{
}

TVector2& TVector2::operator+=(const TVector2& _vOther)
{
	x += _vOther.x;
	y += _vOther.y;
	return *this; // *this es el propio vector. Se devuelve una referencia (no una copia) para poder encadenar
}

TVector2& TVector2::operator-=(const TVector2& _vOther)
{
	x -= _vOther.x;
	y -= _vOther.y;
	return *this;
}

TVector2& TVector2::operator*=(float _fValue)
{
	x *= _fValue;
	y *= _fValue;
	return *this;
}

// _v1 llega por valor, es decir, ya es una COPIA del vector original. Se la modifica con += y se devuelve,
// y así el original no se toca (vSuma = vA + vB no cambia vA)
TVector2 operator+(TVector2 _v1, const TVector2& _v2)
{
	return _v1 += _v2;
}

TVector2 operator-(TVector2 _v1, const TVector2& _v2)
{
	return _v1 -= _v2;
}

// Cambiar el signo no modifica el original, así que se crea un vector nuevo.
// Lo que hay entre {} son los parámetros del constructor TVector2(float _fX, float _fY)
TVector2 operator-(const TVector2& _v1)
{
	return { -_v1.x, -_v1.y };
}

TVector2 operator*(TVector2 _v1, float _fEscalar)
{
	return _v1 *= _fEscalar;
}

// Misma cuenta con los operandos al revés: así funcionan tanto vA * 2.0f como 2.0f * vA
TVector2 operator*(float _fEscalar, TVector2 _v1)
{
	return _v1 *= _fEscalar;
}

std::ostream& operator<<(std::ostream& _os, const TVector2& _v1)
{
	return _os << "(" << _v1.x << ", " << _v1.y << ")";
}

// Dos vectores son iguales si coinciden sus dos componentes
bool operator==(const TVector2& _v1, const TVector2& _v2)
{
	return _v1.x == _v2.x && _v1.y == _v2.y;
}

// Se apoya en == para que la comparación esté escrita en un solo sitio
bool operator!=(const TVector2& _v1, const TVector2& _v2)
{
	return !(_v1 == _v2);
}