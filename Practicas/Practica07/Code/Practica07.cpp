#include <cstdio>
#include <cstring>
#include "File07.h"
#include "Utils07.h"
// Si tienes dudas de este código, lee los comentarios de las prácticas 5 y 6, es exactamente lo mismo.
// Lo único que cambia es que ahora hay que escribir File:: o Utils:: delante de cada función y del enum
int main()
{
#pragma region File

	// --- Escritura ---
	printf("--- FILE ---\n\n");
	void* pArchivo = File::FileOpen("../../../Archivos de texto/Prueba07.bin", File::EFileMode::FILE_WRITE);
	if (pArchivo == nullptr)
	{
		fprintf(stderr, "Error: no se ha podido abrir el archivo.\n");
		return 1;
	}
	printf("Archivo abierto en modo de escritura.\n");

	const char* const pszNumeros = "1 2 3 4 5 6 7 8 9 10";
	const unsigned int uPedidos = static_cast<unsigned int>(strlen(pszNumeros));
	const unsigned int uEscritos = File::FileWrite(pArchivo, pszNumeros, uPedidos);
	if (uPedidos != uEscritos)
	{
		fprintf(stderr, "Error: se escribieron %u de %u bytes\n", uEscritos, uPedidos);
		File::FileClose(pArchivo);
		return 1;
	}
	printf("Correcto! Se escribieron %u de %u bytes\n", uEscritos, uPedidos);

	if (!File::FileClose(pArchivo))
	{
		fprintf(stderr, "Error: no se ha cerrado el archivo.\n");
		return 1;
	}
	printf("Cerrado correctamente.\n\n");

	// --- Lectura ---
	pArchivo = File::FileOpen("../../../Archivos de texto/Prueba07.bin", File::EFileMode::FILE_READ);
	if (pArchivo == nullptr)
	{
		fprintf(stderr, "Error: no se ha podido abrir el archivo.\n");
		return 1;
	}
	printf("Archivo abierto en modo de lectura.\n");

	char acBuffer[128];
	const unsigned int uLeidos = File::FileRead(pArchivo, acBuffer, static_cast<unsigned int>(sizeof(acBuffer) - 1));
	if (uLeidos != uPedidos)
	{
		fprintf(stderr, "Error: se leyeron %u de %u bytes\n", uLeidos, uPedidos);
		File::FileClose(pArchivo);
		return 1;
	}
	acBuffer[uLeidos] = '\0';
	printf("Leidos: %s\n", acBuffer);
	File::FileClose(pArchivo);
	printf("Cerrado correctamente.\n\n");

	// --- Archivo inexistente ---
	if (File::FileOpen("../../../Archivos de texto/Error.bin", File::EFileMode::FILE_READ) == nullptr)
	{
		printf("Correcto: el archivo inexistente '../../../Archivos de texto/Error.bin' devuelve nullptr.\n\n");
	}
#pragma endregion

#pragma region Utils

	printf("--- UTILS ---\n\n");
	const char* const apszTextos[] =
	{
		"enemigo", "Enemigo", "aa", "xyz"
	}; // Array de cadenas a buscar
	for (const char* pszTexto : apszTextos) // Recorre el array de uno en uno
	{
		const int iCuenta = Utils::CountOccurrences("../../../Archivos de texto/texto.txt", pszTexto); // Se crea y se
		// destruye en cada vuelta
		printf("'%s' aparece %d %s\n", pszTexto, iCuenta, iCuenta == 1 ? "vez" : "veces");
	}

	printf("\n");

	int iSuma = 0;
	if (Utils::SumNumbers("../../../Archivos de texto/numeros.txt", iSuma))
	{
		printf("La suma es %d\n", iSuma);
	}
#pragma endregion
	return 0;
}