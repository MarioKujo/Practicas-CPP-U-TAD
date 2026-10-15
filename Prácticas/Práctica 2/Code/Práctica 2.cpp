/*
1 Dado un entero, obtener por separado cada uno de sus bytes con «casting» y aritmética de punteros.Probarlo con 0x00FF0002: ¿por qué salen en el orden 02 00 FF 00 ?

2 Dada int tabla[] = { 1, 3, 2, 5, 3, static_cast<int>(0xFFFFFFFF), 0x00FF0002, 2 }; obtener el entero mayor con un puntero y aritmética de punteros.¿Por qué 0xFFFFFFFF no es el mayor?
3 Como el anterior, pero obtener el byte mayor(usar casting) y la posición en bytes donde aparece por primera vez.Recorrerla con char* y con unsigned char* : ¿coinciden ? ¿Por qué ?
4 Dada una cadena de caracteres, darle la vuelta.
*/
#include <iostream>
/*
Hacer un bucle que recorra la tabla sText y la imprima en la consola.
char sText[] = "Hola";
*/
void ImprimirTabla()
{
	char sText[] = "Hola";

	size_t uSize = strlen(sText);
	/*
	unsigned int uIndex = 0;
	while (sText[uIndex] != '\0')
	{
		printf("%c", sText[uIndex]);
		++uIndex;
	}*/
	for (unsigned int uIndex = 0; uIndex < uSize; ++uIndex)
	{
		printf("%c", sText[uIndex]);
	}
	printf("\n\n");
}
/*
1 Declarar una referencia a una variable y cambiarle el valor.

2 ¿Qué pasa si no inicializamos una referencia?

3 ¿Qué significa esta expresión? int &r = i, r2 = i2;
*/

/*
void Referencias()
{
	int i = 0;
	int i2 = 0;

	int& b = i;

	//int& b; // Error: tiene que tener una referencia a otra variable obligatoriamente

	int& r = i, r2 = i2; // r recibe una referencia de i, r2 recibe una copia del valor almacenado en i2
}
*/
void IntBytes(unsigned int _int)
{
	unsigned char* p = reinterpret_cast<unsigned char*>(&_int);
	for (size_t i = 0; i < sizeof(_int); i++)
	{
		printf("Byte %zu: %02X\n\n", i, *(p + i));
	}
	// Porque los bytes se recorren de final a inicio (de derecha a izquierda)
}

template<size_t N>
int Mayor(const int (&tabla)[N])
{
	const int* mayor = tabla;
	const int* fin = tabla + N;

	for (const int* slider = tabla + 1; slider != fin; ++slider)
	{
		if (*slider > *mayor)
		{
			mayor = slider;
		}
	}
	return *mayor;
	// Porque en un int con signo ese patrón de bits no vale 4.294.967.295, vale -1
}

const char* ByteMayorSigned(const int* tabla)
{
	size_t n = sizeof(tabla);
	const char* inicio = reinterpret_cast<const char*>(tabla);
	const char* mayor = inicio;
	const char* fin = inicio + n * sizeof(int);

	for (const char* slider = inicio + 1; slider != fin; ++slider)
	{
		if (*slider > *mayor)
		{
			mayor = slider;
		}
	}
	return mayor;
}

const unsigned char* ByteMayorUnsigned(const int* tabla)
{
	size_t n = sizeof(tabla);
	const unsigned char* inicio = reinterpret_cast<const unsigned char*>(tabla);
	const unsigned char* mayor = inicio;
	const unsigned char* fin = inicio + n * sizeof(int);

	for (const unsigned char* slider = inicio + 1; slider != fin; ++slider)
	{
		if (*slider > *mayor)
		{
			mayor = slider;
		}
	}
	return mayor;
	//No coinciden porque signed char va de -128 a 127 y unsigned char va de 0 a 255, y el byte FF es 255, el cual no entra en signed char, por lo que el valor se le queda en -1
}

char* Invertir(char* cadena)
{
	size_t longitud = strlen(cadena);
	if (longitud < 2)
	{
		return cadena;
	}

	char* inicio = cadena;
	char* final = cadena + longitud - 1;

	while (inicio < final)
	{
		char temp = *inicio;
		*inicio = *final;
		*final = temp;
		++inicio;
		--final;
	}
	return cadena;
}

int main()
{
	ImprimirTabla();
	unsigned int intAByte = 0x00FF0002;

	IntBytes(intAByte);

	int tabla[] = { 1, 3, 2, 5, 3, static_cast<int>(0xFFFFFFFF), 0x00FF0002, 2 };

	printf("El numero mayor es %d\n\n", Mayor(tabla));


	const char* sMayor = ByteMayorSigned(tabla);

	const char* inicio = reinterpret_cast<const char*>(tabla);

	printf("Byte mayor (signed): %d en la posicion %td\n\n", *sMayor, sMayor - inicio);


	const unsigned char* uMayor = ByteMayorUnsigned(tabla);

	const unsigned char* uInicio = reinterpret_cast<const unsigned char*>(tabla);

	printf("Byte mayor (unsigned): %d en la posicion %td\n\n", *uMayor, uMayor - uInicio);

	char cInversa[] = "Hola";

	printf("%s\n", Invertir(cInversa));

	return 0;
}