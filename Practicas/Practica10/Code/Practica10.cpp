#include "Utils10.h"
#include "TList09.h"
#include <iostream>
int main()
{
	Practica09::TList lNumeros;
	if (Utils::ReadNumbers("numeros.txt", lNumeros))
	{
		printf("Numeros leidos (%d):\n", lNumeros.Size());
		for (const char* p = lNumeros.First(); p != nullptr; p = lNumeros.Next())
		{
			printf("%s\n", p);
		}
	}
	else
	{
		fprintf(stderr, "Error: no se ha podido abrir numeros.txt\n");
	}

	return 0;
}