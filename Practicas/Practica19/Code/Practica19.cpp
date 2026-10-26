#include <cstdio>
#include <crtdbg.h> // Solo existe en Visual Studio
#include "TList19.h"

// Tipo propio, para demostrar que la lista guarda cualquier cosa y no solo tipos básicos
struct SPunto
{
	int iX = 0;
	int iY = 0;
};

// Función plantilla con dos huecos: T es el tipo de los elementos y TPrint el tipo de la función que los
// imprime (cada lambda tiene un tipo propio, por eso hace falta un hueco aparte para ella)
template<typename T, typename TPrint>
void Imprimir(Practica19::TList<T>& _lstLista, const char* _pszTitulo, const TPrint& _fnPrint)
{
	printf("%s (%d):\n", _pszTitulo, _lstLista.Size());
	for (T* pItem = _lstLista.First(); pItem != nullptr; pItem = _lstLista.Next())
	{
		_fnPrint(*pItem); // El * pasa el dato y no su dirección
	}
	printf("\n");
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Avisa de fugas al cerrar (ver práctica 15)

	{ // Llaves: así las listas se destruyen ANTES del informe de fugas y no salen como falsas fugas
		// Lambda: una función sin nombre escrita donde se necesita. Los [] indican que no usa variables de
		// fuera, entre () van sus parámetros, y "auto" deja que el compilador deduzca el tipo de la variable
		const auto fnPrintInt = [](int iNumero)
			{
				printf("%d\n", iNumero);
			};

		// --- TList<int>: T = int ---
		Practica19::TList<int> lstInts;
		printf("Push: %d\n", lstInts.Push(10)); // 1
		printf("Push: %d\n", lstInts.Push(20)); // 2
		printf("Push: %d\n", lstInts.Push(30)); // 3
		lstInts.PushFront(5);                   // La lista queda: 5, 10, 20, 30
		Imprimir(lstInts, "Ints", fnPrintInt);

		// --- Copia profunda: la copia tiene sus propios nodos, así que modificar el original no la afecta ---
		Practica19::TList<int> lstCopia(lstInts);
		*lstInts.First() = 999; // First devuelve la dirección del dato; con * se modifica
		Imprimir(lstInts, "Original modificado", fnPrintInt);
		Imprimir(lstCopia, "Copia (no debe cambiar)", fnPrintInt);

		// --- operator= y autoasignación (la segunda no debe borrar la lista) ---
		Practica19::TList<int> lstAsignada;
		lstAsignada = lstCopia;
		lstAsignada = lstAsignada;
		Imprimir(lstAsignada, "Asignada", fnPrintInt);

		// --- Invertida ---
		Practica19::TList<int> lstInversa = Practica19::GetReverseList(lstCopia);
		Imprimir(lstInversa, "Invertida", fnPrintInt);

		// --- Pop hasta vaciar ---
		int iValor = 0;
		while (lstInversa.Pop(iValor)) // Pop escribe el dato en iValor y devuelve false cuando ya no queda nada
		{
			printf("Pop: %d (quedan %d)\n", iValor, lstInversa.Size());
		}
		printf("Pop con la lista vacia: %s\n", lstInversa.Pop(iValor) ? "algo" : "false");
		printf("First vacia: %s\n\n", lstInversa.First() ? "algo" : "nullptr");

		// --- Reset y reutilización ---
		lstCopia.Reset();
		printf("Size tras Reset: %d\n", lstCopia.Size());
		lstCopia.Push(7);
		Imprimir(lstCopia, "Reutilizada", fnPrintInt);

		// --- TList<float>: la misma clase con otro tipo ---
		Practica19::TList<float> lstFloats;
		lstFloats.Push(1.5f);
		lstFloats.Push(2.25f);
		Imprimir(lstFloats, "Floats", [](float fNumero) { printf("%.2f\n", fNumero); });

		// --- TList<SPunto>: con un tipo propio ---
		Practica19::TList<SPunto> lstPuntos;
		lstPuntos.Push({ 1, 2 }); // {1, 2} crea un SPunto con iX = 1 y iY = 2
		lstPuntos.Push({ 3, 4 });
		Imprimir(lstPuntos, "Puntos", [](const SPunto& oPunto) { printf("(%d, %d)\n", oPunto.iX, oPunto.iY); });
	}
	return 0;
}