/*
a. Una plantilla de función template <typename T> T Clamp(T tValue, T tMin, T tMax) que deje tValue dentro
del rango [tMin, tMax]. Clamp(150, 0, 100) -> 100 y Clamp(-0.5f, 0.0f, 1.0f) -> 0.

b. ¿Por qué no compila Clamp(5, 0.0f, 10)? ¿Cómo se arregla sin cambiar los valores?

 - Porque los tipos son (int, float, int): el compilador deduce T de cada argumento, le salen dos tipos
distintos y no sabe cuál elegir.
 - Se puede arreglar indicando T a mano: Clamp<float>(5, 0.0f, 10), y los int se convierten solos a float.
 - Aquí lo resuelvo con ClampValues(), más abajo: acepta tres tipos distintos y los pasa a su tipo común.

c. Una plantilla de clase template <typename T, int SIZE> class TStack: una pila de tamaño fijo, guardada en
un array T m_aValues[SIZE] (sin new). Métodos: bool Push(const T& tValue) (false si está llena),
bool Pop(T& tValue_) (false si está vacía), int Size() const y bool IsEmpty() const.

d. Probar la pila con TStack<int, 4> (el quinto Push tiene que fallar, y al vaciarla salen 4 3 2 1) y con
TStack<TVector2, 8>, usando el TVector2 de la práctica 12.

e. Mostrar sizeof(TStack<int, 4>) y sizeof(TStack<int, 100>): ¿por qué son distintos? ¿Son el mismo tipo?

- sizeof(TStack<int, 4>) = 20
- sizeof(TStack<int, 100>) = 404

- El int m_iTop ocupa 4 bytes, y el array T m_aValues se lleva el resto: 4 elementos * 4 bytes = 16 bytes,
y todo junto 16 + 4 = 20.
Con 100 elementos: 100 * 4 bytes = 400 bytes + 4 bytes del int m_iTop = 404.

- No, no son el mismo tipo: cada combinación única de tipo + tamaño es un tipo distinto. TStack<int, 4>,
TStack<int, 5>, TStack<int, 100> y TStack<int, 150> son 4 tipos distintos aunque todos guarden ints.

Prefijo nuevo: t = valor cuyo tipo es el genérico T (no sabemos si será int, float, TVector2...).
*/
#pragma once
#include <type_traits>

/*
Los templates se explican en las prácticas 17 y 19. Lo nuevo aquí: funciones plantilla y un número
(SIZE) como parámetro de plantilla. Como siempre con templates, todo el código va en el .h

Si el valor es menor que el mínimo devuelve el mínimo, si es mayor que el máximo devuelve el máximo,
y si está entre los dos (inclusive) lo devuelve tal cual.
T es un hueco para un tipo que el compilador rellena mirando los argumentos de la llamada. Los tres
deben dar el mismo T, y por eso Clamp(5, 0.0f, 10) no compila
*/

template <typename T>
T Clamp(T _tValue, T _tMin, T _tMax)
{
	if (_tValue < _tMin)
	{
		return _tMin;
	}
	if (_tValue > _tMax)
	{
		return _tMax;
	}
	return _tValue;
}

// Igual que Clamp, pero cada argumento puede tener un tipo distinto (TValue, TMin y TMax son tres huecos).
// "auto" en el retorno deja que el compilador deduzca el tipo que se devuelve
template <typename TValue, typename TMin, typename TMax>
auto ClampValues(TValue _tValue, TMin _tMin, TMax _tMax)
{
	// common_type_t da el tipo al que el lenguaje convertiría los tres en una operación mezclada:
	// de (int, float, int) sale float, y de (int, float, double) sale double.
	// Ojo: "común" no garantiza no perder información (un int muy grande puede perder precisión en un float)
	using TCommon = std::common_type_t<TValue, TMin, TMax>;
	const TCommon tCommonValue = static_cast<TCommon>(_tValue);
	const TCommon tCommonMin = static_cast<TCommon>(_tMin);
	const TCommon tCommonMax = static_cast<TCommon>(_tMax);
	if (tCommonValue < tCommonMin)
	{
		return tCommonMin;
	}
	if (tCommonValue > tCommonMax)
	{
		return tCommonMax;
	}
	return tCommonValue;
}

// Pila: el último elemento que entra es el primero que sale (como una pila de platos).
// Ojo: es la estructura de datos "pila", no la zona de memoria llamada "pila" (stack).
// SIZE es un número que se fija al escribir TStack<int, 4> y forma parte del tipo. Por eso el array tiene
// tamaño fijo, vive dentro del propio objeto y no necesita new (ni destructor: no hay nada que liberar)
template <typename T, int SIZE>
class TStack
{
public:
	TStack() {}

	static_assert(SIZE > 0, "SIZE debe ser positivo");

	bool Push(const T& _tValue)
	{
		if (m_iTop >= SIZE) // Ya está llena
		{
			return false;
		}

		m_aValues[m_iTop] = _tValue; // Se guarda en la primera posición libre
		m_iTop++;

		return true;
	}

	// tValue_ es un parámetro de salida: al ser una referencia, escribe en la variable de quien llama
	// (igual que Pop de la práctica 19)
	bool Pop(T& tValue_)
	{
		if (m_iTop == 0) // No hay nada que sacar
		{
			return false;
		}
		--m_iTop; // Retrocede hasta el último elemento guardado
		tValue_ = m_aValues[m_iTop]; // Se copia fuera
		m_aValues[m_iTop] = T{}; // Se pisa con el valor por defecto (0 en un int) para no dejar el dato antiguo.
		// No es imprescindible: ese hueco ya cuenta como libre y se sobrescribirá en el siguiente Push
		return true;
	}

	int Size() const
	{
		return m_iTop;
	}

	bool IsEmpty() const
	{
		return m_iTop == 0;
	}

private:
	// El array crea SIZE objetos de golpe al construir la pila, así que T necesita un constructor sin
	// argumentos (los tipos básicos y TVector2 lo tienen)
	T m_aValues[SIZE];
	int m_iTop = 0; // Posición de la siguiente casilla libre, que a la vez es cuántos elementos hay
};