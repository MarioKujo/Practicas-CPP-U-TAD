#include "TFile.h"
#include <iostream>

int main()
{
	TFile archivo;
	// --- Escritura ---
	FILE* pFile = static_cast<FILE*>(archivo.Open("Prueba.bin", TFileMode::FILE_WRITE));
	if (pFile == nullptr)
	{
		fprintf(stderr, "Error: no se ha podido abrir el archivo.\n");
		return 1;
	}
	printf("Archivo abierto en modo de escritura.\n");

	const char* numeros = "1 2 3 4 5 6 7 8 9 10";
	unsigned int pedidos = static_cast<unsigned int>(strlen(numeros));
	unsigned int escritos = File::FileWrite(pFile, numeros, pedidos);
	if (pedidos != escritos)
	{
		fprintf(stderr, "Error: se escribieron %u de %u bytes\n", escritos, pedidos);
		File::FileClose(pFile);
		return 1;
	}
	printf("Correcto! Se escribieron %u de %u bytes\n", escritos, pedidos);

	if (!File::FileClose(pFile))
	{
		fprintf(stderr, "Error: no se ha cerrado el archivo.\n");
		return 1;
	}
	printf("Cerrado correctamente.\n\n");

	// --- Lectura ---
	pFile = File::FileOpen("Prueba.bin", File::EFileMode::FILE_READ);
	if (pFile == nullptr)
	{
		fprintf(stderr, "Error: no se ha podido abrir el archivo.\n");
		return 1;
	}
	printf("Archivo abierto en modo de lectura.\n");

	char buffer[128];
	unsigned int leidos = File::FileRead(pFile, buffer, static_cast<unsigned int>(sizeof(buffer) - 1));
	if (leidos != pedidos)
	{
		fprintf(stderr, "Error: se leyeron %u de %u bytes\n", leidos, pedidos);
		File::FileClose(pFile);
		return 1;
	}
	buffer[leidos] = '\0';
	printf("Leidos: %s\n", buffer);
	File::FileClose(pFile);
	printf("Cerrado correctamente.\n\n");

	// --- Archivo inexistente ---
	if (File::FileOpen("Error.bin", File::EFileMode::FILE_READ) == nullptr)
	{
		printf("Correcto: el archivo inexistente 'Error.bin' devuelve nullptr.\n");
	}
	return 0;
}