/*
1 int CountOccurrences(const char* pszFileName, const char* pszText): veces que aparece el texto (-1 si no se abre). Distingue mayúsculas y cuenta las solapadas: "aa" en "aaaa" → 3.

2 bool SumNumbers(const char* pszFileName, int& iSum_): suma de los enteros separados por comas (puede haber negativos, espacios y saltos de línea).

3 Declarar en Utils.h, definir en Utils.cpp y leer con las funciones de la práctica 5, por bloques de 16 caracteres.

4 Probar con texto.txt y numeros.txt: "enemigo" → 3, "Enemigo" → 1, "aa" → 3, "xyz" → 0; la suma es 13245.
*/
#include "Utils06.h"
#include "File05.h"
#include <cstring>
int CountOccurrences(const char* pszFileName, const char* pszText)
{
	if (pszFileName == nullptr || pszText == nullptr)
	{
		return -1;
	}
	FILE* archivo = static_cast<FILE*>(FileOpen(pszFileName, EFileMode::FILE_READ));
	if (archivo == nullptr)
	{
		return -1;
	}

	const unsigned int textSize = static_cast<unsigned int>(strlen(pszText));
	const unsigned int BufferSize = textSize * 2 + 256;// siempre cabe un bloque nuevo tras el arrastre
	char* buffer = new char[BufferSize];

	if (textSize == 0 || textSize >= BufferSize)
	{
		FileClose(archivo);
		delete[]buffer;
		buffer = nullptr;
		return 0;
	}

	int count = 0;
	unsigned int carried = 0;

	while (true)
	{
		unsigned int leidos = FileRead(archivo, buffer + carried, BufferSize - carried);
		if (leidos == 0)
		{
			break;
		}

		const unsigned int total = carried + leidos;

		for (unsigned int i = 0; i + textSize <= total; ++i)
		{
			if (memcmp(buffer + i, pszText, textSize) == 0)
			{
				++count;
			}
		}

		carried = (total >= textSize - 1) ? textSize - 1 : total;
		memmove(buffer, buffer + total - carried, carried);
	}

	FileClose(archivo);
	delete[]buffer;
	buffer = nullptr;
	return count;
}

bool SumNumbers(const char* pszFileName, int& iSum_)
{
	if (pszFileName == nullptr)
	{
		return false;
	}
	FILE* archivo = static_cast<FILE*>(FileOpen(pszFileName, EFileMode::FILE_READ));
	if (archivo == nullptr)
	{
		return false;
	}
	constexpr unsigned int BufferSize = 256;
	char buffer[BufferSize];
	int suma = 0;
	int actual = 0;
	bool negativo = false;
	bool hayDigitos = false;
	unsigned int leidos;
	while ((leidos = FileRead(archivo, buffer, BufferSize)) > 0)
	{
		for (unsigned int i = 0;i < leidos;++i)
		{
			const char c = buffer[i];
			switch (c)
			{
			case '-':
			{
				negativo = true;
				break;
			}
			case '0': case '1': case '2': case '3':	case '4':
			case '5': case '6':	case '7': case '8': case '9':
			{
				actual = actual * 10 + (c - '0');
				hayDigitos = true;
				break;
			}
			case ',':
			{
				if (hayDigitos)
				{
					suma += negativo ? -actual : actual;
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
		suma += negativo ? -actual : actual;
	}
	FileClose(archivo);
	iSum_ = suma;
	return true;
}