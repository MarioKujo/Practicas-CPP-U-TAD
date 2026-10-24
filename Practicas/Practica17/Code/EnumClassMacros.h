/*
2 Mediante macros, generalizar el código anterior para que sea más
fácil crear enumerados con esa funcionalidad.
*/
#pragma once

// Es una macro que recibe otra macro como parámetro (x) y la llama una vez por cada color. Sólo dice "aplica X a Rojo, a Azul, a
// Verde y a Amarillo"

#define COLOR_LIST(X) \
X(Rojo)               \
X(Azul)               \
X(Verde)              \
X(Amarillo)           \
X(Morado)

// Dado un nombre, lo deja seguido de una coma. AS_ENUMERATOR(Rojo) se convierte en "Rojo, " (sin comillas)

#define AS_ENUMERATOR(name) name,

// AS_ENUMERATOR es una línea aislada, no incluye el enum class de debajo ni lo modifica

enum class EColorM
{
	// Se expande a AS_ENUMERATOR(Rojo) AS_ENUMERATOR(Azul) AS_ENUMERATOR(Verde) AS_ENUMERATOR(Amarillo), como decíamos, sustituye la X donde la otra macro

	COLOR_LIST(AS_ENUMERATOR)

	Invalido
};
// Borra la macro auxiliar para que no contamine el resto del código y para poder definirlo otra vez con otro significado
#undef AS_ENUMERATOR

class CEnumM
{
public:
	const char* AsStr(EColorM _eEnum);
	EColorM AsEnum(const char* _sEnum);
};