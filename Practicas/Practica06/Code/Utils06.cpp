/*
1 int CountOccurrences(const char* pszFileName, const char* pszText): veces que aparece el texto (-1 si no se abre). Distingue mayúsculas y cuenta las solapadas: "aa" en "aaaa" → 3.

2 bool SumNumbers(const char* pszFileName, int& iSum_): suma de los enteros separados por comas (puede haber negativos, espacios y saltos de línea).

3 Declarar en Utils.h, definir en Utils.cpp y leer con las funciones de la práctica 5, por bloques de 16 caracteres.

4 Probar con texto.txt y numeros.txt: "enemigo" → 3, "Enemigo" → 1, "aa" → 3, "xyz" → 0; la suma es 13245.
*/
#include "Utils06.h"
#include "File05.h"
#include <cstring>

// RECORDATORIO: DENTRO DE LA CARPETA DONDE ESTÉ EL .VCXPROJ TIENES QUE PONER EL DOCUMENTO DE TEXTO DE NOMBRE
// "numeros.txt" O DEL NOMBRE DEL ARCHIVO QUE QUIERAS ABRIR. SI NO, OBVIAMENTE NO LO VA A ABRIR, PORQUE NO HAY NADA

int CountOccurrences(const char* pszFileName, const char* pszText)
{
	if (pszFileName == nullptr || pszText == nullptr) // Si todo es null, no hay nada que hacer
	{
		return -1;
	}
	void* archivo = FileOpen(pszFileName, EFileMode::FILE_READ); // Lo abre
	if (archivo == nullptr)
	{
		return -1;
	}

	const unsigned int textSize = static_cast<unsigned int>(strlen(pszText)); // Tamaño completo del texto
	// El buffer guarda un bloque, no el archivo entero: sitio para los bytes arrastrados + datos nuevos
	const unsigned int BufferSize = textSize * 2 + 256;
	char* buffer = new char[BufferSize]; // <-- NEW

	if (textSize == 0 || textSize >= BufferSize) // Si lo que buscas es mayor o no le has pasado nada, cierra
	{
		FileClose(archivo);
		delete[]buffer; // <-- DELETE
		buffer = nullptr; // <-- TAMBIÉN IMPORTANTE
		return 0;
	}

	int count = 0;
	unsigned int carried = 0;

	while (true)
	{
		// Lee a continuación de los bytes arrastrados; BufferSize - carried es el espacio libre
		unsigned int leidos = FileRead(archivo, buffer + carried, BufferSize - carried);
		if (leidos == 0)   // fin del archivo: no queda nada que procesar
		{
			break;
		}

		// Bytes válidos en el buffer: los arrastrados + los recién leídos
		const unsigned int total = carried + leidos;

		// Prueba cada posición donde cabe el texto; i avanza de 1 en 1, así cuenta las solapadas
		for (unsigned int i = 0; i + textSize <= total; ++i)
		{
			if (memcmp(buffer + i, pszText, textSize) == 0) // compara la información guardada en ambos punteros y si es
				// exactamente igual ( == 0), suma 1 a la cuenta de ocurrencias
			{
				++count;
			}
		}
		// Conserva los últimos textSize-1 bytes: una aparición cortada por la frontera del bloque
		// se completará con los primeros bytes del siguiente bloque
		carried = (total >= textSize - 1) ? textSize - 1 : total;
		memmove(buffer, buffer + total - carried, carried);  // memmove: origen y destino pueden solaparse
	}

	FileClose(archivo);
	delete[]buffer;
	buffer = nullptr;
	return count;
}

bool SumNumbers(const char* pszFileName, int& iSum_)
{
	if (pszFileName == nullptr) // Si no existe, devuelve
	{
		return false;
	}
	void* archivo = FileOpen(pszFileName, EFileMode::FILE_READ);
	if (archivo == nullptr)
	{
		return false;
	}
	constexpr unsigned int BufferSize = 256; // Estándar
	char buffer[BufferSize]; // No puntero porque no hace falta (es un iterador para leer todo el texto en bloques)
	int suma = 0;
	int actual = 0;
	bool negativo = false;
	bool hayDigitos = false;
	unsigned int leidos;
	while ((leidos = FileRead(archivo, buffer, BufferSize)) > 0) // Mientras que siga habiendo texto que leer
	{
		for (unsigned int i = 0;i < leidos;++i)
		{
			const char c = buffer[i];
			switch (c)
			{
			case '-':
			{
				negativo = true; // Si hay un -, el número que va delante es negativo
				break;
			}
			case '0': case '1': case '2': case '3':	case '4':
			case '5': case '6':	case '7': case '8': case '9':
			{
				actual = actual * 10 + (c - '0'); // Todo número que viene se va poniendo hacia la izquierda.
				// Ejemplo con 120: actual = 0 * 10 + ('1' - '0') = 1; actual = 1 * 10 + ('2' - '0') = 12;
				// actual = 12 * 10 + ('0' - '0') = 120;
				hayDigitos = true;
				break;
			}
			case ',':
			{
				if (hayDigitos)
				{
					suma += negativo ? -actual : actual; // Creo que se entiende
				}
				actual = 0;
				negativo = false;
				hayDigitos = false;
				break;
			}
			default:
			{
				break;
			}
			}
		}
	}
	if (hayDigitos)
	{
		suma += negativo ? -actual : actual; // OJO: El último dígito no va seguido de coma
	}
	FileClose(archivo);
	iSum_ = suma;
	return true;
}