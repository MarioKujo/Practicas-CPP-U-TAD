/*
1 Dado un entero, obtener por separado cada uno de sus bytes con «casting» y aritmética de punteros.Probarlo con 0x00FF0002: ¿por qué salen en el orden 02 00 FF 00 ?

2 Dada int tabla[] = { 1, 3, 2, 5, 3, static_cast<int>(0xFFFFFFFF), 0x00FF0002, 2 }; obtener el entero mayor con un puntero y aritmética de punteros.¿Por qué 0xFFFFFFFF no es el mayor?
3 Como el anterior, pero obtener el byte mayor(usar casting) y la posición en bytes donde aparece por primera vez.Recorrerla con char* y con unsigned char* : ¿coinciden ? ¿Por qué ?
4 Dada una cadena de caracteres, darle la vuelta.
*/
#include <iostream>

void IntBytes(unsigned int _int) // Unsigned int para que quepan números más grandes, no por otra cosa
{
	unsigned char* p = reinterpret_cast<unsigned char*>(&_int); // Lo reinterpreta a char (1 byte)
	for (size_t i = 0; i < sizeof(_int); i++) // Itera para cada byte
	{
		printf("Byte %zu: %02X\n\n", i, *(p + i)); // Lo imprime en formato hexadecimal(%02X). *(p + i) porque le añade 
		// su mismo tamaño en memoria, entonces *(p + 0) avanzará 0 bytes respecto al puntero y estará apuntando al
		// primer byte,*(p + 1) avanzará 1 byte respecto al puntero y estará apuntando al segundo byte, *(p + 2)
		// avanzará 2 bytes respecto al puntero y estará apuntando al tercer byte, etc
	}
	// Se imprime al revés porque los bytes se recorren de final a inicio (de derecha a izquierda), lo que viene a ser
	// "little endian"
}

template<size_t N> // Para tener el tamaño del array, no hay otra manera de sacarlo
int Mayor(const int(&tabla)[N])
{
	const int* mayor = tabla; // Apunta al principio
	const int* fin = tabla + N; // Apunta al final (justo el problema es ese N, que no hay otra manera de sacarle el
	// tamaño si queremos que sean const para no modificar nada de la tabla y recibirla por referencia, no por copia

	for (const int* slider = tabla + 1; slider != fin; ++slider) // Ya que el mayor es la primera posición, se lo puede
		// saltar
	{
		if (*slider > *mayor)
		{
			mayor = slider; // Se explica por sí solo: si el número es mayor, se pone como el mayor
		}
	}
	return *mayor;
	// 0xFFFFFFFF no es el mayor porque en un int con signo ese patrón de bits no vale 4.294.967.295, vale -1
}

const char* ByteMayorSigned(const int* tabla) // Aquí sí se puede sacar bien el tamaño
{
	size_t n = sizeof(tabla); // Se saca a un size_t
	const char* inicio = reinterpret_cast<const char*>(tabla); // Se reinterpreta de const int* a const char* para poder
	// iterar entre los bits
	const char* mayor = inicio; // Primera posición (me salto una iteración)
	const char* fin = inicio + n * sizeof(int); // Aquí si puede ser sizeof(int), ya que, como const char* es de 1 byte
	// e int de 4, al multiplicar size * 4 te aseguras de que esté apuntando realmente a la verdadera posición fuera del 
	// array (donde suele estar el caracter de salida '\0')

	for (const char* slider = inicio + 1; slider != fin; ++slider) // Volvemos a iterar
	{
		if (*slider > *mayor)
		{
			mayor = slider; // Igual que el de arriba
		}
	}
	return mayor;
}

const unsigned char* ByteMayorUnsigned(const int* tabla) // Lo mismo que arriba pero con unsigned char*
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
	// char y unsigned char no coinciden porque signed char va de -128 a 127 y unsigned char va de 0 a 255, y el byte FF 
	// es 255, el cual no entra en signed char, por lo que el valor se le queda en -1
}

char* Invertir(const char* cadena) // Devuelve la cadena invertida 
{
	size_t longitudCopia = strlen(cadena) + 1;
	char* invertida = new char[longitudCopia]; // AVISO: FUGA DE MEMORIA. EL QUE LA LLAME TIENE QUE HACER DELETE[]
	strcpy_s(invertida, longitudCopia, cadena);
	invertida[longitudCopia] = '\0'; // Lo de siempre, para marcar el final (necesario)
	size_t longitud = strlen(cadena); // Longitud real (sin el '\0')
	if (longitud < 2) // Si mide 0 o 1 no se puede hacer nada
	{
		return invertida;
	}

	char* inicio = invertida; // Apunta al primer byte
	char* final = invertida + longitud - 1; // Apunta al último byte escrito del array (-1 porque final empieza
	// apuntando al primer byte del array, entonces si le suma longitud entera, apunta al '\0')

	while (inicio < final)
	{
		char temp = *inicio;
		*inicio = *final;
		*final = temp;
		++inicio;
		--final;
	}// Creo que se entiende
	return invertida;
}

int main()
{
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
	char* pInvertida = Invertir(cInversa);
	printf("%s\n", pInvertida);
	delete[]pInvertida;
	pInvertida = nullptr;
	printf("cInversa normal (no se ha modificado): %s\n", cInversa);
	return 0;
}