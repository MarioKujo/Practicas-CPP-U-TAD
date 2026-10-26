#include "Utils06.h"
#include <cstdio>
// Probar con texto.txt y numeros.txt: "enemigo" → 3, "Enemigo" → 1, "aa" → 3, "xyz" → 0; la suma es 13245.
int main()
{
	const char* const apszTextos[] =
	{
		"enemigo", "Enemigo", "aa", "xyz"
	}; // Array de cadenas a buscar
	for (const char* pszTexto : apszTextos) // Recorre el array de uno en uno
	{
		printf("'%s' aparece %d veces\n", pszTexto, CountOccurrences("texto.txt", pszTexto));
	}
	int iSuma = 0;
	if (SumNumbers("numeros.txt", iSuma)) // SumNumbers escribe el resultado en iSuma
	{
		printf("La suma es %d\n", iSuma);
	}
	return 0;
}