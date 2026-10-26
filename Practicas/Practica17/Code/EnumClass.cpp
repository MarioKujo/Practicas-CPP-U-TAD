#include "EnumClass.h"
#include <cstring>

// Tabla que relaciona cada número del enum con su texto: la posición 0 es Rojo, la 1 es Azul...
// Tiene que estar en el MISMO ORDEN que el enum. "Invalido" no está: se trata aparte.
const char* g_tpszNombresColor[] =
{
	"Rojo",
	"Azul",
	"Verde",
	"Amarillo"
};

const char* CEnum::AsStr(EColor _eColor)
{
	// Convertimos el enum a su número para usarlo como posición en la tabla
	unsigned int uIndice = static_cast<unsigned int>(_eColor);
	// Nº de elementos de la tabla = bytes totales de la tabla / bytes de un elemento
	const size_t uNumNombres = sizeof(g_tpszNombresColor) / sizeof(g_tpszNombresColor[0]);
	if (uIndice < uNumNombres) // Comprobamos que el índice existe antes de leer la tabla
	{
		return g_tpszNombresColor[uIndice];
	}
	return "Invalido"; // Para EColor::Invalido o cualquier número fuera de rango
}

CEnum::EColor CEnum::AsEnum(const char* _pszNombre)
{
	if (_pszNombre != nullptr) // Un puntero nulo no apunta a ningún texto: no se puede comparar
	{
		const size_t uNumNombres = sizeof(g_tpszNombresColor) / sizeof(g_tpszNombresColor[0]);
		for (size_t uIndice = 0; uIndice < uNumNombres; uIndice++)
		{
			// strcmp compara dos textos y devuelve 0 si son exactamente iguales (distingue mayúsculas: "azul" !=
			// "Azul").
			// No se puede usar == porque compararía direcciones de memoria, no el contenido del texto.
			if (strcmp(_pszNombre, g_tpszNombresColor[uIndice]) == 0)
			{
				return static_cast<EColor>(uIndice); // El número de la posición es el valor del enum
			}
		}
	}
	return EColor::Invalido;
}