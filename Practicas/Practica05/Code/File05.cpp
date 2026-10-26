// El enunciado está en File05.h
#define _CRT_SECURE_NO_WARNINGS // Tiene que ir antes de todos los include
#include <cstdio>
#include <cstring>
#include "File05.h"

// Si se abre un archivo para leer, tiene que existir ya en la carpeta del proyecto (donde está el .vcxproj).
// Si se abre para escribir, se crea (y si ya existía, se borra su contenido).

void* FileOpen(const char* pszName, EFileMode eMode)
{
	if (pszName == nullptr)
	{
		return nullptr;
	}
	// fopen devuelve un FILE* (o nullptr si falla), que se convierte solo a void*.
	// "rb" y "wb" son "read" y "write" en modo binario (la b): lee y escribe los bytes tal cual, sin traducir nada.
	return fopen(pszName, eMode == EFileMode::FILE_READ ? "rb" : "wb");
}

bool FileClose(void* pFile)
{
	if (pFile == nullptr) // No hay nada que cerrar
	{
		return false;
	}

	// Aquí hay que devolver el void* a su tipo real (FILE*) con static_cast, porque fclose solo entiende FILE*.
	// fclose devuelve 0 si fue bien y otro número si hubo error, por eso se compara con 0 para obtener un bool
	return fclose(static_cast<FILE*>(pFile)) == 0;
}

// pFile: archivo abierto, pBuffer: sitio donde se guardará lo leído, uSize: cuántos bytes como máximo se leen
unsigned int FileRead(void* pFile, char* pBuffer, unsigned int uSize)
{
	if (pFile == nullptr || pBuffer == nullptr || uSize == 0)
	{
		return 0;
	}

	// fread(dónde, tamaño de cada elemento, cuántos elementos, archivo).
	// Como cada elemento es un char (1 byte), pedir uSize elementos es pedir uSize bytes.
	// Devuelve cuántos elementos leyó, que aquí es lo mismo que bytes. Puede ser menos que uSize si el archivo
	// termina antes
	return static_cast<unsigned int>(fread(pBuffer, 1, uSize, static_cast<FILE*>(pFile)));
}

// pFile: archivo abierto, pBuffer: contenido que se escribirá, uSize: cuántos bytes se escriben
unsigned int FileWrite(void* pFile, const char* pBuffer, unsigned int uSize)
{
	if (pFile == nullptr || pBuffer == nullptr || uSize == 0)
	{
		return 0;
	}

	// Igual que fread, pero escribiendo. Devuelve cuántos bytes escribió (si es menos que uSize, algo falló)
	return static_cast<unsigned int>(fwrite(pBuffer, 1, uSize, static_cast<FILE*>(pFile)));
}