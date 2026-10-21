// 1 Organizar el código de la práctica 5 usando un namespace.
#pragma once
#include <iostream>
namespace File
{
	enum EFileMode { FILE_READ, FILE_WRITE };
	void* FileOpen(const char* pszName, EFileMode eMode); // nullptr si falla
	bool FileClose(void* pFile);
	unsigned int FileRead(void* pFile, char* pBuffer, unsigned int uSize); // leídos
	unsigned int FileWrite(void* pFile, const char* pBuffer, unsigned int uSize); // escritos
}