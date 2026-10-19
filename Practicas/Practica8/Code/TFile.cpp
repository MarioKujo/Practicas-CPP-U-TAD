#define _CRT_SECURE_NO_WARNINGS // antes de todo
#include <cstdio>
#include <cstring>
#include "TFile.h"

TFile::TFile(){}

TFile::TFile(TFile& tOther)
{
	pFile = tOther.pFile;
}

TFile::~TFile()
{
	fclose(pFile);
}

void* TFile::Open(const char* pszName, TFileMode eMode)
{
	pFile = fopen(pszName, eMode == TFileMode::FILE_READ ? "rb" : "wb");
	return pFile;
}

bool TFile::Close()
{
	if (pFile == nullptr)
	{
		return false;
	}
	return fclose(static_cast<FILE*>(pFile)) == 0;
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
