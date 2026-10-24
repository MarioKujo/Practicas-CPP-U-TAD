/*
a. Una plantilla de función template <typename T> T Clamp(T tValue,
T tMin, T tMax) que deje tValue dentro del rango [tMin, tMax].
Clamp(150, 0, 100) → 100 y Clamp(-0.5f, 0.0f, 1.0f) → 0.

b. ¿Por qué no compila Clamp(5, 0.0f, 10)? ¿Cómo se arregla sin cambiar
los valores?

- Porque los tipos son (int, float, int). 
- Lo hago más abajo en la función ClampValues(), metiéndole 3 valores distintos a la template y haciendo que la función
sea auto y que reciba cualquiera de los 3 valores que se le pasan

c. Una plantilla de clase template <typename T, int SIZE> class
TStack: una pila de tamaño fijo, guardada en un array T m_aValues[SIZE]
(sin new). Métodos: bool Push(const T& tValue) (false si está llena),
bool Pop(T& tValue_) (false si está vacía), int Size() const y bool
IsEmpty() const.

d. Probar la pila con TStack<int, 4> (el quinto Push tiene que fallar, y al
vaciarla salen 4 3 2 1) y con TStack<TVector2, 8>, usando el TVector2 de
la práctica 12.

e. Mostrar sizeof(TStack<int, 4>) y sizeof(TStack<int, 100>): ¿por
qué son distintos? ¿Son el mismo tipo?

sizeof(TStack<int, 4>) = 20
sizeof(TStack<int, 100>) = 404

int m_top ya son 4 bytes, el resto se lo lleva el T m_aValues (4 elementos * 4 bytes = 16 bytes),
y todo junto (16 + 4 = 20)

100 elementos * 4 bytes = 400 bytes + 4 bytes del int m_top = 404

No, no son el mismo tipo, ya que cada combinación única de tipo + tamaño es un tipo disitnto, entonces TStack<int, 4>,
TStack<int, 5>, TStack<int, 100> y TStack<int, 150> son 4 tipos distintos aunque todos guarden ints

*/
#pragma once
#include <type_traits>

template <typename T>
T Clamp(T tValue, T tMin, T tMax) // Clamp lo único que hace es: si el número es menor que el mínimo, lo iguala al
// mínimo. Si es mayor que el máximo, lo iguala al máximo. Si está entre el mínimo y el máximo (ambos inclusive), se
// queda como está.
{
	if (tValue < tMin)
	{
		return tMin;
	}
	if (tValue > tMax)
	{
		return tMax;
	}
	return tValue;
}

template <typename T1, typename T2, typename T3>
auto ClampValues(T1 t1Value, T2 t2Min, T3 t3Max) // Así le puedes meter un int, un float y un double que te lo saca igual
{
	using CommonType = std::common_type_t<T1, T2, T3>; // Saca el tipo común de los tres (int, float, double) = float
	CommonType val = static_cast<CommonType>(t1Value);
	CommonType min = static_cast<CommonType>(t2Min);
	CommonType max = static_cast<CommonType>(t3Max);
	if (val < min)
	{
		return min;
	}
	if (val > max)
	{
		return max;
	}
	return val;
}

template <typename T, int SIZE>
class TStack // Siempre se revisa hasta donde llega de altura
{
public:
	TStack() : m_top(0) {}

	bool Push(const T& tValue)
	{
		if (m_top >= SIZE) // Si ha llegado al tope, no pueden entrar más
		{
			return false;
		}

		m_aValues[m_top] = tValue;// Como es un array normal y corriente, puede acceder a todo lo que tiene guardado así
		m_top++; // Aumenta en uno porque al hacerle push mete un elemento más

		return true;
	}

	bool Pop(T& tValue_)
	{
		if (m_top == 0) // No hay elementos, no hay nada que eliminar
		{
			return false;
		}
		--m_top; // Decrementamos el índice para llegar al elemento actual
		tValue_ = m_aValues[m_top]; // Extraemos el valor
		m_aValues[m_top] = T{}; // Esto destruye el objeto o resetea el valor, evitando datos residuales o "basura"
		return true;
	}

	int Size() const
	{
		return m_top;
	}

	bool IsEmpty() const
	{
		return m_top == 0;
	}
private:
	T m_aValues[SIZE];
	int m_top = 0; // Marca el siguiente índice en el que entrará un valor (si hay un elemento, m_top = 1)
};