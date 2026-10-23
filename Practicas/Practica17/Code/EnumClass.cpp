#include "EnumClass.h"
#include <cstring>

const char* s_tColorNames[] = {
	"Rojo",
	"Azul",
	"Verde",
	"Amarillo" };

const char* CEnum::AsStr(EColor _eEnum)
{
	unsigned int uIndex = static_cast<unsigned int>(_eEnum); // Técnicamente un enum es un número por debajo, así que...
	if (uIndex < sizeof(s_tColorNames) / sizeof(s_tColorNames[0]))
	{
		return s_tColorNames[uIndex];
	}
	return "Invalido";
}

EColor CEnum::AsEnum(const char* _sEnum)
{
	if (_sEnum != nullptr)
	{
		for (size_t i = 0; i < sizeof(s_tColorNames) / sizeof(s_tColorNames[0]);i++)
		{
			if (strcmp(_sEnum, s_tColorNames[i]) == 0)
			{
				return static_cast<EColor>(i);
			}
		}
	}
	return EColor::Invalido;
}
