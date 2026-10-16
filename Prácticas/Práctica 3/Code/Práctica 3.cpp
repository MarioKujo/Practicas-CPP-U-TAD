/*
1 Dada una tabla de cadenas, hacer una función que, dado un índice, retorne la cadena de ese índice si existe.

2 Hacer una función que, dado un índice a la tabla de cadenas, retorne la cadena de ese índice, si existe, invertida.
*/
#include <iostream>
#include <crtdbg.h>

const char* s_tTablaDeCadenas[] =
{
	"Hola",
	"Adios",
	"Otra cadena",
	"Wahahahahahaha"
};

const char* GetCadena(unsigned int _uIndex)
{
	size_t size = sizeof(s_tTablaDeCadenas) / sizeof(s_tTablaDeCadenas[0]);
	if (_uIndex < size)
	{
		return s_tTablaDeCadenas[_uIndex];
	}
	else
	{
		return nullptr;
	}
}

//char* GetCadenaInvertida(unsigned int _uIndex)
//{
//	size_t size = sizeof(s_tTablaDeCadenas) / sizeof(s_tTablaDeCadenas[0]);
//	if (_uIndex < size)
//	{
//		size_t cadenaSize = strlen(s_tTablaDeCadenas[_uIndex]);
//		size_t bytes = cadenaSize + 1;
//		char* cadenaCopia = new char[bytes];
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

size_t s_uTablaCadenasSize = sizeof(s_tTablaDeCadenas) / sizeof(const char*);

bool GetCadenaInvertida(unsigned int _uIndex, char* _sBuffer, unsigned int _uBufferSize)
{
	if (_uIndex < s_uTablaCadenasSize)
	{
		size_t uSizeCadena = strlen(s_tTablaDeCadenas[_uIndex]);
		if (_uBufferSize > uSizeCadena)
		{
			for (unsigned int uIndex = 0;uIndex < uSizeCadena;++uIndex)
			{
				_sBuffer[uIndex] = s_tTablaDeCadenas[_uIndex][uSizeCadena - 1 - uIndex];
			}
			_sBuffer[uSizeCadena] = '\0';
			return true;
		}
	}
	return false;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//StackOverflow1();
	//StackOverflow2();
	printf("Cadena %d es: %s\n\n", 3, GetCadena(3));
	//char* invertida = GetCadenaInvertida(3);
	//if(invertida)
	//{
	//	printf("Cadena %d invertida es: %s\n\n", 3, invertida);
	//	delete[]invertida;
	//	invertida = nullptr;
	//}
	char buffer[128];
	if (GetCadenaInvertida(3, buffer, 128))
	{
		printf("Cadena %d invertida es: %s\n\n", 3, buffer);
	}
	return 0;
}