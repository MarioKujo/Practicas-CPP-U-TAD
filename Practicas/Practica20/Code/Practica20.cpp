#include <cstdio>
#include "Templates.h"
#include "TVector2.h" // El de la práctica 12

int main()
{
	printf("Clamp(150, 0, 100) -> %d\n", Clamp(150, 0, 100)); // Los tres son int: T = int
	printf("Clamp(-0.5f, 0.0f, 1.0f) -> %f\n", Clamp(-0.5f, 0.0f, 1.0f)); // Los tres son float: T = float
	// Clamp(5, 0.0f, 10) no compilaría (apartado b); ClampValues sí, porque convierte todo al tipo común (float)
	printf("ClampValues(5, 0.0f, 10) -> %f\n\n", ClampValues(5, 0.0f, 10));

	TStack<int, 4> oStackInts; // Pila de ints con capacidad para 4

	printf("--- PRUEBA DE PUSH ---\n");
	printf("Push 1: %s\n", oStackInts.Push(1) ? "Exito" : "Fallo");
	printf("Push 2: %s\n", oStackInts.Push(2) ? "Exito" : "Fallo");
	printf("Push 3: %s\n", oStackInts.Push(3) ? "Exito" : "Fallo");
	printf("Push 4: %s\n", oStackInts.Push(4) ? "Exito" : "Fallo");

	// El quinto Push tiene que fallar: la pila solo tiene sitio para 4
	const bool bQuintoPush = oStackInts.Push(5);
	printf("Push 5 (Esperado: Fallo): %s\n", bQuintoPush ? "Exito" : "Fallo");

	printf("\n--- PRUEBA DE POP (Vaciando la pila) ---\n");
	printf("Elementos extraidos: ");

	int iValorExtraido = 0;
	// Pop devuelve true mientras queden elementos, así que el bucle acaba solo al vaciarla (salen 4 3 2 1)
	while (oStackInts.Pop(iValorExtraido))
	{
		printf("%d ", iValorExtraido);
	}

	printf("\n\n");

	TStack<TVector2, 8> oStackVectores; // Misma plantilla con otro tipo y otro tamaño: es un tipo distinto

	printf("--- PRUEBA DE PUSH (Vectores) ---\n");
	printf("Push (1.0, 2.0): %s\n", oStackVectores.Push(TVector2(1.0f, 2.0f)) ? "Exito" : "Fallo");
	printf("Push (3.0, 4.0): %s\n", oStackVectores.Push(TVector2(3.0f, 4.0f)) ? "Exito" : "Fallo");
	printf("Push (5.0, 6.0): %s\n", oStackVectores.Push(TVector2(5.0f, 6.0f)) ? "Exito" : "Fallo");

	printf("\n--- PRUEBA DE POP (Vectores) ---\n");
	TVector2 oVectorLeido(0.0f, 0.0f);
	while (oStackVectores.Pop(oVectorLeido)) // Salen en orden inverso: (5, 6), (3, 4), (1, 2)
	{
		printf("(%.1f, %.1f)\n", oVectorLeido.x, oVectorLeido.y);
	}
	printf("\n");

	// Apartado e: los tamaños son distintos porque son tipos distintos, cada uno con su propio array
	printf("sizeof(TStack<int, 4>) = %zu\n", sizeof(TStack<int, 4>));
	printf("sizeof(TStack<int, 100>) = %zu\n", sizeof(TStack<int, 100>));
	return 0;
}