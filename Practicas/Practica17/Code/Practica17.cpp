#include <cstdio>
#include "EnumClass.h"
#include "EnumClassMacros.h"
// Función plantilla: una "receta" con huecos para tipos. TClase y TEnum son esos huecos, y al llamarla
// el compilador genera una copia de la función con los tipos reales puestos (una para CEnum y otra para CEnumM).
// Así las pruebas se escriben una sola vez y se aplican a las dos versiones del enumerado.
// _eVerde se pasa de fuera porque cada enumerado tiene su propio tipo (CEnum::EColor, CEnumM::EColorM).
template <typename TClase, typename TEnum>
void RunTests(const char* _pszTitulo, TEnum _eVerde)
{
	printf("--- %s ---\n\n", _pszTitulo);

	TClase oEnum;
	printf("AsStr(Verde) = %s\n", oEnum.AsStr(_eVerde));

	TEnum eLeido = oEnum.AsEnum("Azul");
	// El enum class no se convierte solo a int: static_cast pide el número explícitamente
	printf("AsEnum(\"Azul\") = %d (%s)\n", static_cast<int>(eLeido), oEnum.AsStr(eLeido));

	// Prueba de ida y vuelta: número -> enum -> texto -> enum. Tiene que volver al mismo valor.
	for (int iIndice = 0; iIndice < 3; iIndice++)
	{
		TEnum eColor = static_cast<TEnum>(iIndice);
		const char* pszNombre = oEnum.AsStr(eColor);
		bool bCoincide = (oEnum.AsEnum(pszNombre) == eColor);
		printf("%d -> %s -> %d %s\n", iIndice, pszNombre, static_cast<int>(oEnum.AsEnum(pszNombre)), bCoincide ? "OK" : "FALLO");
	}
	// Casos límite: "Morado" solo existe en la versión con macros (está en COLOR_LIST); una mayúscula distinta,
	// un puntero nulo y un número que no corresponde a ningún valor del enum dan siempre "Invalido"
	printf("AsEnum(\"Morado\") = %s\n", oEnum.AsStr(oEnum.AsEnum("Morado")));
	printf("AsEnum(\"azul\") = %s\n", oEnum.AsStr(oEnum.AsEnum("azul")));
	printf("AsEnum(nullptr) = %s\n", oEnum.AsStr(oEnum.AsEnum(nullptr)));
	printf("AsEnum(fuera de rango) = %s\n\n", oEnum.AsStr(static_cast<TEnum>(99)));
}

int main()
{
	// Entre <> los tipos que ocupan los huecos TClase y TEnum (TEnum también se deduce solo del segundo argumento)
	RunTests<CEnum, CEnum::EColor>("NO MACROS", CEnum::EColor::Verde);
	RunTests<CEnumM, CEnumM::EColorM>("MACROS", CEnumM::EColorM::Verde);
	return 0;
}