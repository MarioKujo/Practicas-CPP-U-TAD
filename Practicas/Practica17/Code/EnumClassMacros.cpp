#include "EnumClassMacros.h"
#include <cstring>

// El operador # convierte el nombre en texto entre comillas: AS_STRING(Rojo) se convierte en "Rojo",
#define AS_STRING(name) #name,

// Misma tabla que en la versión sin macros, pero sale de la misma COLOR_LIST que el enum, así que siempre
// coinciden en orden y cantidad. "Invalido" se añade a mano porque en el enum también va el último
static const char* const g_apszNombresColorM[] =
{
	COLOR_LIST(AS_STRING) // Se expande a "Rojo", "Azul", "Verde", "Amarillo", "Morado",
	"Invalido"
};

#undef AS_STRING

static constexpr size_t g_nNombresColorM = sizeof(g_apszNombresColorM) / sizeof(g_apszNombresColorM[0]);
// AsStr y AsEnum son idénticas a las de CEnum (ver EnumClass.cpp). Aquí "Invalido" sí está en la tabla,
// así que AsEnum("Invalido") lo encuentra en vez de caer en el return final
const char* CEnumM::AsStr(EColorM _eColor)
{
	unsigned int uIndice = static_cast<unsigned int>(_eColor);
	const size_t nNombres = g_nNombresColorM;
	if (uIndice < nNombres)
	{
		return g_apszNombresColorM[uIndice];
	}
	return "Invalido";
}

CEnumM::EColorM CEnumM::AsEnum(const char* _pszNombre)
{
	if (_pszNombre != nullptr)
	{
		const size_t nNombres = g_nNombresColorM;
		for (size_t nIndice = 0; nIndice < nNombres; nIndice++)
		{
			if (strcmp(_pszNombre, g_apszNombresColorM[nIndice]) == 0)
			{
				return static_cast<EColorM>(nIndice);
			}
		}
	}
	return EColorM::Invalido;
}