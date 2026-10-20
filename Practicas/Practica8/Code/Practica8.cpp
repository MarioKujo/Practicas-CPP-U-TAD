#include "TFile.h"
#include <iostream>

int main()
{
	TFile archivo;
	// --- Escritura ---
	void* pFile = archivo.Open("Prueba.bin", TFileMode::FILE_WRITE);
	if (pFile == nullptr)
	{
		fprintf(stderr, "Error: no se ha podido abrir el archivo.\n");
		return 1;
	}
	printf("Archivo abierto en modo de escritura.\n");

	const char* numeros = "1 2 3 4 5 6 7 8 9 10";
	unsigned int pedidos = static_cast<unsigned int>(strlen(numeros));
	unsigned int escritos = archivo.Write(numeros, pedidos);
	if (pedidos != escritos)
	{
		fprintf(stderr, "Error: se escribieron %u de %u bytes\n", escritos, pedidos);
		return 1;
	}
	printf("Correcto! Se escribieron %u de %u bytes\n", escritos, pedidos);

	if (archivo.Close())
	{
		printf("Cerrado correctamente.\n\n");
	}

	// --- Lectura ---
	pFile = archivo.Open("Prueba.bin", TFileMode::FILE_READ);
	if (pFile == nullptr)
	{
		fprintf(stderr, "Error: no se ha podido abrir el archivo.\n");
		return 1;
	}
	printf("Archivo abierto en modo de lectura.\n");

	char buffer[128];
	unsigned int leidos = archivo.Read(buffer, static_cast<unsigned int>(sizeof(buffer) - 1));
	buffer[leidos] = '\0';
	printf("Leidos: %s\n", buffer);
	if (archivo.Close())
	{
		printf("Cerrado correctamente.\n\n");
	}

	// --- Archivo inexistente ---
	if (archivo.Open("Error.bin", TFileMode::FILE_READ) == nullptr)
	{
		printf("Correcto: el archivo inexistente 'Error.bin' devuelve nullptr.\n\n");
	}

	// --- Doble liberación ---
	TFile archivo2 = archivo;
	printf("Copia hecha. Ahora se destruyen los dos...\n\n");
	return 0;
}