// 1 Organizar el código de la práctica 5 usando un namespace.
#pragma once
#include <iostream>

// Un namespace es un "apellido" para un grupo de nombres. Sirve para agrupar código relacionado y evitar
// choques entre nombres (por eso en la práctica 5 no podíamos llamar a las funciones OpenFile o ReadFile,
// que ya existían en windows.h). Para usarlas desde fuera se escribe File::FileOpen(...)
namespace File
{
	enum EFileMode
	{
		FILE_READ, FILE_WRITE
	};
	void* FileOpen(const char* pszName, EFileMode eMode); // nullptr si falla
	bool FileClose(void* pFile);
	unsigned int FileRead(void* pFile, char* pBuffer, unsigned int uSize); // Devuelve cuántos bytes se leyeron
	unsigned int FileWrite(void* pFile, const char* pBuffer, unsigned int uSize); // Devuelve cuántos bytes se
	// escribieron
}