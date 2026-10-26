// 2 Organizar el código de la práctica 6 usando un namespace.
#include "Utils07.h"
#include "File07.h"
#include <cstdio>
#include <cstring>

// Si tienes dudas de este código, lee los comentarios de las prácticas 5 y 6, es exactamente lo mismo.
// Lo nuevo: las funciones de la práctica 5 ahora se llaman con File:: delante (File::FileOpen, File::FileRead...)

namespace Utils
{
	constexpr unsigned int s_uTamBloque = 16;

	int CountOccurrences(const char* pszFileName, const char* pszText)
	{
		if (pszFileName == nullptr || pszText == nullptr)
		{
			return -1;
		}
		FILE* pArchivo = static_cast<FILE*>(File::FileOpen(pszFileName, File::EFileMode::FILE_READ));
		if (pArchivo == nullptr)
		{
			return -1;
		}

		const unsigned int uTamTexto = static_cast<unsigned int>(strlen(pszText));

		if (uTamTexto == 0)
		{
			File::FileClose(pArchivo);
			return 0;
		}
		const unsigned int uTamBuffer = uTamTexto + s_uTamBloque;
		char* pcBuffer = new char[uTamBuffer];

		int iCuenta = 0;
		unsigned int uArrastrados = 0;

		while (true)
		{
			unsigned int uLeidos = File::FileRead(pArchivo, pcBuffer + uArrastrados, s_uTamBloque);
			if (uLeidos == 0)
			{
				break;
			}

			const unsigned int uTotal = uArrastrados + uLeidos;

			for (unsigned int uPos = 0; uPos + uTamTexto <= uTotal; ++uPos)
			{
				if (memcmp(pcBuffer + uPos, pszText, uTamTexto) == 0)
				{
					++iCuenta;
				}
			}

			uArrastrados = (uTotal >= uTamTexto - 1) ? uTamTexto - 1 : uTotal;
			memmove(pcBuffer, pcBuffer + uTotal - uArrastrados, uArrastrados);
		}

		File::FileClose(pArchivo);
		delete[] pcBuffer;
		pcBuffer = nullptr;
		return iCuenta;
	}

	bool SumNumbers(const char* pszFileName, int& iSum_)
	{
		if (pszFileName == nullptr)
		{
			return false;
		}
		FILE* pArchivo = static_cast<FILE*>(File::FileOpen(pszFileName, File::EFileMode::FILE_READ));
		if (pArchivo == nullptr)
		{
			return false;
		}
		char acBuffer[s_uTamBloque];
		int iSuma = 0;
		int iActual = 0;
		bool bNegativo = false;
		bool bHayDigitos = false;
		unsigned int uLeidos;
		while ((uLeidos = File::FileRead(pArchivo, acBuffer, s_uTamBloque)) > 0)
		{
			for (unsigned int uPos = 0; uPos < uLeidos; ++uPos)
			{
				const char cCaracter = acBuffer[uPos];
				switch (cCaracter)
				{
				case '-':
				{
					bNegativo = true;
					break;
				}
				case '0': case '1': case '2': case '3':	case '4':
				case '5': case '6':	case '7': case '8': case '9':
				{
					iActual = iActual * 10 + (cCaracter - '0');
					bHayDigitos = true;
					break;
				}
				case ',':
				{
					if (bHayDigitos)
					{
						iSuma += bNegativo ? -iActual : iActual;
					}
					iActual = 0;
					bNegativo = false;
					bHayDigitos = false;
					break;
				}
				default:
				{
					break;
				}
				}
			}
		}
		if (bHayDigitos)
		{
			iSuma += bNegativo ? -iActual : iActual;
		}
		File::FileClose(pArchivo);
		iSum_ = iSuma;
		return true;
	}
}