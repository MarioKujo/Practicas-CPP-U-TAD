#include "EnumClassMacros.h"
#include <cstring>

#define AS_STRING(name)#name,
const char* s_tColorNamesM[] =
{
	COLOR_LIST(AS_STRING)
	"Invalido"
};
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
