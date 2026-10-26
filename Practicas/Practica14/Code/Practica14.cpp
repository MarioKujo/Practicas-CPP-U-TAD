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

- En el constructor: el objeto todavía no es de la clase hija (su vptr apunta a la vtable de CEntityVirtual), así
que no hay polimorfismo: se llamaría a la versión de la clase base, nunca a la de CBall. Como Move() es virtual pura y
no tiene cuerpo, no hay nada que ejecutar: con una llamada directa suele dar error al enlazar (unresolved external) y,
si se llega por un camino indirecto, falla en ejecución con "pure virtual function call".

- En el destructor: la parte hija ya se ha destruido, así que el objeto vuelve a ser de la clase base y pasa lo mismo:
se llama a la versión de la base (y, si es pura sin cuerpo, también falla).

4 Virtual vs no virtual: ¿cuántos pasos más hacen falta? (Pista: Depurar → Ventanas → Desensamblado.)

- Una llamada no virtual es un único "call" a una dirección que el compilador ya conoce. La virtual hace 3 pasos más:
1. cargar el puntero a la vtable del objeto (vptr),
2. buscar en la tabla la entrada de la función,
3. hacer la llamada indirecta a esa dirección.
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

// Igual que en la práctica 4
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

const int MAX_ENTITIES = 32;

// Prefijos de las variables a comparar: g_ = global, l_ = local, h_ = heap (new); i = int, p = puntero

// Variable global: vive en la memoria estática, junto a la vtable
int g_iVariableGlobal = 10;

int main()
{
  // Variable local: vive en la pila
  int l_iVariableLocal = 20;

  // Variable creada con new: vive en el heap
  int* const h_piVariableNew = new int(30);

  CBall* const pBall = new CBall(5, 3, 1, 0);
  /*
  Cómo sacar la dirección de la vtable: en Visual Studio x64, los primeros 8 bytes de un objeto con
  virtuales son el vptr, que guarda la dirección de su vtable. Se convierte pBall a void** ("puntero
  a puntero") para poder leer esos 8 bytes como si fueran un puntero, y el * de delante los lee.
  Esto depende de cómo organiza MSVC los objetos: C++ no garantiza este formato
  */
  void* const* const ppVptr = reinterpret_cast<void* const*>(pBall);
  void* const pVTable = *ppVptr;

  // C++ no permite preguntar el tamaño de la vtable, así que se cuentan a mano las virtuales de CBall:
  // destructor, Move y Draw
  const int NUM_FUNCIONES_VIRTUALES = 3;
  void* const* const ppVTable = static_cast<void* const*>(pVTable); // Ahora se puede acceder a la vtable como un array: ppVTable[0], [1]...

  // %p imprime una dirección en hexadecimal y exige un void*, por eso los casts
  printf("--------------------------------------------------\n");
  printf("Direccion de la VTABLE:    %p\n", pVTable);
  printf("Direccion variable GLOBAL: %p\n", static_cast<void*>(&g_iVariableGlobal));
  printf("Direccion variable LOCAL:  %p\n", static_cast<void*>(&l_iVariableLocal));
  printf("Direccion variable NEW:    %p\n\n", static_cast<void*>(h_piVariableNew));

  // Cada entrada de la vtable es la dirección de una función virtual de CBall
  for (int iEntrada = 0; iEntrada < NUM_FUNCIONES_VIRTUALES; ++iEntrada)
  {
    printf("Entrada %d de la vtable:    %p\n", iEntrada, ppVTable[iEntrada]);
  }
  printf("Tamano de la vtable = %d entradas x %zu bytes = %zu bytes\n\n",
    NUM_FUNCIONES_VIRTUALES, sizeof(void*), NUM_FUNCIONES_VIRTUALES * sizeof(void*));

  // Pregunta 2: la diferencia entre los dos tiene que ser 8 bytes (el vptr)
  printf("sizeof(CEntityVirtual) = %zu\n", sizeof(CEntityVirtual));
  printf("sizeof(CEntityNoVirtual) = %zu\n", sizeof(CEntityNoVirtual));
  printf("--------------------------------------------------\n");

  // Todo lo creado con new se libera con delete. Como el destructor es virtual, delete pBall
  // ejecuta también el destructor de CBall
  delete h_piVariableNew;
  delete pBall;

  return 0;
}