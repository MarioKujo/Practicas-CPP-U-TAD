/*
Un personaje en 32 bits
Realizar funciones que, dado ese entero(unsigned int):
- Devuelvan el número de balas.
- Añadan balas a las existentes (como máximo 255, sin tocar los demás campos)
- Devuelvan si está activo el modo de balas infinitas.
- Activen el modo de balas infinitas.
*/
#include <iostream>
#define MASK_BALAS 0x00FF0000
#define MASK_2 0x00000002 // 0000 0000 0000 0000 0000 0000 0000 0010 <-- la verdadera máscara

unsigned int NumBalas(unsigned int _uData)
{
	// 1000 1110 0010 0101 0010 0000 0000 0100 <-- uMask
	// 0000 0000 1111 1111 0000 0000 0000 0000 <-- Balas

	unsigned int uTemp = _uData << 8;

	// 0010 0101 0010 0000 0000 0100 0000 0000 <-- uMask << 8 (valores reales)
	// 1111 1111 0000 0000 0000 0000 0000 0000 <-- Balas << 8 (desecha los 8 bits de vida)

	uTemp >>= 24;

	// 0000 0000 0000 0000 0000 0000 0010 0101 <-- (uMask << 8) >> 24 (valores reales)
	// 0000 0000 0000 0000 0000 0000 1111 1111 <-- (Balas << 8) >> 24 (sí, son 24 ceros, no hace falta que los cuentes).
	// Tienen que estar a la derecha del todo para poder ser leídos correctamente.

	return uTemp;
}

unsigned int AddBalas(unsigned int _uMask, int _balasToAdd)
{
	// 1000 1110 0010 0101 0010 0000 0000 0100 <-- uMask
	// 0010 0101 0010 0000 0000 0100 0000 0000 <-- uMask << 8
	// 0000 0000 0000 0000 0000 0000 0010 0101 <-- (uMask << 8) >> 24

	unsigned int uNumBalas = NumBalas(_uMask);

	uNumBalas += _balasToAdd;

	if (uNumBalas > 255)
	{
		uNumBalas = 255;
	}

	// 0000 0000 0010 0110 0000 0000 0000 0000 <-- ((uMask << 8) >> 24) << 16

	uNumBalas <<= 16;

	// 1111 1111 0000 0000 1111 1111 1111 1111 <-- ~MASK_BALAS (primero tengo que borrarlo de la máscara original)

	unsigned int newMask = _uMask & ~MASK_BALAS;

	// 1000 1110 0000 0000 0010 0000 0000 0100 <-- Así queda de momento (vuelven los valores, balas está a cero)
	// 0000 0000 0010 0110 0000 0000 0000 0000 <-- Ahí van las balas sumadas
	// --------------------------------------- OR

	newMask |= uNumBalas;

	return newMask;
}

bool BalasInfinitas(unsigned int _uMask)
{
	// 1000 1110 0010 0101 0010 0000 0000 0100 <-- uMask
	// 0000 0000 0000 0000 0000 0000 0000 0010 <-- MASK_2
	// --------------------------------------- <-- AND (solo es 1 si ambos son 1)
	// 0000 0000 0000 0000 0000 0000 0000 0000 <-- Falso

	// 1000 1110 0010 0101 0010 0000 0000 0110 <-- uMask
	// 0000 0000 0000 0000 0000 0000 0000 0010 <-- MASK_2
	// --------------------------------------- <-- AND (solo es 1 si ambos son 1)
	// 0000 0000 0000 0000 0000 0000 0000 0010 <-- Verdadero

	return _uMask & MASK_2;
}

unsigned int ActivarBalasInfinitas(unsigned int _uMask)
{
	// 1000 1110 0010 0101 0010 0000 0000 0100 <-- uMask
	// 0000 0000 0000 0000 0000 0000 0000 0010 <-- MASK_2
	// ---- ---- ---- ---- ---- ---- ---- ---- <-- OR
	// 1000 1110 0010 0101 0010 0000 0000 0110 <-- uMask | MASK_2
	return _uMask | MASK_2;
}

int main()
{
	// LIFE = 142 (8E)
	// BALAS = 37 (25)
	// COMPAÑEROS = 2 (200)
	unsigned int uData = 0x8E252004; // con balas inactivas y escudo (último 4)

	printf("Numero de balas = %d\n\n", NumBalas(uData));

	uData = AddBalas(uData, 20);

	printf("Numero de balas = %d\n\n", NumBalas(uData));

	printf("Balas infinitas esta %s\n\n", BalasInfinitas(uData) ? "activo" : "inactivo");

	uData = ActivarBalasInfinitas(uData);

	printf("Balas infinitas esta %s\n\n", BalasInfinitas(uData) ? "activo" : "inactivo");

	return 0;
}