#include "File.h"
#include <cstdio>
#include <cstring>
#include "Utils.h"
#include "TList.h"
#include <iostream>
int main()
{
	// File
	
	// --- Escritura ---
	void* archivo = File::FileOpen("Prueba.bin", File::EFileMode::FILE_WRITE);
	if (archivo == nullptr)
	{
		fprintf(stderr, "Error: no se ha podido abrir el archivo.\n");
		return 1;
	}
	printf("Archivo abierto en modo de escritura.\n");

	const char* numeros = "1 2 3 4 5 6 7 8 9 10";
	unsigned int pedidos = static_cast<unsigned int>(strlen(numeros));
	unsigned int escritos = File::FileWrite(archivo, numeros, pedidos);
	if (pedidos != escritos)
	{
		fprintf(stderr, "Error: se escribieron %u de %u bytes\n", escritos, pedidos);
		File::FileClose(archivo);
		return 1;
	}
	printf("Correcto! Se escribieron %u de %u bytes\n", escritos, pedidos);

	if (!File::FileClose(archivo))
	{
		fprintf(stderr, "Error: no se ha cerrado el archivo.\n");
		return 1;
	}
	printf("Cerrado correctamente.\n\n");

	// --- Lectura ---
	archivo = File::FileOpen("Prueba.bin", File::EFileMode::FILE_READ);
	if (archivo == nullptr)
	{
		fprintf(stderr, "Error: no se ha podido abrir el archivo.\n");
		return 1;
	}
	printf("Archivo abierto en modo de lectura.\n");

	char buffer[128];
	unsigned int leidos = File::FileRead(archivo, buffer, static_cast<unsigned int>(sizeof(buffer) - 1));
	if (leidos != pedidos)
	{
		fprintf(stderr, "Error: se leyeron %u de %u bytes\n", leidos, pedidos);
		File::FileClose(archivo);
		return 1;
	}
	buffer[leidos] = '\0';
	printf("Leidos: %s\n", buffer);
	File::FileClose(archivo);
	printf("Cerrado correctamente.\n\n");

	// --- Archivo inexistente ---
	if (File::FileOpen("Error.bin", File::EFileMode::FILE_READ) == nullptr)
	{
		printf("Correcto: el archivo inexistente 'Error.bin' devuelve nullptr.\n");
	}

	// Utils

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

	// TList
	/*
	Práctica 10:
	2 Sacar por consola los números leídos.
	*/
	TList lNumeros;
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