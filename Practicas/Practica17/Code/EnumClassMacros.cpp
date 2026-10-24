#include "EnumClassMacros.h"
#include <cstring>
// Línea de código huérfana, igual que AS_ENUMERATOR en el .h
// #name, deja AS_STRING(Rojo) como "Rojo, " (ahora sí con comillas, porque # lo transforma en cadena)
#define AS_STRING(name) #name,

const char* s_tColorNamesM[] =
{
	//AS_STRING(Rojo) AS_STRING(Azul) AS_STRING(Verde) AS_STRING(Amarillo)
	COLOR_LIST(AS_STRING)
	"Invalido"
};
// Borra la macro auxiliar para que no contamine el resto del código y para poder definirlo otra vez con otro significado
#undef AS_STRING

const char* CEnumM::AsStr(EColorM _eEnum)
{
	unsigned int uIndex = static_cast<unsigned int>(_eEnum); // Técnicamente un enum es un número por debajo, así que...
	if (uIndex < sizeof(s_tColorNamesM) / sizeof(s_tColorNamesM[0]))
	{
		return s_tColorNamesM[uIndex];
	}
	return "Invalido";
}

EColorM CEnumM::AsEnum(const char* _sEnum)
{
	if (_sEnum != nullptr)
	{
		for (size_t i = 0; i < sizeof(s_tColorNamesM) / sizeof(s_tColorNamesM[0]);i++)
		{
			if (strcmp(_sEnum, s_tColorNamesM[i]) == 0)
			{
				return static_cast<EColorM>(i);
			}
		}
	}
	return EColorM::Invalido;
}
