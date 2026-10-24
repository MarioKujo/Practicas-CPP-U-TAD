#include "Templates.h"
#include "TVector2.h"
#include <iostream>
int main()
{
	printf("Clamp(150, 0, 100) -> %d\n", Clamp(150, 0, 100));
	printf("Clamp(-0.5f, 0.0f, 1.0f) -> %f\n", Clamp(-0.5f, 0.0f, 1.0f));
	printf("ClampValues(5, 0.0f, 10) -> %f\n\n", ClampValues(5, 0.0f, 10));

	TStack<int, 4> tStack;

    printf("--- PRUEBA DE PUSH ---\n");
    printf("Push 1: %s\n", tStack.Push(1) ? "Exito" : "Fallo");
    printf("Push 2: %s\n", tStack.Push(2) ? "Exito" : "Fallo");
    printf("Push 3: %s\n", tStack.Push(3) ? "Exito" : "Fallo");
    printf("Push 4: %s\n", tStack.Push(4) ? "Exito" : "Fallo");

    // El 5to Push debe fallar obligatoriamente
    bool quintoIntento = tStack.Push(5);
    printf("Push 5 (Esperado: Fallo): %s\n", quintoIntento ? "Exito" : "Fallo");

    printf("\n--- PRUEBA DE POP (Vaciando la pila) ---\n");
    printf("Elementos extraidos: ");

    int valorExtraido = 0;
    // El bucle Pop se repetirá mientras haya elementos y devolvera true
    while (tStack.Pop(valorExtraido)) {
        printf("%d ", valorExtraido);
    }

    printf("\n\n");

    TStack<TVector2, 8> tVector;

    printf("--- PRUEBA DE PUSH (Vectores) ---\n");
    printf("Push (1.0, 2.0): %s\n", tVector.Push(TVector2(1.0f, 2.0f)) ? "Exito" : "Fallo");
    printf("Push (3.0, 4.0): %s\n", tVector.Push(TVector2(3.0f, 4.0f)) ? "Exito" : "Fallo");
    printf("Push (5.0, 6.0): %s\n", tVector.Push(TVector2(5.0f, 6.0f)) ? "Exito" : "Fallo");

    printf("\n--- PRUEBA DE POP (Vectores) ---\n");
    TVector2 vectorLeido(0.0f, 0.0f);
    while (tVector.Pop(vectorLeido))
    {
        printf("(%.1f, %.1f)\n", vectorLeido.x, vectorLeido.y);
    }
    printf("\n");
    printf("sizeof(TStack<int, 4>) = %zu\n", sizeof(TStack<int, 4>));
    printf("sizeof(TStack<int, 100>) = %zu\n", sizeof(TStack<int, 100>));
    return 0;
}