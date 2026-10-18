#include "File.h"
#include <cstdio>
#include <cstring>
int main()
{
	FILE* archivo = static_cast<FILE*>(FileOpen("Prueba.bin", EFileMode::FILE_WRITE));
	if (archivo != nullptr)
	{
		printf("Archivo abierto en modo de escritura.\n\n");
	}
	else
	{
		fprintf(stderr, "Error: no se ha podido abrir el archivo.\n\n");
		return 1;
	}
	const char* numeros = "1 2 3 4 5 6 7 8 9 10";
	unsigned int pedidos = static_cast<unsigned int>(strlen(numeros));
	unsigned int escritos = FileWrite(archivo, numeros, static_cast<unsigned int>(strlen(numeros)));
	if (pedidos != escritos)
	{
		fprintf(stderr, "Error: se escribieron %u de %u bytes\n\n", escritos, pedidos);
		FileClose(archivo);
		return 1;
	}
	else
	{
		printf("Correcto! Se escribieron %u de %u bytes\n\n", escritos, pedidos);
	}

	if (!FileClose(archivo))
	{
		fprintf(stderr, "Error: no se ha cerrado el archivo.\n\n");
		return 1;
	}
	else
	{
		printf("Cerrado correctamente.\n\n");
	}

	archivo = static_cast<FILE*>(FileOpen("Prueba.bin", EFileMode::FILE_READ));

	if (archivo != nullptr)
	{
		printf("Archivo abierto en modo de lectura.\n\n");
	}
	else
	{
		fprintf(stderr, "Error: no se ha podido abrir el archivo.\n\n");
		return 1;
	}

	char buffer[128];
	unsigned int leidos = FileRead(archivo, buffer, static_cast<unsigned int>(sizeof(buffer) - 1));
	if (leidos != pedidos)
	{
		fprintf(stderr, "Error: se leyeron %u de %u bytes\n\n", leidos, pedidos);
		FileClose(archivo);
		return 1;
	}
	buffer[leidos] = '\0';
	printf("Leidos: %s\n\n", buffer);
	FileClose(archivo);
	if (FileOpen("Error.bin", EFileMode::FILE_READ) == nullptr)
	{
		fprintf(stderr, "Error: archivo 'Error.bin' no encontrado\n\n");
		return 1;
	}
	return 0;
}