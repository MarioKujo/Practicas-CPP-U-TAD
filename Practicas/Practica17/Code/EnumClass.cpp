#include "EnumClass.h"
#include <cstring>

// Relaciona cada número del enum con su texto: la posición 0 es Rojo, la 1 es Azul...
// Tiene que estar en el MISMO ORDEN que el enum. "Invalido" no está: se trata aparte.
// (Es la versión "a mano": si se añade un color hay que tocarlo aquí Y en el enum. La versión con macros evita eso)
static const char* const g_apszNombresColor[] =
{
	"Rojo",
	"Azul",
	"Verde",
	"Amarillo"
};
static constexpr size_t g_nNombresColor = sizeof(g_apszNombresColor) / sizeof(g_apszNombresColor[0]);

const char* CEnum::AsStr(EColor _eColor)
{
	// El número del enum se usa como posición en la tabla
	unsigned int uIndice = static_cast<unsigned int>(_eColor);
	// Elementos de la tabla = bytes totales / bytes de un elemento (ver práctica 4)
	const size_t nNombres = g_nNombresColor;
	if (uIndice < nNombres) // Se comprueba antes de leer la tabla, para no salirse de ella
	{
		return g_apszNombresColor[uIndice];
	}
	return "Invalido"; // Para EColor::Invalido o cualquier número fuera de rango
}

CEnum::EColor CEnum::AsEnum(const char* _pszNombre)
{
	if (_pszNombre != nullptr) // Un puntero nulo no apunta a ningún texto: no se puede comparar
	{
		const size_t nNombres = g_nNombresColor;
		for (size_t nIndice = 0; nIndice < nNombres; nIndice++)
		{
			// strcmp compara el CONTENIDO de dos textos y devuelve 0 si son idénticos (distingue mayúsculas:
			// "azul" != "Azul"). Con == se compararían las direcciones de memoria, no los textos
			if (strcmp(_pszNombre, g_apszNombresColor[nIndice]) == 0)
			{
				return static_cast<EColor>(nIndice); // La posición en la tabla es el valor del enum
			}
		}
	}
	return EColor::Invalido; // Puntero nulo o texto que no está en la tabla
}