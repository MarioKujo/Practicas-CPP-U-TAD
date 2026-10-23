/*
1 Implementar en File.cpp las funciones declaradas en File.h: FileOpen, FileClose, FileRead y FileWrite (siguiente transparencia).

2 File.h no puede incluir <cstdio> ni nombrar FILE: el identificador del fichero es un void*.

3 Implementar con fopen ("rb" / "wb"), fclose, fread y fwrite. Para evitar el warning C4996: #define _CRT_SECURE_NO_WARNINGS antes de los include.

4 No llamarlas OpenFile, ReadFile...: esos nombres ya existen en windows.h.

5 Probar en un main: escribir un fichero, leerlo y mostrarlo, y abrir uno que no existe (→nullptr).
*/
#pragma once
#include <iostream>
enum EFileMode { FILE_READ, FILE_WRITE };
void* FileOpen(const char* pszName, EFileMode eMode); // nullptr si falla
bool FileClose(void* pFile); // Cerrar (nunca puede dar error, siempre y cuando haya algo abierto)
unsigned int FileRead(void* pFile, char* pBuffer, unsigned int uSize); // leídos
unsigned int FileWrite(void* pFile, const char* pBuffer, unsigned int uSize); // escritos