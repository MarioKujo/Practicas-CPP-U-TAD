// 1 Organizar el código de la práctica 5 usando un namespace.
#define _CRT_SECURE_NO_WARNINGS // Tiene que ir antes de todos los include
#include <cstdio>
#include <cstring>
#include "File07.h"

// Si tienes dudas de este código, lee los comentarios de las prácticas 5 y 6, es exactamente lo mismo.
// Lo único nuevo es que todo está dentro de namespace File, igual que en el .h

namespace File
{
	void* FileOpen(const char* pszName, EFileMode eMode)
	{
		if (pszName == nullptr)
		{
			return nullptr;
		}
		return fopen(pszName, eMode == EFileMode::FILE_READ ? "rb" : "wb");
	}

	bool FileClose(void* pFile)
	{
		if (pFile == nullptr)
		{
			return false;
		}

		return fclose(static_cast<FILE*>(pFile)) == 0;
	}

	unsigned int FileRead(void* pFile, char* pBuffer, unsigned int uSize)
	{
		if (pFile == nullptr || pBuffer == nullptr || uSize == 0)
		{
			return 0;
		}

		return static_cast<unsigned int>(fread(pBuffer, 1, uSize, static_cast<FILE*>(pFile)));
	}

	unsigned int FileWrite(void* pFile, const char* pBuffer, unsigned int uSize)
	{
		if (pFile == nullptr || pBuffer == nullptr || uSize == 0)
		{
			return 0;
		}

		return static_cast<unsigned int>(fwrite(pBuffer, 1, uSize, static_cast<FILE*>(pFile)));
	}
}