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
#include "File05.h"

// RECORDATORIO: DENTRO DE LA CARPETA DONDE ESTÉ EL .VCXPROJ TIENES QUE PONER EL DOCUMENTO DE TEXTO DE NOMBRE
// "numeros.txt" O DEL NOMBRE DEL ARCHIVO QUE QUIERAS ABRIR. SI NO, OBVIAMENTE NO LO VA A ABRIR, PORQUE NO HAY NADA

void* FileOpen(const char* pszName, EFileMode eMode)
{
	return fopen(pszName, eMode == EFileMode::FILE_READ ? "rb" : "wb"); // "rb" vs "r" y "wb" vs "w": la b significa que
	// se abre en modo binario (byte a byte)
}

bool FileClose(void* pFile)
{
	if (pFile == nullptr)
	{
		return false;
	}

	return fclose(static_cast<FILE*>(pFile)) == 0; // fclose devuelve 0 al igual que main(), 0 significa correcto y
	// cualquier otra cosa error
}

unsigned int FileRead(void* pFile, char* pBuffer, unsigned int uSize) // puntero al archivo, buffer para rellenar con
// lo que se lea y uSize tamaño del buffer
{
	if (pFile == nullptr || pBuffer == nullptr || uSize == 0)
	{
		return 0;
	}

	return static_cast<unsigned int>(fread(pBuffer, 1, uSize, static_cast<FILE*>(pFile))); // 1 es el tamaño en bytes,
	// como queremos leer char*, y char es 1 byte... ya lo pillas. fread devuelve el número de elementos leídos
}

unsigned int FileWrite(void* pFile, const char* pBuffer, unsigned int uSize) // puntero al archivo, buffer con contenido
// con el que rellenar el archivo, tamaño del buffer
{
	if (pFile == nullptr || pBuffer == nullptr || uSize == 0)
	{
		return 0;
	}

	return static_cast<unsigned int>(fwrite(pBuffer, 1, uSize, static_cast<FILE*>(pFile))); // fread devuelve el
	// número de bytes escritos
}