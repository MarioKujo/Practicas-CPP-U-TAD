#include "TList11.h"
#include <cstdio>
#include <iostream>
int main()
{
	Practica11::TList oNumeros;
	const char* numeros[] =
	{
	"uno",
	"dos",
	"tres",
	"cuatro",
	"cinco",
	"seis",
	"siete",
	"ocho",
	"nueve",
	"diez"
	};
	for (int i = 0; i < 10; i++)
	{
		oNumeros.Push(numeros[i]);
	}
	printf("Numeros leidos (%d):\n", oNumeros.Size());
	for (const char* pszNumero = oNumeros.First(); pszNumero != nullptr; pszNumero = oNumeros.Next())
	{
		printf("%s\n", pszNumero);
	}

	printf("\n");

	// Constructor de copia
	Practica11::TList oNumeros2(oNumeros);
	printf("Numeros leidos (copia) (%d):\n", oNumeros2.Size());
	for (const char* pszNumero = oNumeros2.First(); pszNumero != nullptr; pszNumero = oNumeros2.Next())
	{
		printf("%s\n", pszNumero);
	}

	printf("\n");

	// Lista invertida (GetReverseList se encuentra sola porque su parámetro es de tipo Practica11::TList)
	Practica11::TList oNumeros3(GetReverseList(oNumeros));
	printf("Numeros leidos (invertido) (%d):\n", oNumeros3.Size());
	for (const char* pszNumero = oNumeros3.First(); pszNumero != nullptr; pszNumero = oNumeros3.Next())
	{
		printf("%s\n", pszNumero);
	}

	printf("\n");

	// operator=: oNumeros4 ya existe (vacía) y se rellena con una copia de oNumeros3
	Practica11::TList oNumeros4;
	oNumeros4 = oNumeros3;
	printf("Numeros leidos (operator=) (%d):\n", oNumeros4.Size());
	for (const char* pszNumero = oNumeros4.First(); pszNumero != nullptr; pszNumero = oNumeros4.Next())
	{
		printf("%s\n", pszNumero);
	}
	return 0;
}