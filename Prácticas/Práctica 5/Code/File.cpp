/*
1 Implementar en File.cpp las funciones declaradas en File.h: FileOpen, FileClose, FileRead y FileWrite (siguiente transparencia).

2 File.h no puede incluir <cstdio> ni nombrar FILE: el identificador del fichero es un void*.

3 Implementar con fopen ("rb" / "wb"), fclose, fread y fwrite. Para evitar el warning C4996: #define _CRT_SECURE_NO_WARNINGS antes de los include.

4 No llamarlas OpenFile, ReadFile...: esos nombres ya existen en windows.h.

5 Probar en un main: escribir un fichero, leerlo y mostrarlo, y abrir uno que no existe (→nullptr).
*/

#define _CRT_SECURE_NO_WARNINGS // antes de todo
#include <cstdio>
#include <cstring>
#include "File.h"

void* FileOpen(const char* pszName, EFileMode eMode)
{
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