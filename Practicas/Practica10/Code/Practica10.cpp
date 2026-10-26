#include "Utils10.h"
#include "TList09.h"
#include <cstdio>
#include <iostream>

int main()
{
	Practica09::TList oNumeros;
	if (Utils::ReadNumbers("numeros.txt", oNumeros)) // ReadNumbers rellena oNumeros
	{
		printf("Numeros leidos (%d):\n", oNumeros.Size());
		// Recorre la lista: First() da el primero y Next() el siguiente, hasta que devuelve nullptr
		for (const char* pszNumero = oNumeros.First(); pszNumero != nullptr; pszNumero = oNumeros.Next())
		{
			printf("%s\n", pszNumero);
		}
	}
	else
	{
		fprintf(stderr, "Error: no se ha podido abrir numeros.txt\n");
	}

	return 0;
}