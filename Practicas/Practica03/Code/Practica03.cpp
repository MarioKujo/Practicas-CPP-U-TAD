/*
1 Dada una tabla de cadenas, hacer una función que, dado un índice, retorne la cadena de ese índice si existe.

2 Hacer una función que, dado un índice a la tabla de cadenas, retorne la cadena de ese índice, si existe, invertida.
*/
#include <iostream>
#include <crtdbg.h> // Solo existe en Visual Studio (Windows): sirve para detectar fugas de memoria

// Convención de nombres: s_ = variable global estática, _ = parámetro de función,
// a = array, pc = puntero a char, n = tamaño/cantidad, u = unsigned

// Un array de punteros: cada elemento guarda la dirección donde empieza una cadena ("Hola", "Adios"...).
// Los [] después del nombre son los que dicen que es un array (al profe se le olvidaron en el enunciado).
const char* s_apcCadenas[] =
{
	"Hola",
	"Adios",
	"Otra cadena",
	"Wahahahahahaha"
};

// Número de cadenas de la tabla: tamaño total del array entre tamaño de un elemento.
// Es mejor que escribir sizeof(const char*) porque, si cambia el tipo de la tabla, esto se ajusta solo.
size_t s_nCadenas = sizeof(s_apcCadenas) / sizeof(s_apcCadenas[0]);

// Devuelve la cadena que está en esa posición (0 sería "Hola", 1 sería "Adios", etc.)
const char* GetCadena(unsigned int _uIndice)
{
	if (_uIndice < s_nCadenas) // Comprueba que el índice existe (si no, leeríamos memoria que no es de la tabla)
	{
		return s_apcCadenas[_uIndice];
	}
	return nullptr; // nullptr significa "no hay cadena". Quien llame a la función debería comprobarlo antes de usar el
	// resultado
}

/*
//Primer intento(lo dejo como recordatorio de lo que hay que evitar) : reservaba memoria con new dentro de la
//función, y quien la llamase tenía que acordarse de hacer delete[]. Si se olvida, hay una fuga de memoria.
char* GetCadenaInvertida(unsigned int _uIndice)
{
	size_t nCadenas = sizeof(s_apcCadenas) / sizeof(s_apcCadenas[0]);
	if (_uIndice < nCadenas)
	{
		size_t nLongitud = strlen(s_apcCadenas[_uIndice]);
		size_t nBytes = nLongitud + 1;
		char* pcCopia = new char[nBytes]; // <-- Este era el problema
		strcpy_s(pcCopia, nBytes, s_apcCadenas[_uIndice]);
		if (nLongitud < 2)
		{
			return pcCopia;
		}
		char* pcInicio = pcCopia;
		char* pcFin = pcInicio + nLongitud - 1;
		while (pcInicio < pcFin)
		{
			char cTemp = *pcInicio;
			*pcInicio = *pcFin;
			*pcFin = cTemp;
			++pcInicio;
			--pcFin;
		}
		return pcCopia;
	}
	return nullptr;
}
 */

// Versión buena: no reserva memoria. Quien la llama pone el sitio donde guardar el resultado (_pcBuffer)
// y su tamaño (_uBufferSize). Devuelve true si ha podido hacerlo y false si no.
bool GetCadenaInvertida(unsigned int _uIndice, char* _pcBuffer, unsigned int _uBufferSize)
{
	if (_uIndice < s_nCadenas) // Comprueba que el índice existe
	{
		size_t nLongitud = strlen(s_apcCadenas[_uIndice]); // Longitud de la cadena, sin contar el '\0' final

		// Tiene que caber la cadena y además el '\0', por eso el buffer debe ser MAYOR que la longitud
		if (_uBufferSize > nLongitud)
		{
			for (unsigned int uPosicion = 0; uPosicion < nLongitud; ++uPosicion)
			{
				// Copia el carácter de atrás hacia delante. Con uPosicion = 0 queremos el último carácter
				// (el de la posición nLongitud - 1), porque la posición nLongitud es el '\0'
				_pcBuffer[uPosicion] = s_apcCadenas[_uIndice][nLongitud - 1 - uPosicion];
			}
			_pcBuffer[nLongitud] = '\0'; // Marca el final de la cadena; sin esto printf no sabría dónde parar
			return true;
		}
	}
	return false; // El índice no existe o la cadena no cabe en el buffer
}

int main()
{
	// Al cerrar el programa, Visual Studio escribe en la ventana Salida si ha quedado memoria sin liberar
	// y dónde se reservó
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	printf("Cadena %d es: %s\n\n", 3, GetCadena(3));

	//char* pcInvertida = GetCadenaInvertida(3);
	//if (pcInvertida)
	//{
	//	printf("Cadena %d invertida es: %s\n\n", 3, pcInvertida);
	//	delete[] pcInvertida; // Hay que liberarla a mano, y es fácil olvidarse
	//	pcInvertida = nullptr;
	//}

	char acBuffer[128]; // El sitio donde se guardará la cadena invertida (vive en main, se libera sola)
	if (GetCadenaInvertida(3, acBuffer, 128))
	{
		printf("Cadena %d invertida es: %s\n\n", 3, acBuffer);
	}
	return 0;
}