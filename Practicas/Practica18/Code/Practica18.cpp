#include "Debug.h"

int main()
{
	int iVida = 100;
	LOG("vida = %d", iVida);

	// Prueba de la pregunta d: ¿cuánto vale iIntentos después? Debug: 1 | Release: 0
	int iIntentos = 0;
	ASSERT(++iIntentos < 3);
	printf("iIntentos = %d\n", iIntentos);

	ASSERT(iVida > 200); // En Debug: la condición es falsa, así que muestra el mensaje y aborta
	printf("iVida (para usarlo en Release: %d\n", iVida);
	return 0;
}