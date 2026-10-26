#include "File05.h"
#include <cstdio>
#include <cstring>

int main()
{
	// --- Escritura ---
	void* pArchivo = FileOpen("../../../Archivos de texto/Prueba05.bin", EFileMode::FILE_WRITE);
	if (pArchivo == nullptr)
	{
		fprintf(stderr, "Error: no se ha podido abrir el archivo.\n");
		return 1;
	}
	printf("Archivo abierto en modo de escritura.\n");

	const char* const pszNumeros = "1 2 3 4 5 6 7 8 9 10";
	const unsigned int uPedidos = static_cast<unsigned int>(strlen(pszNumeros)); // Sin contar el '\0': en el archivo solo va
	// el texto
	const unsigned int uEscritos = FileWrite(pArchivo, pszNumeros, uPedidos);
	if (uPedidos != uEscritos) // Solo pasaría si falla el disco (por ejemplo, si está lleno)
	{
		fprintf(stderr, "Error: se escribieron %u de %u bytes\n", uEscritos, uPedidos);
		FileClose(pArchivo); // Aunque haya fallado, hay que cerrarlo igualmente
		return 1;
	}
	printf("Correcto! Se escribieron %u de %u bytes\n", uEscritos, uPedidos);

	if (!FileClose(pArchivo))
	{
		fprintf(stderr, "Error: no se ha cerrado el archivo.\n");
		return 1;
	}
	printf("Cerrado correctamente.\n\n");

	// --- Lectura ---
	pArchivo = FileOpen("../../../Archivos de texto/Prueba05.bin", EFileMode::FILE_READ); // Reutilizamos la variable, ya cerrada
	if (pArchivo == nullptr)
	{
		fprintf(stderr, "Error: no se ha podido abrir el archivo.\n");
		return 1;
	}
	printf("Archivo abierto en modo de lectura.\n");

	char acBuffer[128];
	// Se piden 127 bytes y no 128 para dejar sitio al '\0' final: el archivo no lo guarda, hay que ponerlo a mano
	const unsigned int uLeidos = FileRead(pArchivo, acBuffer, static_cast<unsigned int>(sizeof(acBuffer) - 1));
	if (uLeidos != uPedidos) // Tienen que coincidir: leemos el archivo entero, que es lo que escribimos antes
	{
		fprintf(stderr, "Error: se leyeron %u de %u bytes\n", uLeidos, uPedidos);
		FileClose(pArchivo);
		return 1;
	}
	acBuffer[uLeidos] = '\0'; // Sin esto printf no sabría dónde termina el texto
	printf("Leidos: %s\n", acBuffer);
	FileClose(pArchivo);
	printf("Cerrado correctamente.\n\n");

	// --- Archivo inexistente ---
	if (FileOpen("Error.bin", EFileMode::FILE_READ) == nullptr)
	{
		printf("Correcto: el archivo inexistente 'Error.bin' devuelve nullptr.\n");
	}
	return 0;
}