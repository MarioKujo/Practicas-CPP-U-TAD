// El enunciado está en Utils06.h
#include "Utils06.h"
#include "File05.h"
#include <cstring>

// Los archivos texto.txt y numeros.txt tienen que estar en la carpeta del proyecto (donde está el .vcxproj).
// Si no están, FileOpen devuelve nullptr y las funciones devuelven -1 / false.

// El enunciado pide leer el archivo por bloques de 16 caracteres: cada FileRead pide como máximo esta cantidad
constexpr unsigned int s_uTamBloque = 16;

int CountOccurrences(const char* pszFileName, const char* pszText)
{
	if (pszFileName == nullptr || pszText == nullptr) // Sin nombre o sin texto no hay nada que buscar
	{
		return -1;
	}
	void* pArchivo = FileOpen(pszFileName, EFileMode::FILE_READ);
	if (pArchivo == nullptr)
	{
		return -1;
	}

	const unsigned int uTamTexto = static_cast<unsigned int>(strlen(pszText)); // Sin contar el '\0'

	if (uTamTexto == 0) // Texto vacío: no hay nada que contar
	{
		FileClose(pArchivo);
		return 0;
	}

	// No cargamos el archivo entero: lo leemos por bloques y reutilizamos el mismo buffer.
	// Su tamaño es lo máximo que puede haber a la vez: hasta (uTamTexto - 1) bytes arrastrados del bloque
	// anterior + un bloque nuevo de 16. Con uTamTexto + s_uTamBloque sobra un byte, pero así es más fácil de leer
	const unsigned int uTamBuffer = uTamTexto + s_uTamBloque;
	char* const pcBuffer = new char[uTamBuffer]; // Memoria dinámica: hay que liberarla con delete[]

	int iCuenta = 0;
	unsigned int uArrastrados = 0; // Bytes del bloque anterior que se conservan al principio del buffer

	while (true)
	{
		// Se lee un bloque de 16 bytes justo detrás de los bytes arrastrados
		unsigned int uLeidos = FileRead(pArchivo, pcBuffer + uArrastrados, s_uTamBloque);
		if (uLeidos == 0) // El archivo se ha acabado
		{
			break;
		}

		// Bytes útiles del buffer: los arrastrados + los recién leídos
		const unsigned int uTotal = uArrastrados + uLeidos;

		// Se prueba cada posición donde todavía cabe el texto. Avanza de 1 en 1 (no de uTamTexto en uTamTexto),
		// por eso se cuentan también las apariciones solapadas: "aa" en "aaaa" aparece en 0, 1 y 2
		for (unsigned int uPos = 0; uPos + uTamTexto <= uTotal; ++uPos)
		{
			// memcmp compara byte a byte dos zonas de memoria; devuelve 0 si son idénticas
			if (memcmp(pcBuffer + uPos, pszText, uTamTexto) == 0)
			{
				++iCuenta;
			}
		}

		// Una aparición podría quedar cortada entre dos bloques (la mitad al final de uno y la mitad al principio
		// del siguiente). Para no perderla, guardamos los últimos uTamTexto - 1 bytes y los movemos al inicio del buffer.
		// Con uno menos no puede haber una aparición completa, así que nada se cuenta dos veces
		uArrastrados = (uTotal >= uTamTexto - 1) ? uTamTexto - 1 : uTotal;
		memmove(pcBuffer, pcBuffer + uTotal - uArrastrados, uArrastrados); // memmove permite que origen y destino se solapen
	}

	FileClose(pArchivo);
	delete[] pcBuffer;
	return iCuenta;
}

bool SumNumbers(const char* pszFileName, int& iSum_)
{
	if (pszFileName == nullptr)
	{
		return false;
	}
	void* pArchivo = FileOpen(pszFileName, EFileMode::FILE_READ);
	if (pArchivo == nullptr)
	{
		return false;
	}

	char acBuffer[s_uTamBloque]; // Array normal (no new): su tamaño es fijo y se libera solo al salir de la función

	// El número se va construyendo carácter a carácter, y estas variables se conservan entre bloques por si un
	// número queda cortado justo en la frontera entre dos lecturas (con bloques de 16 pasa a menudo)
	int iSuma = 0; // Total acumulado
	int iActual = 0; // Número que se está leyendo ahora mismo
	bool bNegativo = false; // true si el número actual lleva un '-' delante
	bool bHayDigitos = false; // true si ya se ha leído algún dígito del número actual
	unsigned int uLeidos;

	// Se asigna y se compara en la misma línea: lee un bloque y repite mientras haya leído algo
	while ((uLeidos = FileRead(pArchivo, acBuffer, s_uTamBloque)) > 0)
	{
		for (unsigned int uPos = 0; uPos < uLeidos; ++uPos)
		{
			const char cCaracter = acBuffer[uPos];
			switch (cCaracter)
			{
			case '-':
			{
				bNegativo = true; // El número que viene a continuación es negativo
				break;
			}
			case '0': case '1': case '2': case '3':	case '4':
			case '5': case '6':	case '7': case '8': case '9':
			{
				// Los caracteres '0'..'9' son números consecutivos en la tabla ASCII, así que restarle '0' a
				// un dígito da su valor (por ejemplo '7' - '0' = 7).
				// Cada dígito nuevo desplaza el número una posición a la izquierda (x10) y se suma al final.
				// Ejemplo con 120: 0*10+1 = 1; 1*10+2 = 12; 12*10+0 = 120
				iActual = iActual * 10 + (cCaracter - '0');
				bHayDigitos = true;
				break;
			}
			case ',':
			{
				// La coma indica que el número ha terminado: se suma al total y se prepara para el siguiente
				if (bHayDigitos)
				{
					iSuma += bNegativo ? -iActual : iActual;
				}
				iActual = 0;
				bNegativo = false;
				bHayDigitos = false;
				break;
			}
			default: // Espacios, saltos de línea y cualquier otra cosa se ignoran
			{
				break;
			}
			}
		}
	}
	if (bHayDigitos)
	{
		iSuma += bNegativo ? -iActual : iActual; // El último número no va seguido de coma, así que se suma aquí
	}
	FileClose(pArchivo);
	iSum_ = iSuma; // Se escribe el resultado en la variable del llamador
	return true;
}