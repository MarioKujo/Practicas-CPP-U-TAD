#define _CRT_SECURE_NO_WARNINGS // antes de todo
#include <cstdio>
#include <cstring>
#include "TFile.h"

// Si tienes alguna duda, revisa los comentarios de la práctica 5

TFile::TFile(){}

/*
3. Si se copia un TFile (TFile oCopia = oOriginal;) y después se destruyen los dos, Copia solo el valor del puntero, no
el archivo.Dos objetos son entonces "dueños" del mismo FILE*, y cada destructor lo cierra: doble liberación. La solución
es que un recurso tenga un único dueño: prohibir la copia ( = delete) o transferirlo con semántica de movimiento.
*/

TFile::TFile(TFile& tOther)
{
	pFile = tOther.pFile;
}
TFile::~TFile()
{
	printf("Destructor: direccion de pFile = %p\n", (void*)pFile);
	Close();
}

void* TFile::Open(const char* pszName, TFileMode eMode)
{
	Close(); // Si había algo abierto antes, se jode el que estaba abierto y así Open no revienta
	pFile = fopen(pszName, eMode == TFileMode::FILE_READ ? "rb" : "wb");
	return pFile;
}

bool TFile::Close()
{
	if (pFile == nullptr)
	{
		return false;
	}
	const bool ok = (fclose(static_cast<FILE*>(pFile)) == 0);
	pFile = nullptr;
	return ok;
}

unsigned int TFile::Read(char* pBuffer, unsigned int uSize)
{
	if (pFile == nullptr || pBuffer == nullptr || uSize == 0)
	{
		return 0;
	}
	return static_cast<unsigned int>(fread(pBuffer, 1, uSize, static_cast<FILE*>(pFile)));
}

unsigned int TFile::Write(const char* pBuffer, unsigned int uSize)
{
	if (pFile == nullptr || pBuffer == nullptr || uSize == 0)
	{
		return 0;
	}
	return static_cast<unsigned int>(fwrite(pBuffer, 1, uSize, static_cast<FILE*>(pFile)));
}
