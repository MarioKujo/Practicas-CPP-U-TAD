#define _CRT_SECURE_NO_WARNINGS // Tiene que ir antes de todos los include
#include <cstdio>
#include <cstring>
#include "TFile.h"

// Si tienes alguna duda, revisa los comentarios de la práctica 5.
// Lo nuevo: "TFile::" delante del nombre indica que la función es un método de la clase TFile

TFile::TFile() {}

// Copia solo el VALOR del puntero (la dirección), no el archivo: los dos objetos acaban apuntando al mismo FILE*.
// Es justo lo que provoca el problema del punto 3 del enunciado
TFile::TFile(TFile& oOther)
{
	m_pFile = oOther.m_pFile;
}

TFile::~TFile()
{
	printf("Destructor: direccion de m_pFile = %p\n", m_pFile);
	Close(); // Si sigue abierto, se cierra aquí; así no se puede olvidar cerrarlo
}

void* TFile::Open(const char* pszName, TFileMode eMode)
{
	Close(); // Si ya había un archivo abierto, se cierra antes para no perder su puntero (y dejarlo abierto para
	// siempre)
	m_pFile = fopen(pszName, eMode == TFileMode::FILE_READ ? "rb" : "wb");
	return m_pFile;
}

bool TFile::Close()
{
	if (m_pFile == nullptr) // No hay nada que cerrar
	{
		return false;
	}
	const bool bOk = (fclose(static_cast<FILE*>(m_pFile)) == 0);
	m_pFile = nullptr; // Marca el objeto como "sin archivo", para que un segundo Close no vuelva a cerrarlo
	return bOk;
}

unsigned int TFile::Read(char* pBuffer, unsigned int uSize)
{
	if (m_pFile == nullptr || pBuffer == nullptr || uSize == 0)
	{
		return 0;
	}
	return static_cast<unsigned int>(fread(pBuffer, 1, uSize, static_cast<FILE*>(m_pFile)));
}

unsigned int TFile::Write(const char* pBuffer, unsigned int uSize)
{
	if (m_pFile == nullptr || pBuffer == nullptr || uSize == 0)
	{
		return 0;
	}
	return static_cast<unsigned int>(fwrite(pBuffer, 1, uSize, static_cast<FILE*>(m_pFile)));
}