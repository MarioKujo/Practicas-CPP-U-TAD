/*
1 Partir de TList.h e implementar todos sus métodos en TList.cpp, sin cambiar la parte pública. La parte privada la decidís vosotros.

2 Push añade al final y retorna el nº de elementos. First/Next recorren la lista; Pop quita y retorna el primero. Sin elementos → nullptr.

3 El destructor libera toda la memoria. Reset vacía la lista, que se puede seguir usando.

4 Probar en un main los casos límite (lista vacía, final del recorrido, Pop hasta vaciarla).

5 Añadir una cadena desde un buffer local y modificar después el buffer: ¿qué devuelve la lista? ¿Por qué?

Devuelve lo que le hemos pasado al push, ya que TList hace una copia propia reservando memoria con new char[] y luego con strcpy_s. No guarda la dirección del buffer, guarda la dirección de su propia copia, así que da igual si modificas la variable local en el main.
*/
#include <iostream>
#include "TList09.h"
int main()
{
	TList tList;

	// Lista vacía
	printf("Size vacia: %d\n", tList.Size());                    // 0
	printf("First vacia: %s\n", tList.First() ? "algo" : "nullptr");
	printf("Next sin First: %s\n", tList.Next() ? "algo" : "nullptr");
	printf("Pop vacia: %s\n", tList.Pop() ? "algo" : "nullptr");

	// Push y retorno
	printf("Push: %d\n", tList.Push("uno"));                     // 1
	printf("Push: %d\n", tList.Push("dos"));                     // 2
	printf("Push: %d\n", tList.Push("tres"));                    // 3

	// Recorrido completo y final del recorrido
	for (const char* p = tList.First(); p != nullptr; p = tList.Next())
	{
		printf("%s\n", p);
	}
	printf("Next tras el final: %s\n", tList.Next() ? "algo" : "nullptr");

	// Pop hasta vaciar
	while (tList.Size() > 0)
	{
		const char* p = tList.Pop();
		printf("Pop: %s (quedan %d)\n", p, tList.Size());
	}
	printf("Pop con la lista ya vacia: %s\n", tList.Pop() ? "algo" : "nullptr");

	// Reutilizar tras vaciar, y Reset
	tList.Push("otra");
	tList.Reset();
	printf("Size tras Reset: %d\n", tList.Size());               // 0
	tList.Push("de nuevo");
	printf("Reutilizada: %s\n", tList.First());

	// Punto 5
	char buffer[16] = "hola";
	tList.Push(buffer);
	strcpy_s(buffer, "XXXX");
	tList.First();
	printf("Ultimo: %s\n", tList.Next());                        // hola
	printf("\n");
	return 0;
}