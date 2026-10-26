#include <cstdio>
#include <iostream>
#include "TList16.h"
#include <crtdbg.h> // Solo existe en Visual Studio

// Una interfaz no se puede instanciar: se crean clases que la heredan y que están obligadas a hacer
// override de todas sus funciones virtuales puras (ver práctica 15)
class CText : public Practica16::IListItem
{
public:
	virtual void Print() const override
	{
		printf("%s\n", m_pszText);
	}
	virtual Practica16::IListItem* Clone() const override
	{
		// new CText(*this) crea en el heap un CText nuevo copiando este (usa el constructor de copia que el
		// compilador genera solo). Vive hasta que alguien haga delete: la lista, en Reset
		return new CText(*this);
	}
	// Ojo: la copia solo copia el puntero, no el texto. Aquí vale porque apunta a literales ("uno", "dos"...),
	// que existen durante todo el programa. Con un buffer local, la copia quedaría apuntando a memoria inválida
	const char* m_pszText = "";
};

class CNumber : public Practica16::IListItem
{
public:
	virtual void Print() const override
	{
		printf("%d\n", m_iValue);
	}
	virtual Practica16::IListItem* Clone() const override
	{
		return new CNumber(*this);
	}
	int m_iValue = 0;
};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Avisa de fugas al cerrar (ver práctica 15)

	const char* const apszTextos[] =
	{
		"uno",
		"dos",
		"tres",
		"cuatro",
		"cinco"
	};
	constexpr int NUM_PARES = 5; // Cuántos pares texto + número se meten (tiene que coincidir con el tamaño de la tabla)

	// Textos y números mezclados en la misma lista
	Practica16::TList lstItems;
	for (int iIndex = 0; iIndex < NUM_PARES; ++iIndex)
	{
		// Estos dos objetos se destruyen al acabar cada vuelta, y no pasa nada: Push ya guardó copias
		CText oText;
		oText.m_pszText = apszTextos[iIndex];
		CNumber oNumber;
		oNumber.m_iValue = iIndex + 1;

		lstItems.Push(oText);
		lstItems.Push(oNumber);
	}

	printf("Numeros leidos (%d):\n", lstItems.Size());
	// main no sabe si pItem es un CText o un CNumber: cada Print() hace lo suyo
	for (Practica16::IListItem* pItem = lstItems.First(); pItem != nullptr; pItem = lstItems.Next())
	{
		pItem->Print();
	}
	printf("\n");

	Practica16::TList lstCopia(lstItems); // Constructor de copia
	printf("Numeros leidos (copia) (%d):\n", lstCopia.Size());
	lstCopia.Print();
	printf("\n");

	Practica16::TList lstInvertida(GetReverseList(lstItems));
	printf("Numeros leidos (invertido) (%d):\n", lstInvertida.Size());
	lstInvertida.Print();
	printf("\n");

	Practica16::TList lstAsignada;
	lstAsignada = lstInvertida; // operator=
	printf("Numeros leidos (operator=) (%d):\n", lstAsignada.Size());
	lstAsignada.Print();
	printf("\n");

	// Pop saca el primer elemento y lo entrega: ahora es responsabilidad de main hacer delete
	Practica16::IListItem* const pItemQuitado = lstAsignada.Pop();
	if (pItemQuitado != nullptr)
	{
		printf("Pop: ");
		pItemQuitado->Print();
		delete pItemQuitado; // Borra el objeto de verdad gracias al destructor virtual de IListItem
	}

	return 0;
}