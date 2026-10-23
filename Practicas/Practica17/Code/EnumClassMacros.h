/*
2 Mediante macros, generalizar el código anterior para que sea más
fácil crear enumerados con esa funcionalidad.
*/
#pragma once
#define COLOR_LIST(X) \
X(Rojo)               \
X(Azul)               \
X(Verde)              \
X(Amarillo)

#define AS_ENUMERATOR(name)name,
enum class EColorM
{
	COLOR_LIST(AS_ENUMERATOR)
	Invalido
};
#undef AS_ENUMERATOR

class CEnumM
{
public:
	const char* AsStr(EColorM _eEnum);
	EColorM AsEnum(const char* _sEnum);
};