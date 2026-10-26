/*
Práctica 14 - Funciones virtuales y vtable

1 Con código documentado que lo demuestre, en Visual Studio x64: ¿cuánto ocupa la vtable? ¿Dónde está? (Pista: compara
su dirección, en los primeros 8 bytes del objeto, con una global, una local y una de new.)

- La vtable es un array con un puntero a función por cada función virtual, y en x64 cada puntero ocupa 8 bytes.
CBall tiene 3 funciones virtuales (destructor, Move y Draw), así que ocupa 3 x 8 = 24 bytes.
- Está en la memoria estática (zona de solo lectura del ejecutable): su dirección se parece a la de la global,
y no a la de la local (pila) ni a la de new (heap).

2 ¿Cuánto ocupa de más un objeto por tener funciones virtuales? (Compara el sizeof con y sin virtual.)

- Exactamente 8 bytes, justo lo que ocupa el puntero a la vtable (vptr) que guarda cada objeto.

3 ¿Qué pasa si llamo a un método virtual desde el constructor? ¿Y desde el destructor?

- En el constructor: El polimorfismo está desactivado porque el objeto aún no es de la clase derivada. Al ser una
función virtual pura ('= 0') sin cuerpo, provoca un error crítico en ejecución (pure virtual function call).

- En el destructor: La parte derivada ya ha sido destruida, por lo que el objeto ha retrocedido a ser de la clase base y
se llamaría a su versión (si es pura sin cuerpo, también peta).

4 Virtual vs no virtual: ¿cuántos pasos más hacen falta? (Pista: Depurar → Ventanas → Desensamblado.)

- Hacen falta 3 pasos más para la clase virtual, donde tiene que
1. cargar el puntero,
2. buscar en la tabla
y 3. hacer la llamada indirecta a ese registro

*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>      // _kbhit, _getch
#include <windows.h>    // Sleep
#include "consola.h"    // gotoxy, hidecursor, clear
#include "CEntityVirtual.h"
#include "CEntityNoVirtual.h"
#include "CBall.h"
#include "Constants.h"

void DrawWorld()
{
    for (int iX = 0; iX < WORLD_WIDTH; ++iX)
    {
        gotoxy(iX, 0);                printf("-");
        gotoxy(iX, WORLD_HEIGHT - 1); printf("-");
    }
    for (int iY = 1; iY < WORLD_HEIGHT - 1; ++iY)
    {
        gotoxy(0, iY);                printf("|");
        gotoxy(WORLD_WIDTH - 1, iY);  printf("|");
    }
    gotoxy(2, WORLD_HEIGHT);
    printf("ESC para salir");
}

// ---------------------------------------------------------------------------------------
// MAIN
// ---------------------------------------------------------------------------------------
const int MAX_ENTITIES = 32;

// Prefijos de las variables a comparar: g_ = global, l_ = local, h_ = heap (new); i = int, p = puntero

// 1. Una variable global para comparar (memoria estática)
int g_iVariableGlobal = 10;

int main()
{
    // 2. Una variable local para comparar (pila)
    int l_iVariableLocal = 20;

    // 3. Una variable creada con new para comparar (heap)
    int* h_piVariableNew = new int(30);

    // Creamos una pelota
    CBall* pBall = new CBall(5, 3, 1, 0);

    // CÓMO OBTENER LA DIRECCIÓN DE LA VTABLE:
    // 'pBall' es un CBall*. Si lo convertimos a void** (puntero a puntero)
    // y lo desreferenciamos con un *, leemos los primeros 8 bytes del objeto (el vptr),
    // que contienen la dirección de la vtable.
    void* pVTable = *(void**)pBall;

    // La vtable es un array de punteros a función (una entrada por función virtual). C++ no permite
    // preguntar su tamaño, así que lo calculamos contando las virtuales de CBall: destructor, Move y Draw.
    const int NUM_FUNCIONES_VIRTUALES = 3;
    void** ppVTable = (void**)pVTable;

    // Imprimimos todas las direcciones en hexadecimal (%p) usando punteros void*
    printf("--------------------------------------------------\n");
    printf("Direccion de la VTABLE:    %p\n", pVTable);
    printf("Direccion variable GLOBAL: %p\n", (void*)&g_iVariableGlobal); // %p imprime una dirección; el cast a void* es
    // el tipo que %p exige
    printf("Direccion variable LOCAL:  %p\n", (void*)&l_iVariableLocal);
    printf("Direccion variable NEW:    %p\n\n", (void*)h_piVariableNew);

    // Cada entrada de la vtable es la dirección de una función virtual de CBall
    for (int iEntrada = 0; iEntrada < NUM_FUNCIONES_VIRTUALES; ++iEntrada)
    {
        printf("Entrada %d de la vtable:    %p\n", iEntrada, ppVTable[iEntrada]);
    }
    printf("Tamano de la vtable = %d entradas x %zu bytes = %zu bytes\n\n",
        NUM_FUNCIONES_VIRTUALES, sizeof(void*), NUM_FUNCIONES_VIRTUALES * sizeof(void*));

    printf("sizeof(CEntityVirtual) = %zu\n", sizeof(CEntityVirtual));
    printf("sizeof(CEntityNoVirtual) = %zu\n", sizeof(CEntityNoVirtual));
    printf("--------------------------------------------------\n");

    // Limpieza de memoria: todo lo creado con new se libera con delete
    delete h_piVariableNew;
    delete pBall;

    return 0;
}