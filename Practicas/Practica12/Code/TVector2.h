/*
▸ TVector2 con float x, y públicos; TVector2() deja (0, 0) y TVector2(x, y).
▸ Métodos: +=, -= y *= (por un float). Retornan TVector2&.
▸ No miembro: + y - entre vectores, * con float en los dos órdenes, - unario, == y !=; operator<<.

▸ Pista: implementar + con +=. ¿Por qué 2.0f * v no puede ser método?

- 2.0f * v no puede ser un método: un método se llama sobre el operando de la IZQUIERDA (2.0f.operator*(v)),
y un float no es una clase, no tiene métodos ni se pueden añadir. Por eso tiene que ser una función suelta

▸ Además: añadir operator= a la TList de la práctica 11 (regla de tres).
*/
#pragma once
#include <iostream>

// Sobrecargar un operador es darle significado a +, -, *, == ... para nuestra propia clase.
// Así, en vez de vC = Sumar(vA, vB) se puede escribir vC = vA + vB. Un operador es una función normal
// con un nombre especial: "operator+", "operator==", etc.
class TVector2
{
public:
	float x;
	float y;

	// Con los valores por defecto (= 0.0f) este único constructor cubre dos casos:
	// TVector2() deja (0, 0) y TVector2(2.0f, 3.0f) deja (2, 3)
	TVector2(float _fX = 0.0f, float _fY = 0.0f);

	// Los operadores compuestos modifican el propio vector, por eso son métodos (el vector de la izquierda
	// es "this"). Devuelven una referencia a sí mismo para poder encadenarlos: vA += vB += vC;
	TVector2& operator+=(const TVector2& _vOther);
	TVector2& operator-=(const TVector2& _vOther);
	TVector2& operator*=(float _fValue);
};

// Estos NO son métodos: son funciones sueltas. Reciben los dos operandos como parámetros.
// Se pasa por valor el primer vector porque la función trabaja sobre una COPIA suya (ver el .cpp)
TVector2 operator+(TVector2 _v1, const TVector2& _v2);
TVector2 operator-(TVector2 _v1, const TVector2& _v2);
TVector2 operator-(const TVector2& _v1); // Unario: -vA (solo un operando, cambia el signo)

// Tiene que haber dos versiones de * (vector * float y float * vector).
TVector2 operator*(TVector2 _v1, float _fEscalar);
TVector2 operator*(float _fEscalar, TVector2 _v1);

// Permite escribir std::cout << vA. Recibe y devuelve el flujo (_os) para poder encadenar: cout << vA << vB
std::ostream& operator<<(std::ostream& _os, const TVector2& _v1);

bool operator==(const TVector2& _v1, const TVector2& _v2);
bool operator!=(const TVector2& _v1, const TVector2& _v2);