#include "Utils06.h"
#include <iostream>
// Probar con texto.txt y numeros.txt: "enemigo" → 3, "Enemigo" → 1, "aa" → 3, "xyz" → 0; la suma es 13245.
int main()
{
	const char* tests[] = { "enemigo", "Enemigo", "aa", "xyz" };
	for (const char* t : tests)
	{
		printf("'%s' aparece %d veces\n", t, CountOccurrences("texto.txt", t));
	}
	int iSum = 0;
	if (SumNumbers("numeros.txt", iSum))
	{
		printf("La suma es %d\n", iSum);
	}
	return 0;
}