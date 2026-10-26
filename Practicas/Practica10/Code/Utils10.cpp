// El enunciado está en Utils10.h
#include "Utils10.h"
#include "File07.h"

// El archivo (por ejemplo numeros.txt) tiene que estar en la carpeta del proyecto (donde está el .vcxproj).
// Si no está, FileOpen devuelve nullptr y la función devuelve false.
// Si tienes dudas con la lectura del archivo, mira los comentarios de las prácticas 5 y 6


namespace Utils
{
	constexpr unsigned int s_uTamBloque = 16;

	bool ReadNumbers(const char* pszFileName, Practica09::TList& oLista_)
	{
		oLista_.Reset(); // Vacía la lista, para que al terminar solo contenga los números de ESTE archivo
		if (pszFileName == nullptr)
		{
			return false;
		}
		void* pArchivo = File::FileOpen(pszFileName, File::EFileMode::FILE_READ);
		if (pArchivo == nullptr)
		{
			return false;
		}
		constexpr unsigned int uTamToken = 32; // Máximo de caracteres de un número (31 + el '\0')
		char acBuffer[s_uTamBloque];
		// Aquí se va construyendo cada número como texto, carácter a carácter, hasta llegar a una coma.
		// Se conserva entre bloques por si un número queda cortado justo en la frontera entre dos lecturas
		char acToken[uTamToken];
		unsigned int uLongToken = 0; // Cuántos caracteres lleva acToken ahora mismo
		unsigned int uLeidos;

		while ((uLeidos = File::FileRead(pArchivo, acBuffer, s_uTamBloque)) > 0)
		{
			for (unsigned int uPos = 0; uPos < uLeidos; ++uPos)
			{
				const char cCaracter = acBuffer[uPos];
				if (cCaracter == ',')
				{
					// La coma indica que el número ha terminado. Si hay algo guardado (uLongToken > 0),
					// se cierra la cadena con '\0' y se añade a la lista. TList::Push hace su propia copia
					// de la cadena, así que reutilizar acToken para el siguiente número no es problema
					if (uLongToken > 0)
					{
						acToken[uLongToken] = '\0'; // Sin esto, la cadena no tendría final
						oLista_.Push(acToken);
					}
					uLongToken = 0; // Se empieza de cero para el siguiente número
				}
				else if ((cCaracter == '-' || (cCaracter >= '0' && cCaracter <= '9')) && uLongToken < uTamToken - 1)
				{
					// Solo se guardan '-' y dígitos; espacios y saltos de línea se ignoran. La segunda condición
					// evita escribir fuera de acToken (se deja siempre un hueco para el '\0').
					// Para -37 entra primero '-', luego '3' y luego '7'
					acToken[uLongToken++] = cCaracter;
				}
			}
		}
		if (uLongToken > 0)
		{
			acToken[uLongToken] = '\0'; // El último número no va seguido de coma, así que se añade aquí
			oLista_.Push(acToken);
		}

		File::FileClose(pArchivo);
		return true;
	}
}