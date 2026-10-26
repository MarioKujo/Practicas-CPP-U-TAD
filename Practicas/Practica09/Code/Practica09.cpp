/*
1 Partir de TList.h e implementar todos sus métodos en TList.cpp, sin cambiar la parte pública. La parte privada la
decidís vosotros.

2 Push añade al final y retorna el nº de elementos. First/Next recorren la lista; Pop quita y retorna el primero. Sin
elementos → nullptr.

3 El destructor libera toda la memoria. Reset vacía la lista, que se puede seguir usando.

4 Probar en un main los casos límite (lista vacía, final del recorrido, Pop hasta vaciarla).

5 Añadir una cadena desde un buffer local y modificar después el buffer: ¿qué devuelve la lista? ¿Por qué?

Devuelve lo que le hemos pasado al push, ya que TList hace una copia propia reservando memoria con new char[] y luego
con strcpy_s. No guarda la dirección del buffer, guarda la dirección de su propia copia, así que da igual si modificas
la variable local en el main.
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include "TList09.h"
int main()
{
	Practica09::TList oLista;

	// Lista vacía: todo tiene que devolver 0 o nullptr, y no romperse
	printf("Size vacia: %d\n", oLista.Size());                    // 0
	printf("First vacia: %s\n", oLista.First() ? "algo" : "nullptr");
	printf("Next sin First: %s\n", oLista.Next() ? "algo" : "nullptr");
	printf("Pop vacia: %s\n", oLista.Pop() ? "algo" : "nullptr");

	// Push devuelve el tamaño de la lista tras añadir
	printf("Push: %d\n", oLista.Push("uno"));                     // 1
	printf("Push: %d\n", oLista.Push("dos"));                     // 2
	printf("Push: %d\n", oLista.Push("tres"));                    // 3

	// Recorrido completo y final del recorrido
	for (const char* pszCadena = oLista.First(); pszCadena != nullptr; pszCadena = oLista.Next())
	{
		printf("%s\n", pszCadena);
	}
	printf("Next tras el final: %s\n", oLista.Next() ? "algo" : "nullptr");

	// Pop hasta vaciar. La cadena se imprime ANTES del siguiente Pop, porque ese Pop la liberaría
	while (oLista.Size() > 0)
	{
		const char* const pszCadena = oLista.Pop();
		printf("Pop: %s (quedan %d)\n", pszCadena, oLista.Size());
	}
	printf("Pop con la lista ya vacia: %s\n", oLista.Pop() ? "algo" : "nullptr");

	// Reutilizar tras vaciar, y Reset
	oLista.Push("otra");
	oLista.Reset();
	printf("Size tras Reset: %d\n", oLista.Size());               // 0
	oLista.Push("de nuevo");
	printf("Reutilizada: %s\n", oLista.First());

	// Punto 5: se cambia el buffer después del Push y la lista conserva el valor original
	char acBuffer[16] = "hola";
	oLista.Push(acBuffer);
	strcpy_s(acBuffer, "XXXX");
	oLista.First(); // Coloca el recorrido en "de nuevo"
	printf("Ultimo: %s\n", oLista.Next());                        // hola
	printf("\n");
	return 0;
}