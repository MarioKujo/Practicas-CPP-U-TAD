#include "EnumClassMacros.h"
#include <cstring>

// Macro auxiliar: el operador # convierte el nombre en texto entre comillas.
// AS_STRING(Rojo) se convierte en: "Rojo",
#define AS_STRING(name) #name,

// Misma tabla que en la versión sin macros, pero generada desde la misma COLOR_LIST que el enum,
// así que siempre coinciden en orden y cantidad. Aquí "Invalido" sí se añade a mano porque en el enum también va el último.
const char* g_tpszNombresColorM[] =
{
	COLOR_LIST(AS_STRING) // Se expande a "Rojo", "Azul", "Verde", "Amarillo", "Morado",
	"Invalido"
};
#undef AS_STRING

const char* CEnumM::AsStr(EColorM _eColor)
{
	unsigned int uIndice = static_cast<unsigned int>(_eColor);
	const size_t uNumNombres = sizeof(g_tpszNombresColorM) / sizeof(g_tpszNombresColorM[0]);
	if (uIndice < uNumNombres)
	{
		return g_tpszNombresColorM[uIndice];
	}
	return "Invalido";
}

CEnumM::EColorM CEnumM::AsEnum(const char* _pszNombre)
{
	if (_pszNombre != nullptr)
	{
		const size_t uNumNombres = sizeof(g_tpszNombresColorM) / sizeof(g_tpszNombresColorM[0]);
		for (size_t uIndice = 0; uIndice < uNumNombres; uIndice++)
		{
			if (strcmp(_pszNombre, g_tpszNombresColorM[uIndice]) == 0)
			{
				return static_cast<EColorM>(uIndice);
			}
		}
	}
	return EColorM::Invalido;
}