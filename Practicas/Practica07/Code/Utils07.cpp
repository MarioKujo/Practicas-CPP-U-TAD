// 2 Organizar el código de la práctica 6 usando un namespace.
#include "Utils07.h"
#include "File07.h"
#include <cstring>
namespace Utils
{
	int CountOccurrences(const char* pszFileName, const char* pszText)
	{
		if (pszFileName == nullptr || pszText == nullptr)
		{
			return -1;
		}
		FILE* archivo = static_cast<FILE*>(File::FileOpen(pszFileName, File::EFileMode::FILE_READ));
		if (archivo == nullptr)
		{
			return -1;
		}

		const unsigned int textSize = static_cast<unsigned int>(strlen(pszText));
		const unsigned int BufferSize = textSize * 2 + 256;// siempre cabe un bloque nuevo tras el arrastre
		char* buffer = new char[BufferSize];

		if (textSize == 0 || textSize >= BufferSize)
		{
			File::FileClose(archivo);
			delete[]buffer;
			buffer = nullptr;
			return 0;
		}

		int count = 0;
		unsigned int carried = 0;

		while (true)
		{
			unsigned int leidos = File::FileRead(archivo, buffer + carried, BufferSize - carried);
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

		File::FileClose(archivo);
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
		FILE* archivo = static_cast<FILE*>(File::FileOpen(pszFileName, File::EFileMode::FILE_READ));
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
		while ((leidos = File::FileRead(archivo, buffer, BufferSize)) > 0)
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
		File::FileClose(archivo);
		iSum_ = suma;
		return true;
	}
}