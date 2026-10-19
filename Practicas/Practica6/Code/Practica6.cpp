#include "Utils.h"
#include <iostream>
// Probar con texto.txt y numeros.txt: "enemigo" → 3, "Enemigo" → 1, "aa" → 3, "xyz" → 0; la suma es 13245.
int main()
{
	int enemigo1 = Utils::CountOccurrences("texto.txt", "enemigo");
	int enemigo2 = Utils::CountOccurrences("texto.txt", "Enemigo");
	int aa = Utils::CountOccurrences("texto.txt", "aa");
	int xyz = Utils::CountOccurrences("texto.txt", "xyz");
	printf("'enemigo' aparece %d %s\n", enemigo1, enemigo1 == 1 ? "vez" : "veces");
	printf("'Enemigo' aparece %d %s\n", enemigo2, enemigo2 == 1 ? "vez" : "veces");
	printf("'aa' aparece %d %s\n", aa, aa == 1 ? "vez" : "veces");
	printf("'xyz' aparece %d %s\n", xyz, xyz == 1 ? "vez" : "veces");
	int a = 0;
	if (Utils::SumNumbers("numeros.txt", a))
	{
		printf("La suma es %d\n", a);
	}
	return 0;
}