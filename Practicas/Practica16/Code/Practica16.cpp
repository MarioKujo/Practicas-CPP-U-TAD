#include <iostream>
#include "TList16.h"
#include <crtdbg.h>

// Una interfaz no se puede instanciar, así que las clases que la implementan heredan de ella
// y están obligadas a hacer override de todas sus funciones virtuales puras.
class CText : public Practica16::IListItem
{
public:
	virtual void Print() const override
	{
		printf("%s\n", pszText);
	}
	virtual Practica16::IListItem* Clone() const override
	{
		return new CText(*this); // new: la copia vive en el heap hasta que alguien le haga delete (la lista, en Reset)
	}
	const char* pszText = "";
};

class CNumber : public Practica16::IListItem
{
public:
	virtual void Print() const override
	{
		printf("%d\n", iValue);
	}
	virtual Practica16::IListItem* Clone() const override
	{
		return new CNumber(*this);
	}
	int iValue = 0;
};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Los textos van en una tabla; los números salen del propio contador del bucle (1, 2, 3...)
	const char* tpszTextos[] =
	{
		"uno",
		"dos",
		"tres",
		"cuatro",
		"cinco"
	};
	const int NUM_PARES = 5; // Cuántos pares texto + número metemos (tiene que coincidir con el tamaño de la tabla)

	// Textos y números mezclados en la misma lista: Push guarda una copia de cada uno
	Practica16::TList lstItems;
	for (int iIndex = 0; iIndex < NUM_PARES; ++iIndex)
	{
		// Estos dos objetos solo viven durante esta vuelta del bucle; no pasa nada
		// porque la lista ya tiene sus propias copias hechas con Clone()
		CText oText;
		oText.pszText = tpszTextos[iIndex];
		CNumber oNumber;
		oNumber.iValue = iIndex + 1;

		lstItems.Push(oText);
		lstItems.Push(oNumber);
	}

	printf("Numeros leidos (%d):\n", lstItems.Size());
	// Recorrido con First/Next; Print() es el de cada tipo (CText o CNumber) sin que main sepa cuál es
	for (Practica16::IListItem* pItem = lstItems.First(); pItem != nullptr; pItem = lstItems.Next())
	{
		pItem->Print();
	}
	printf("\n");

	Practica16::TList lstCopia(lstItems);
	printf("Numeros leidos (copia) (%d):\n", lstCopia.Size());
	lstCopia.Print();
	printf("\n");

	Practica16::TList lstInvertida(GetReverseList(lstItems));
	printf("Numeros leidos (invertido) (%d):\n", lstInvertida.Size());
	lstInvertida.Print();
	printf("\n");

	Practica16::TList lstAsignada;
	lstAsignada = lstInvertida;
	printf("Numeros leidos (operator=) (%d):\n", lstAsignada.Size());
	lstAsignada.Print();
	printf("\n");

	// Pop saca el primer elemento de la lista y nos lo entrega: ahora es responsabilidad nuestra hacer delete
	Practica16::IListItem* pItemQuitado = lstAsignada.Pop();
	printf("Pop: ");
	pItemQuitado->Print();
	delete pItemQuitado;

	return 0;
}