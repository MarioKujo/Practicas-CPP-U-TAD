/*
1 Implementar en File.cpp las funciones declaradas en File.h: FileOpen, FileClose, FileRead y FileWrite (siguiente
transparencia).

2 File.h no puede incluir <cstdio> ni nombrar FILE: el identificador del fichero es un void*.

3 Implementar con fopen ("rb" / "wb"), fclose, fread y fwrite. Para evitar el warning C4996: #define
_CRT_SECURE_NO_WARNINGS antes de los include.

4 No llamarlas OpenFile, ReadFile...: esos nombres ya existen en windows.h.

5 Probar en un main: escribir un fichero, leerlo y mostrarlo, y abrir uno que no existe (→nullptr).
*/
#pragma once

// Modo en el que se abre el archivo: para leer o para escribir
enum EFileMode
{
	FILE_READ, FILE_WRITE
};

// Un void* es un puntero "sin tipo": guarda una dirección de memoria sin decir qué hay en ella.
// Aquí se usa para esconder el FILE* de <cstdio>; quien use estas funciones solo se guarda el puntero y se lo pasa
// a las demás funciones, sin saber qué hay dentro.
void* FileOpen(const char* pszName, EFileMode eMode); // Devuelve nullptr si falla
bool FileClose(void* pFile); // Devuelve true si se cerró bien (solo falla si no hay nada abierto)
unsigned int FileRead(void* pFile, char* pBuffer, unsigned int uSize); // Devuelve cuántos bytes se leyeron
unsigned int FileWrite(void* pFile, const char* pBuffer, unsigned int uSize); // Devuelve cuántos bytes se escribieron