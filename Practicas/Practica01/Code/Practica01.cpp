/*
Un personaje en 32 bits
Realizar funciones que, dado ese entero(unsigned int):
- Devuelvan el número de balas.
- Añadan balas a las existentes (como máximo 255, sin tocar los demás campos)
- Devuelvan si está activo el modo de balas infinitas.
- Activen el modo de balas infinitas.
*/
#include <iostream>

// Una máscara es un número que vale 1 solo en los bits que nos interesan y 0 en el resto.
// Con ella podemos leer o modificar esos bits sin tocar los demás.
#define MASK_BALAS 0x00FF0000 // 0000 0000 1111 1111 0000 0000 0000 0000 <-- los 8 bits donde están las balas
#define MASK_2     0x00000002 // 0000 0000 0000 0000 0000 0000 0000 0010 <-- el bit del modo "balas infinitas"

unsigned int NumBalas(unsigned int _uData)
{
	// Las balas están en el "medio" del número, pero para leerlas como un número normal
	// tienen que acabar pegadas a la derecha. Lo conseguimos con dos desplazamientos (<< y >>).
	// Los bits que se salen por un lado desaparecen, y por el otro entran ceros.

	// 1000 1110 0010 0101 0010 0000 0000 0100 <-- _uData
	// 0000 0000 1111 1111 0000 0000 0000 0000 <-- Balas (esto es lo que queremos)

	// Primero desplazamos 8 bits a la izquierda: los 8 bits de vida (los de más a la izquierda) se salen y desaparecen
	unsigned int uTemp = _uData << 8;

	// 0010 0101 0010 0000 0000 0100 0000 0000 <-- _uData << 8 (valores reales)
	// 1111 1111 0000 0000 0000 0000 0000 0000 <-- Balas << 8 (ya están pegadas a la izquierda)

	// Ahora desplazamos 24 a la derecha: los bits de después de las balas se salen y desaparecen
	uTemp >>= 24;

	// 0000 0000 0000 0000 0000 0000 0010 0101 <-- (_uData << 8) >> 24 (valores reales, 0x25 = 37 balas)
	// 0000 0000 0000 0000 0000 0000 1111 1111 <-- (Balas << 8) >> 24 (sí, son 24 ceros, no hace falta que los cuentes).
	// Ahora las balas están a la derecha del todo, así que el número vale justo lo que hay en esos 8 bits.

	return uTemp;
}

unsigned int AddBalas(unsigned int _uMask, int _balasToAdd)
{
	// Primero leemos las balas actuales con la función de arriba (aquí valen 0x25 = 37)
	unsigned int uNumBalas = NumBalas(_uMask);

	uNumBalas += _balasToAdd;

	// Con 8 bits solo caben hasta 255. Si nos pasamos, lo dejamos en el máximo
	if (uNumBalas > 255)
	{
		uNumBalas = 255;
	}

	// Colocamos el nuevo número de balas en su sitio (8 bits a la izquierda de donde están las balas son 16 posiciones).
	// Ejemplo con 37 + 20 = 57 (0x39):
	// 0000 0000 0011 1001 0000 0000 0000 0000 <-- uNumBalas << 16

	uNumBalas <<= 16;

	// Antes de escribir las balas nuevas hay que borrar las viejas, si no se mezclarían.
	// ~ invierte todos los bits de la máscara: ceros donde están las balas y unos en todo lo demás.
	// 1111 1111 0000 0000 1111 1111 1111 1111 <-- ~MASK_BALAS

	// Al hacer AND con ese valor se conserva todo lo demás y las balas quedan a cero
	unsigned int newMask = _uMask & ~MASK_BALAS;

	// 1000 1110 0000 0000 0010 0000 0000 0100 <-- Así queda de momento (vuelven los valores, balas está a cero)
	// 0000 0000 0011 1001 0000 0000 0000 0000 <-- Ahí van las balas sumadas
	// --------------------------------------- OR (es 1 si alguno de los dos es 1)

	newMask |= uNumBalas;

	// 1000 1110 0011 1001 0010 0000 0000 0100 <-- Resultado: solo han cambiado las balas

	return newMask;
}

bool BalasInfinitas(unsigned int _uMask)
{
	// Con un AND solo sobrevive el bit que queremos mirar; todos los demás se ponen a cero.
	// Si el resultado es 0, el bit estaba apagado; si no es 0, estaba encendido.

	// 1000 1110 0010 0101 0010 0000 0000 0100 <-- uMask
	// 0000 0000 0000 0000 0000 0000 0000 0010 <-- MASK_2
	// --------------------------------------- <-- AND (solo es 1 si ambos son 1)
	// 0000 0000 0000 0000 0000 0000 0000 0000 <-- Falso (todo ceros)

	// 1000 1110 0010 0101 0010 0000 0000 0110 <-- uMask
	// 0000 0000 0000 0000 0000 0000 0000 0010 <-- MASK_2
	// --------------------------------------- <-- AND (solo es 1 si ambos son 1)
	// 0000 0000 0000 0000 0000 0000 0000 0010 <-- Verdadero (hay algún 1)

	// El resultado es un número (0 o 2), pero al devolverlo como bool se convierte solo: 0 es false y cualquier otro
	// valor es true
	return _uMask & MASK_2;
}

unsigned int ActivarBalasInfinitas(unsigned int _uMask)
{
	// Con un OR se enciende el bit que queremos y el resto se queda como estaba
	// (si ya estaba encendido, no pasa nada)

	// 1000 1110 0010 0101 0010 0000 0000 0100 <-- uMask
	// 0000 0000 0000 0000 0000 0000 0000 0010 <-- MASK_2
	// --------------------------------------- <-- OR (es 1 si alguno de los dos es 1)
	// 1000 1110 0010 0101 0010 0000 0000 0110 <-- uMask | MASK_2
	return _uMask | MASK_2;
}

int main()
{
	// LIFE = 142 (8E)
	// BALAS = 37 (25)
	// COMPAÑEROS = 2 (200)
	unsigned int uData = 0x8E252004; // Balas infinitas desactivadas (bit 0x2 apagado) y escudo activado (el 4 del final)

	printf("Numero de balas = %d\n\n", NumBalas(uData));

	uData = AddBalas(uData, 20);

	printf("Numero de balas = %d\n\n", NumBalas(uData));

	printf("Balas infinitas esta %s\n\n", BalasInfinitas(uData) ? "activo" : "inactivo");

	uData = ActivarBalasInfinitas(uData);

	printf("Balas infinitas esta %s\n\n", BalasInfinitas(uData) ? "activo" : "inactivo");

	return 0;
}