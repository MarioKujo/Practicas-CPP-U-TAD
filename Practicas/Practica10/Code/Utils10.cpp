/*
1 Añadir al namespace de utilidades de la práctica 7 una función que retorne una
lista de cadenas (TList) con los números separados por comas presentes en un
fichero. Diseñar la declaración de la función.
2 Sacar por consola los números leídos.
*/
#include "Utils10.h"
#include "File07.h"
#include <cstring>

// RECORDATORIO: DENTRO DE LA CARPETA DONDE ESTÉ EL .VCXPROJ TIENES QUE PONER EL DOCUMENTO DE TEXTO DE NOMBRE
// "numeros.txt" O DEL NOMBRE DEL ARCHIVO QUE QUIERAS ABRIR. SI NO, OBVIAMENTE NO LO VA A ABRIR, PORQUE NO HAY NADA

namespace Utils
{

	bool ReadNumbers(const char* pszFileName, Practica09::TList& tList)
	{
		tList.Reset(); // Por si acaso, nada más
		if (pszFileName == nullptr)
		{
			return false;
		}
		void* archivo = File::FileOpen(pszFileName, File::EFileMode::FILE_READ);
		if (archivo == nullptr)
		{
			return false;
		}

		constexpr unsigned int BufferSize = 256;
		constexpr unsigned int TokenSize = 32;
		char buffer[BufferSize];
		char token[TokenSize]; // Aquí se va a guardar cada número que va a leer del texto y hay que meterle a la lista
		unsigned int tokenLen = 0;
		unsigned int leidos;

		while ((leidos = File::FileRead(archivo, buffer, BufferSize)) > 0)
		{
			for (unsigned int i = 0; i < leidos; i++)
			{
				const char c = buffer[i];
				if (c == ',') // Compara caracter a caracter y si llega a una coma y ya hay más de un número guardado
					// (tokenLen > 0), se hace push de lo que haya guardado
				{
					if (tokenLen > 0)
					{
						token[tokenLen] = '\0'; // Nunca se puede uno olvidar de esto cuando trata con chars
						tList.Push(token);
					}
					tokenLen = 0; // Se reinicia antes de leer otro número
				}
				else if ((c == '-' || (c >= '0' && c <= '9')) && tokenLen < TokenSize - 1)
				{
					token[tokenLen++] = c; // Si hay un - (negativo) o si hay un número y no ha sobrepasado el tamaño
					// (quitando el '\0'), sigue entrando en la cadena, un número a la vez. Para -37, primero '-', luego
					// '3' y luego '7'
				}

			}
		}
		if (tokenLen > 0)
		{
			token[tokenLen] = '\0'; // El último no va seguido de coma
			tList.Push(token);
		}

		File::FileClose(archivo);
		return true;
	}
}