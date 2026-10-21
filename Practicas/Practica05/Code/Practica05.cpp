#include "File05.h"
#include <cstdio>
#include <cstring>

int main()
{
	// --- Escritura ---
	void* archivo = FileOpen("Prueba.bin", EFileMode::FILE_WRITE);
	if (archivo == nullptr)
	{
		fprintf(stderr, "Error: no se ha podido abrir el archivo.\n");
		return 1;
	}
	printf("Archivo abierto en modo de escritura.\n");

	const char* numeros = "1 2 3 4 5 6 7 8 9 10";
	unsigned int pedidos = static_cast<unsigned int>(strlen(numeros));
	unsigned int escritos = FileWrite(archivo, numeros, pedidos);
	if (pedidos != escritos)
	{
		fprintf(stderr, "Error: se escribieron %u de %u bytes\n", escritos, pedidos);
		FileClose(archivo);
		return 1;
	}
	printf("Correcto! Se escribieron %u de %u bytes\n", escritos, pedidos);

	if (!FileClose(archivo))
	{
		fprintf(stderr, "Error: no se ha cerrado el archivo.\n");
		return 1;
	}
	printf("Cerrado correctamente.\n\n");

	// --- Lectura ---
	archivo = FileOpen("Prueba.bin", EFileMode::FILE_READ);
	if (archivo == nullptr)
	{
		fprintf(stderr, "Error: no se ha podido abrir el archivo.\n");
		return 1;
	}
	printf("Archivo abierto en modo de lectura.\n");

	char buffer[128];
	unsigned int leidos = FileRead(archivo, buffer, static_cast<unsigned int>(sizeof(buffer) - 1));
	if (leidos != pedidos)
	{
		fprintf(stderr, "Error: se leyeron %u de %u bytes\n", leidos, pedidos);
		FileClose(archivo);
		return 1;
	}
	buffer[leidos] = '\0';
	printf("Leidos: %s\n", buffer);
	FileClose(archivo);
	printf("Cerrado correctamente.\n\n");

	// --- Archivo inexistente ---
	if (FileOpen("Error.bin", EFileMode::FILE_READ) == nullptr)
	{
		printf("Correcto: el archivo inexistente 'Error.bin' devuelve nullptr.\n");
	}
	return 0;
}