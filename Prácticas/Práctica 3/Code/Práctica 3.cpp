/*
1 Dada una tabla de cadenas, hacer una función que, dado un índice, retorne la cadena de ese índice si existe.

2 Hacer una función que, dado un índice a la tabla de cadenas, retorne la cadena de ese índice, si existe, invertida.
*/
#include <iostream>
#include <crtdbg.h>

#pragma region MiniPracticas
/*
void StackOverflow1(int n)
{
	char relleno[1024];
	relleno[0] = (char)n;          // evita que se optimice fuera
	printf("%d %d\n", n, relleno[0]);
	StackOverflow1(n + 1);
}
*/

/*
void StackOverflow2()
{
	char buffer[2 * 1024 * 1024];   // 2 MB en la pila
	buffer[0] = 1;
	printf("%d\n", buffer[0]);
}
*/

/*
char* GetGreeting()
{
	char t[] = "Hola";
	return t; // Sólo vive en el frame de la función. Al devolverlo, apunta a basura
}
*/

/*
// Escribir una función que reciba una variable int y le asigne un valor.
void ChangeValueRef(int& rValue)
{
	rValue = 5;
}
*/

/*
// Lo mismo, pero recibiendo un puntero a un int.
void ChangeValuePointer(int* pValue)
{
	*pValue = 5;
}
*/

/*
// ¿Cómo haríamos para pasar un puntero y que nos lo rellenen con la dirección de una variable?
void FillPointer(int*& pointer, int& toPoint)
{
	pointer = &toPoint;
}

// ¿Qué dos opciones tenemos?
void FillDoublePointer(int** pointer, int& toPoint)
{
	*pointer = &toPoint;
}
*/
#pragma endregion

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

char* GetCadenaInvertida(unsigned int _uIndex)
{
	size_t size = sizeof(s_tTablaDeCadenas) / sizeof(s_tTablaDeCadenas[0]);
	if (_uIndex < size)
	{
		size_t cadenaSize = strlen(s_tTablaDeCadenas[_uIndex]);
		size_t bytes = cadenaSize + 1;
		char* cadenaCopia = new char[bytes];
		strcpy_s(cadenaCopia, bytes, s_tTablaDeCadenas[_uIndex]);
		if (cadenaSize < 2)
		{
			return cadenaCopia;
		}
		char* inicio = cadenaCopia;
		char* fin = inicio + cadenaSize - 1;
		while (inicio < fin)
		{
			char temp = *inicio;
			*inicio = *fin;
			*fin = temp;
			++inicio;
			--fin;
		}
		return cadenaCopia;
	}
	else
	{
		return nullptr;
	}
}  

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//StackOverflow1();
	//StackOverflow2();
	printf("Cadena %d es: %s\n\n", 3, GetCadena(3));
	char* invertida = GetCadenaInvertida(3);
	if(invertida)
	{
		printf("Cadena %d invertida es: %s\n\n", 3, invertida);
		delete[]invertida;
		invertida = nullptr;
	}
	return 0;
}