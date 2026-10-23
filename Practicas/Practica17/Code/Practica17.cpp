#include <cstdio>
#include "EnumClass.h"

int main()
{
	CEnum cEnum;
	printf("AsStr(Verde) = %s\n", cEnum.AsStr(EColor::Verde));

	EColor eLeido = cEnum.AsEnum("Azul");
	printf("AsEnum(\"Azul\") = %d (%s)\n", static_cast<int>(eLeido), cEnum.AsStr(eLeido));

	for (int i = 0; i < 3; i++)
	{
		EColor e = static_cast<EColor>(i);
		const char* sNombre = cEnum.AsStr(e);
		bool bCoincide = (cEnum.AsEnum(sNombre) == e);
		printf("%d -> %s -> %d %s\n", i, sNombre, static_cast<int>(cEnum.AsEnum(sNombre)), bCoincide ? "OK" : "FALLO");
	}
	printf("AsEnum(\"Morado\") = %s\n", cEnum.AsStr(cEnum.AsEnum("Morado")));
	printf("AsEnum(\"azul\") = %s\n", cEnum.AsStr(cEnum.AsEnum("azul")));
	printf("AsEnum(nullptr) = %s\n", cEnum.AsStr(cEnum.AsEnum(nullptr)));
	printf("AsEnum(fuera de rango) = %s\n", cEnum.AsStr(static_cast<EColor>(99)));
	return 0;
}