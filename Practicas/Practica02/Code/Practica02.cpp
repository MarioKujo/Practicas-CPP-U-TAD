/*
1 Dado un entero, obtener por separado cada uno de sus bytes con «casting» y aritmética de punteros. Probarlo con 0x00FF0002: ¿por qué salen en el orden 02 00 FF 00 ?

- Se imprime al revés porque los bytes se recorren de final a inicio (de derecha a izquierda), lo que viene a ser
"little endian"

2 Dada int aTabla[] = { 1, 3, 2, 5, 3, static_cast<int>(0xFFFFFFFF), 0x00FF0002, 2 }; obtener el entero mayor con un puntero y aritmética de punteros.¿Por qué 0xFFFFFFFF no es el mayor?

- 0xFFFFFFFF no es el mayor porque en un int con signo ese patrón de bits no vale 4.294.967.295, vale -1

3 Como el anterior, pero obtener el byte mayor(usar casting) y la posición en bytes donde aparece por primera vez.Recorrerla con char* y con unsigned char* : ¿coinciden ? ¿Por qué ?

- char y unsigned char no coinciden porque signed char va de -128 a 127 y unsigned char va de 0 a 255, y el byte FF
	es 255, el cual no entra en signed char, por lo que el valor se le queda en -1

4 Dada una cadena de caracteres, darle la vuelta.
*/
#include <iostream>

// Convención de nombres: p = puntero, a = array, n = tamaño/cantidad, u = unsigned, c = char
// Ejemplos: pcInicio = puntero a char, pucByte = puntero a unsigned char, aTabla = array

void IntBytes(const unsigned int uValor)
{
	// Un puntero es una variable que, en vez de guardar un número normal, guarda una DIRECCIÓN de memoria
	// (el "número de casilla" donde vive un dato). &uValor significa "la dirección de uValor".
	// Un int ocupa 4 bytes seguidos en memoria. Para poder mirarlos de uno en uno, usamos un puntero que
	// avanza de 1 en 1 byte (unsigned char*) y con reinterpret_cast le decimos al compilador:
	// "trata esa dirección como si fueran bytes sueltos".
	const unsigned char* pucByte = reinterpret_cast<const unsigned char*>(&uValor);
	for (size_t nIndice = 0; nIndice < sizeof(uValor); nIndice++) // Una vuelta por cada byte (4 en un int)
	{
		// Sumarle un número a un puntero lo hace avanzar ESA cantidad de elementos de su tipo. Como unsigned char
		// mide 1 byte, (pucByte + 1) es "la dirección del byte siguiente", (pucByte + 2) la del siguiente, etc.
		// El * de delante significa "dame lo que hay guardado en esa dirección".
		// %02X imprime el valor en hexadecimal con 2 dígitos.
		printf("Byte %zu: %02X\n\n", nIndice, *(pucByte + nIndice));
	}
}

template<size_t N> // Así la función sabe cuántos elementos tiene el array (N), sin pasárselo a mano
int Mayor(const int(&aTabla)[N])
{
	const int* piMayor = aTabla; // Un array "es" la dirección de su primer elemento, así que apunta al principio
	const int* const piFin = aTabla + N; // Dirección JUSTO DESPUÉS del último elemento (no se lee nunca, solo marca el final)

	for (const int* piActual = aTabla + 1; piActual != piFin; ++piActual) // Empieza en el 2º elemento, porque el 1º ya
		// es el "mayor" de momento
	{
		if (*piActual > *piMayor) // Compara los VALORES (con el *), no las direcciones
		{
			// Sin asterisco cambiamos A QUÉ DIRECCIÓN apunta piMayor (ahora apunta al nuevo mayor).
			// Con asterisco (*piMayor = *piActual) estaríamos machacando el valor guardado en el array.
			piMayor = piActual;
		}
	}
	return *piMayor;
}

// Igual que en Mayor: N lo deduce el compilador a partir del array, así que siempre es el tamaño real
template<size_t N>
const char* ByteMayorSigned(const int(&aTabla)[N])
{
	// Pasamos de "puntero a int" (avanza de 4 en 4 bytes) a "puntero a char" (avanza de 1 en 1 byte)
	const char* const pcInicio = reinterpret_cast<const char*const >(aTabla);
	const char* pcMayor = pcInicio; // De momento el mayor es el primer byte

	// El array tiene N ints y cada int ocupa sizeof(int) bytes (4), así que en total son N * 4 bytes.
	// Sumándolo al inicio llegamos a la dirección justo después del último byte (no se lee, solo marca el final)
	const char* const pcFin = pcInicio + N * sizeof(int);

	for (const char* pcActual = pcInicio + 1; pcActual != pcFin; ++pcActual) // Recorre byte a byte
	{
		if (*pcActual > *pcMayor)
		{
			pcMayor = pcActual; // Igual que en Mayor: movemos el puntero, no tocamos los valores
		}
	}
	return pcMayor;
}

// Idéntica a la anterior, pero con unsigned char: aquí el byte FF vale 255 y no -1
template<size_t N>
const unsigned char* ByteMayorUnsigned(const int(&aTabla)[N])
{
	const unsigned char* const pucInicio = reinterpret_cast<const unsigned char*>(aTabla);
	const unsigned char* pucMayor = pucInicio;
	const unsigned char* const pucFin = pucInicio + N * sizeof(int);

	for (const unsigned char* pucActual = pucInicio + 1; pucActual != pucFin; ++pucActual)
	{
		if (*pucActual > *pucMayor)
		{
			pucMayor = pucActual;
		}
	}
	return pucMayor;
}

// AVISO: FUGA DE MEMORIA. EL QUE LA LLAME TIENE QUE HACER DELETE[]

char* InvertirFuga(const char* pcCadena) // Devuelve la cadena invertida
{
	size_t nLongitudCopia = strlen(pcCadena) + 1; // +1 para el '\0', el carácter invisible que marca el final de una
	// cadena
	// new reserva memoria que NO se libera sola al salir de la función; quien reciba el puntero debe hacer delete[]
	char* const pcInvertida = new char[nLongitudCopia];
	strcpy_s(pcInvertida, nLongitudCopia, pcCadena);
	pcInvertida[nLongitudCopia] = '\0'; // Lo de siempre, para marcar el final (necesario)
	const size_t nLongitud = strlen(pcCadena); // Longitud real (sin el '\0')
	if (nLongitud < 2) // Si mide 0 o 1 no se puede hacer nada
	{
		return pcInvertida;
	}

	char* pcInicio = pcInvertida; // Apunta al primer carácter

	char* pcFinal = pcInvertida + nLongitud - 1;// Apunta al último carácter. Si le sumáramos nLongitud entera caeríamos
	// en el '\0', por eso el -1

	// Intercambia el primero con el último, luego el segundo con el penúltimo, etc., acercándose
	// desde los dos extremos hasta que los punteros se cruzan
	while (pcInicio < pcFinal)
	{
		char cTemp = *pcInicio;
		*pcInicio = *pcFinal;
		*pcFinal = cTemp;
		++pcInicio; // Avanza un carácter hacia la derecha
		--pcFinal; // Retrocede un carácter hacia la izquierda
	}
	return pcInvertida;
}

void Invertir(const char* pcOrigen, char* pcDestino)
{
	const char* pcFin = pcOrigen + strlen(pcOrigen); // Apunta al '\0' del final

	while (pcFin > pcOrigen)
	{
		// --pcFin retrocede ANTES de leer (si no, leeríamos el '\0'). Así copiamos la cadena de atrás hacia delante.
		*pcDestino = *--pcFin;
		++pcDestino;
	}
	*pcDestino = '\0';
}

int main()
{
	unsigned int uNumero = 0x00FF0002;

	IntBytes(uNumero);

	const int aTabla[] = { 1, 3, 2, 5, 3, static_cast<int>(0xFFFFFFFF), 0x00FF0002, 2 };

	printf("El numero mayor es %d\n\n", Mayor(aTabla));


	const char* pcMayor = ByteMayorSigned(aTabla);

	const char* const pcInicio = reinterpret_cast<const char*>(aTabla);

	// Restar dos punteros da cuántos elementos hay entre ellos; con char* eso son bytes, o sea, la posición
	printf("Byte mayor (signed): %d en la posicion %td\n\n", *pcMayor, pcMayor - pcInicio);


	const unsigned char* pucMayor = ByteMayorUnsigned(aTabla);

	const unsigned char* const pucInicio = reinterpret_cast<const unsigned char*>(aTabla);

	printf("Byte mayor (unsigned): %d en la posicion %td\n\n", *pucMayor, pucMayor - pucInicio);

	const char acOriginal[] = "Hola";
	char acInversa[100];
	Invertir(acOriginal, acInversa);

	printf("acInversa es: %s\n", acInversa);

	printf("acOriginal (no se ha modificado): %s\n", acOriginal);
	return 0;
}