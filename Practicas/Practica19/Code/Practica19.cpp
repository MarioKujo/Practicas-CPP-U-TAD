#include <cstdio>
#include <crtdbg.h>
#include "TList19.h"

struct SPunto
{
	int x = 0;
	int y = 0;
};

template<typename T, typename TPrint>
void Imprimir(Practica19::TList<T>& lista, const char* sTitulo, TPrint print)
{
	printf("%s (%d):\n", sTitulo, lista.Size());
	for (T* p = lista.First();p != nullptr;p = lista.Next())
	{
		print(*p);
	}
	printf("\n");
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	{ // Llaves: las listas se destruyen antes del informe de fugas
		auto printInt = [](int v)
			{
				printf("%d\n", v);
			};

			// --- TList<int> ---
		Practica19::TList<int> lInts;
		printf("Push: %d\n", lInts.Push(10)); // 1
		printf("Push: %d\n", lInts.Push(20)); // 2
		printf("Push: %d\n", lInts.Push(30)); // 3
		lInts.PushFront(5);                   // 5, 10, 20, 30
		Imprimir(lInts, "Ints", printInt);

		// --- Copia profunda ---
		Practica19::TList<int> lCopia(lInts);
		*lInts.First() = 999;                 // modifico el original
		Imprimir(lInts, "Original modificado", printInt);
		Imprimir(lCopia, "Copia (no debe cambiar)", printInt);

		// --- operator= y autoasignación ---
		Practica19::TList<int> lAsignada;
		lAsignada = lCopia;
		lAsignada = lAsignada;
		Imprimir(lAsignada, "Asignada", printInt);

		// --- Invertida ---
		Practica19::TList<int> lInversa = Practica19::GetReverseList(lCopia);
		Imprimir(lInversa, "Invertida", printInt);

		// --- Pop hasta vaciar ---
		int iValor = 0;
		while (lInversa.Pop(iValor))
		{
			printf("Pop: %d (quedan %d)\n", iValor, lInversa.Size());
		}
		printf("Pop con la lista vacia: %s\n", lInversa.Pop(iValor) ? "algo" : "false");
		printf("First vacia: %s\n\n", lInversa.First() ? "algo" : "nullptr");

		// --- Reset y reutilización ---
		lCopia.Reset();
		printf("Size tras Reset: %d\n", lCopia.Size());
		lCopia.Push(7);
		Imprimir(lCopia, "Reutilizada", printInt);

		// --- TList<float> ---
		Practica19::TList<float> lFloats;
		lFloats.Push(1.5f);
		lFloats.Push(2.25f);
		Imprimir(lFloats, "Floats", [](float v) {printf("%.2f\n", v);});

		// --- TList<struct propio> ---
		Practica19::TList<SPunto>lPuntos;
		lPuntos.Push({ 1, 2 });
		lPuntos.Push({ 3, 4 });
		Imprimir(lPuntos, "Puntos", [](const SPunto& p) {printf("(%d, %d)\n", p.x, p.y);});
	}
	return 0;
}