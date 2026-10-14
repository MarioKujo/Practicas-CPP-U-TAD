/*Un personaje en 32 bits
Realizar funciones que, dado ese entero(unsigned int):
- Devuelvan el número de balas.
- Añadan balas a las existentes (como máximo 255, sin tocar los demás campos)
- Devuelvan si está activo el modo de balas infinitas.
- Activen el modo de balas infinitas.*/
#include <iostream>

#define MASK_2 0x00000002
#define MASK_BALAS 0b00000000111111110000000000000000

bool EstaActivoElModoDeBalasInfinito(unsigned int _uMask)
{
	bool bEstaActivo = false;

	// 10001110001001010010000000000100 <- _uMask
	// 00000000000000000000000000000010 <- MASK_2
	// -------------------------------- AND
	// 00000000000000000000000000000000 -> bool FALSE!!!

	// 10001110001001010010000000000100 <- _uMask
	// 00000000000000000000000000000010 <- MASK_2
	// // -------------------------------- AND
	// 00000000000000000000000000000010 -> bool TRUE!!!

	bEstaActivo = _uMask & MASK_2;

	return bEstaActivo;
}

unsigned int ActivarBalasInfinitas(unsigned int _uMask)
{
	// 10001110001001010010000000000100 <- _uMask
	// 00000000000000000000000000000010 <- MASK_2
	// -------------------------------- OR
	// 10001110001001010010000000000110 

	// 10001110001001010010000000000100 <- _uMask
	// 00000000000000000000000000000010 <- MASK_2
	// // -------------------------------- OR
	// 10001110001001010010000000000110

	unsigned int uNewMask = _uMask | MASK_2;
	return uNewMask;
}

int GetNumeroBalas(unsigned int _uData)
{
	unsigned int uTemp = _uData << 8;
	uTemp = uTemp >> 24;

	// 10001110001001010010000000000100 <- _uMask
	// 00100101001000000000010000000000 <- << 8
	// 00000000000000000000000000100101 <- << 24

	return uTemp;
}

unsigned int AddBalas(unsigned int _uMask, int _iBalasToAdd)
{
	// 10001110001001010010000000000100 <- _uMask
	// 00100101001000000000010000000000 <- << 8
	// 00000000000000000000000000100101 <- << 24
	
	unsigned int uNumBalas = GetNumeroBalas(_uMask);

	// 00000000000000000000000000100110 <- + _iBalasToAdd 0x01
	uNumBalas += _iBalasToAdd;

	//Comprobar que no sea mayor que 255 -> 0x000000FF
	if (uNumBalas > 255)
	{
		uNumBalas = 255;
	}

	// 00000000100110000000000000000000 <- << 16
	uNumBalas = uNumBalas << 16;
	// 00000000111111110000000000000000 MASK_BALAS
	// 11111111000000001111111111111111 ~MASK_BALAS
	
	// 10001110001001010010000000000100 <- _uMask
	// 11111111000000001111111111111111 ~MASK_BALAS
	// -------------------------------- AND
	// 10001110000000000010000000000100 <- Máscara original con balas a 0
	unsigned int uNewMask = _uMask & ~MASK_BALAS;

	// 10001110000000000010000000000100 <- Máscara original con balas a 0
	// 00000000100110000000000000000000 <- Balas sumadas
	// -------------------------------- OR
	uNewMask |= uNumBalas;

	return uNewMask;
}

int main()
{
	// LIFE = 142 (8E)
	// BALAS = 37 (25)
	// COMPAÑEROS = 2 (200)
	//unsigned int uData = 0x8E252006; // con balas activas y escudo (último 6)
	unsigned int uData = 0x8E252004; // con balas inactivas y escudo (último 4)
		printf("Modo Balas Infinito %s!\n",EstaActivoElModoDeBalasInfinito(uData)?"ACTIVO!":"inactivo");

	uData = ActivarBalasInfinitas(uData);

	printf("Modo Balas Infinito %s!\n", EstaActivoElModoDeBalasInfinito(uData) ? "ACTIVO!" : "inactivo");

	printf("Numero Balas = %d\n", GetNumeroBalas(uData));

	uData = AddBalas(uData, 20);

	printf("Numero Balas = %d\n", GetNumeroBalas(uData));

}