/*
1 Añadir al namespace de utilidades de la práctica 7 una función que retorne una
lista de cadenas (TList) con los números separados por comas presentes en un
fichero. Diseñar la declaración de la función.
2 Sacar por consola los números leídos.
*/
#include "Utils10.h"
#include "File07.h"
#include <cstring>
namespace Utils
{

	bool ReadNumbers(const char* pszFileName, TList& tList)
	{
		tList.Reset();
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
		char token[TokenSize];
		unsigned int tokenLen = 0;
		unsigned int leidos;

		while ((leidos = File::FileRead(archivo, buffer, BufferSize)) > 0)
		{
			for (unsigned int i = 0; i < leidos; i++)
			{
				const char c = buffer[i];
				if (c == ',')
				{
					if (tokenLen > 0)
					{
						token[tokenLen] = '\0';
						tList.Push(token);
					}
					tokenLen = 0;
				}
				else if ((c == '-' || (c >= '0' && c <= '9')) && tokenLen < TokenSize - 1)
				{
					token[tokenLen++] = c;
				}

			}
		}
		if (tokenLen > 0)
		{
			token[tokenLen] = '\0';
			tList.Push(token);
		}

		File::FileClose(archivo);
		return true;
	}
}