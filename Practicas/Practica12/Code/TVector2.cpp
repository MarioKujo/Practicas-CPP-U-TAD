#include "TVector2.h"

// Creo que no es necesario comentar nada, todo se entiende muy fácil

TVector2::TVector2(float _fX, float _fY):x(_fX), y(_fY)
{
}

TVector2& TVector2::operator+=(const TVector2& _other)
{
	x += _other.x;
	y += _other.y;
	return *this;
}

TVector2& TVector2::operator-=(const TVector2& _other)
{
	x -= _other.x;
	y -= _other.y;
	return *this;
}

TVector2& TVector2::operator*=(float fValue)
{
	x *= fValue;
	y *= fValue;
	return *this;
}

TVector2 operator+(TVector2 _v1, const TVector2& _v2)
{
	return _v1 += _v2;
}

TVector2 operator-(TVector2 _v1, const TVector2& _v2)
{
	return _v1 -= _v2;
}

TVector2 operator-(const TVector2& _v1)
{
	return { -_v1.x, -_v1.y }; // En estos casos, lo que hay entre {} son los parámetros del constructor (porque
	// TVector2 recibe (float x, float y)
}

TVector2 operator*(TVector2 _v1, float _f1)
{
	return _v1 *= _f1;
}

TVector2 operator*(float _f1, TVector2 _v1)
{
	return _v1 *= _f1;
}

std::ostream& operator<<(std::ostream& os, const TVector2& _v1)
{
	return os << "(" << _v1.x << ", " << _v1.y << ")";
}

bool operator==(const TVector2& _v1, const TVector2& _v2)
{
	return _v1.x == _v2.x && _v1.y == _v2.y;
}

bool operator!=(const TVector2& _v1, const TVector2& _v2)
{
	return !(_v1 == _v2);
}
