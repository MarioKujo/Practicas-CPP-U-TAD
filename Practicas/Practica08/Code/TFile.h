/*
1 Implementar la funcionalidad de la práctica 5 con una clase TFile: las funciones pasan a ser métodos (Open, Close,
Read, Write) y el identificador del fichero, un miembro privado.

2 El destructor cierra el fichero si sigue abierto: así no se puede olvidar cerrarlo.

3 ¿Qué pasa si se copia un TFile (TFile oCopia = oOriginal;) y después se destruyen los dos? Probarlo y explicarlo.

- Si se copia un TFile (TFile oCopia = oOriginal;) y después se destruyen los dos, se copia solo el valor del puntero,
no el archivo. Dos objetos son entonces "dueños" del mismo FILE*, y cada destructor lo cierra: doble liberación. La
solución es que un recurso tenga un único dueño: prohibir la copia ( = delete) o transferirlo con semántica de
movimiento.
*/
#pragma once

enum class TFileMode
{
	FILE_READ, FILE_WRITE
};

// Una clase agrupa datos (miembros) y las funciones que trabajan con ellos (métodos).
// Se usa así: TFile oArchivo; oArchivo.Open(...); oArchivo.Write(...);
class TFile
{
public:	// Lo que está en "public" se puede usar desde fuera de la clase
	TFile(); // Constructor: se ejecuta solo al crear el objeto
	TFile(TFile& oOther); // Constructor de copia: se ejecuta con TFile oCopia = oOriginal; o TFile oCopia(oOriginal);
	~TFile(); // Destructor: se ejecuta solo cuando el objeto se destruye (aquí, al salir de main)
	void* Open(const char* pszName, TFileMode eMode); // nullptr si falla
	bool Close();
	unsigned int Read(char* pBuffer, unsigned int uSize); // Devuelve cuántos bytes se leyeron
	unsigned int Write(const char* pBuffer, unsigned int uSize); // Devuelve cuántos bytes se escribieron
private: // Lo que está en "private" solo lo ven los métodos de la clase: nadie de fuera puede tocar el archivo
	// directamente
	void* m_pFile = nullptr; // El FILE* escondido como void*. nullptr = no hay nada abierto
};