/*
1 Dada una tabla de cadenas, hacer una función que, dado un índice, retorne la cadena de ese índice si existe.

2 Hacer una función que, dado un índice a la tabla de cadenas, retorne la cadena de ese índice, si existe, invertida.
*/
#include <iostream>
#include <crtdbg.h>

const char* s_tTablaDeCadenas[] = // Al profe le faltó poner los corchetes []
{
	"Hola",
	"Adios",
	"Otra cadena",
	"Wahahahahahaha"
};
size_t s_uTablaCadenasSize = sizeof(s_tTablaDeCadenas) / sizeof(s_tTablaDeCadenas[0]);
// es como hacer sizeof (s_tTablaDeCadenas)/ sizeof(const char*), pero mejor, porque s_tTablaDeCadenas podría ser
// cualquier otra variable

const char* GetCadena(unsigned int _uIndex) // Recibe la cadena del índice (0 sería "Hola", 1 sería "Adios", etc)
{
	if (_uIndex < s_uTablaCadenasSize) // Si está dentro de los confines del universo -digo- del array de cadenas, lo devuelve
	{
		return s_tTablaDeCadenas[_uIndex];
	}
		return nullptr; // Si no te jodes
}

//char* GetCadenaInvertida(unsigned int _uIndex)
//{
//	size_t size = sizeof(s_tTablaDeCadenas) / sizeof(s_tTablaDeCadenas[0]);
//	if (_uIndex < size)
//	{
//		size_t cadenaSize = strlen(s_tTablaDeCadenas[_uIndex]);
//		size_t bytes = cadenaSize + 1;
//		char* cadenaCopia = new char[bytes]; // <-- Este era el problema, lo dejo como testimonio de lo que podría
// haber sido y saber qué evitar
//		strcpy_s(cadenaCopia, bytes, s_tTablaDeCadenas[_uIndex]);
//		if (cadenaSize < 2)
//		{
//			return cadenaCopia;
//		}
//		char* inicio = cadenaCopia;
//		char* fin = inicio + cadenaSize - 1;
//		while (inicio < fin)
//		{
//			char temp = *inicio;
//			*inicio = *fin;
//			*fin = temp;
//			++inicio;
//			--fin;
//		}
//		return cadenaCopia;
//	}
//		return nullptr;
//}


bool GetCadenaInvertida(unsigned int _uIndex, char* _sBuffer, unsigned int _uBufferSize) // Recibe el índice, un sitio
// donde guardarla y el tamaño del buffer (dónde la guarda)
{
	if (_uIndex < s_uTablaCadenasSize) // Si está dentro del array
	{
		size_t uSizeCadena = strlen(s_tTablaDeCadenas[_uIndex]); // Pilla el tamaño (OJO) de LA CADENA
		if (_uBufferSize > uSizeCadena) // Si cabe en el buffer
		{
			for (unsigned int uIndex = 0;uIndex < uSizeCadena;++uIndex)
			{
				_sBuffer[uIndex] = s_tTablaDeCadenas[_uIndex][uSizeCadena - 1 - uIndex]; // La invierte (-1 para que a
				// la primera tirada pille el último caracter y no '\0')
			}
			_sBuffer[uSizeCadena] = '\0'; // Se lo añade a la fuerza (porsiaca)
			return true;
		}
	}
	return false; // Si no cabe en el buffer del otro lado, te jodes! :D
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Te deja un log abajo del todo (Salida/Exit) si hay una fuga de memoria (Memory Leak!) y te dice dónde

	printf("Cadena %d es: %s\n\n", 3, GetCadena(3));
	//char* invertida = GetCadenaInvertida(3);
	//if(invertida)
	//{
	//	printf("Cadena %d invertida es: %s\n\n", 3, invertida);
	//	delete[]invertida; // Demencial
	//	invertida = nullptr;
	//}
	char buffer[128];
	if (GetCadenaInvertida(3, buffer, 128))
	{
		printf("Cadena %d invertida es: %s\n\n", 3, buffer);
	}
	return 0;
}