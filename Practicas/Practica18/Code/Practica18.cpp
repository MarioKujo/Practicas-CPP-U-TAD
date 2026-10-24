#include "Debug.h"

int main()
{
	int iVida = 100;
	LOG("vida = %d", iVida);

	int iIntentos = 0;
	ASSERT(++iIntentos < 3);
	printf("iIntentos = %d\n", iIntentos);

	ASSERT(iVida > 200);   // en Debug: aborta
	return 0;
}