#include "TList11.h"
#include <iostream>
int main()
{
	TList lNumeros;
	lNumeros.Push("uno");
	lNumeros.Push("dos");
	lNumeros.Push("tres");
	lNumeros.Push("cuatro");
	lNumeros.Push("cinco");
	lNumeros.Push("seis");
	lNumeros.Push("siete");
	lNumeros.Push("ocho");
	lNumeros.Push("nueve");
	lNumeros.Push("diez");
	printf("Numeros leidos (%d):\n", lNumeros.Size());
	for (const char* p = lNumeros.First(); p != nullptr; p = lNumeros.Next())
	{
		printf("%s\n", p);
	}
	TList lNumeros2(lNumeros);
	printf("Numeros leidos (copia) (%d):\n", lNumeros2.Size());
	for (const char* p = lNumeros2.First(); p != nullptr; p = lNumeros2.Next())
	{
		printf("%s\n", p);
	}
	TList lNumeros3(GetReverseList(lNumeros));
	printf("Numeros leidos (invertido) (%d):\n", lNumeros3.Size());
	for (const char* p = lNumeros3.First(); p != nullptr; p = lNumeros3.Next())
	{
		printf("%s\n", p);
	}
	return 0;
}