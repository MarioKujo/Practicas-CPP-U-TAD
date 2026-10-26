#include "Debug.h"

int main()
{
	int iVida = 100;
	LOG("vida = %d", iVida); // Muestra algo como: Practica18.cpp(7): vida = 100

	// Pregunta d: ¿cuánto vale iIntentos después? Debug: 1 | Release: 0
	// En Debug, ++iIntentos se ejecuta (1 < 3 es cierto, así que no aborta). En Release la línea desaparece entera
	int iIntentos = 0;
	ASSERT(++iIntentos < 3);
	printf("iIntentos = %d\n", iIntentos);

	// En Debug la condición es falsa (100 no es mayor que 200): muestra el mensaje y aborta, así que el
	// printf de debajo no llega a ejecutarse. En Release no hace nada y sí se ejecuta
	ASSERT(iVida > 200);
	printf("iVida (para usarlo en Release): %d\n", iVida);
	return 0;
}