/*
1 Implementar la funcionalidad de la práctica 5 con una clase TFile: las funciones pasan a ser métodos (Open, Close, Read, Write) y el identificador del fichero, un miembro privado.

2 El destructor cierra el fichero si sigue abierto: así no se puede olvidar cerrarlo.

3 ¿Qué pasa si se copia un TFile (TFile oCopia = oOriginal;) y después se destruyen los dos? Probarlo y explicarlo.
*/
#pragma once
#include <iostream>

enum class TFileMode { FILE_READ, FILE_WRITE };

class TFile
{
public:
	TFile();
	TFile(TFile& tOther);
	~TFile();
	void* Open(const char* pszName, TFileMode eMode); // nullptr si falla
	bool Close();
	unsigned int Read(char* pBuffer, unsigned int uSize); // leídos
	unsigned int Write(const char* pBuffer, unsigned int uSize); // escritos
private:
	FILE* pFile = nullptr;
};