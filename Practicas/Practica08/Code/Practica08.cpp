#include "TFile.h"
#include <cstring>
#include <iostream>

// Si tienes alguna duda, revisa los comentarios de la práctica 5

int main()
{
	TFile oArchivo; // Ya no hay que cerrarlo a mano al final: el destructor lo hace
	// --- Escritura ---
	void* pArchivo = oArchivo.Open("Prueba.bin", TFileMode::FILE_WRITE);
	if (pArchivo == nullptr)
	{
		fprintf(stderr, "Error: no se ha podido abrir el archivo.\n");
		return 1;
	}
	printf("Archivo abierto en modo de escritura.\n");

	const char* const pszNumeros = "1 2 3 4 5 6 7 8 9 10";
	const unsigned int uPedidos = static_cast<unsigned int>(strlen(pszNumeros));
	const unsigned int uEscritos = oArchivo.Write(pszNumeros, uPedidos);
	if (uPedidos != uEscritos)
	{
		fprintf(stderr, "Error: se escribieron %u de %u bytes\n", uEscritos, uPedidos);
		return 1; // No hace falta cerrar: el destructor de oArchivo lo hará al salir
	}
	printf("Correcto! Se escribieron %u de %u bytes\n", uEscritos, uPedidos);

	if (oArchivo.Close())
	{
		printf("Cerrado correctamente.\n\n");
	}

	// --- Lectura ---
	pArchivo = oArchivo.Open("Prueba.bin", TFileMode::FILE_READ);
	if (pArchivo == nullptr)
	{
		fprintf(stderr, "Error: no se ha podido abrir el archivo.\n");
		return 1;
	}
	printf("Archivo abierto en modo de lectura.\n");

	char acBuffer[128];
	// Se piden 127 bytes y no 128 para dejar sitio al '\0' final
	const unsigned int uLeidos = oArchivo.Read(acBuffer, static_cast<unsigned int>(sizeof(acBuffer) - 1));
	acBuffer[uLeidos] = '\0';
	printf("Leidos: %s\n", acBuffer);
	if (oArchivo.Close())
	{
		printf("Cerrado correctamente.\n\n");
	}

	// --- Archivo inexistente ---
	if (oArchivo.Open("Error.bin", TFileMode::FILE_READ) == nullptr)
	{
		printf("Correcto: el archivo inexistente 'Error.bin' devuelve nullptr.\n\n");
	}

	// --- Doble liberación ---
	oArchivo.Open("Prueba.bin", TFileMode::FILE_READ);
	TFile oCopia = oArchivo;
	printf("Copia hecha. Ahora se destruyen los dos...\n\n");
	return 0;
}