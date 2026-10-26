#include "TList11.h"
#include <cstring>
#include <cstdio>

// Es la TList de la práctica 9. Solo se comenta lo nuevo (constructor de copia, operator=, PushFront y
// GetReverseList); para el resto, lee los comentarios de TList09.cpp

namespace Practica11
{
	TList::TList()
	{
	}

	TList::TList(const TList& oOther)
	{
		printf("Constructor de copia de TList\n"); // Sirve para contar cuántas copias se hacen (punto 3)
		// La lista nueva está vacía. Se recorre la otra y se hace Push de cada cadena; como Push crea un
		// nodo nuevo con su propia copia de la cadena, las dos listas no comparten nada
		for (const TListNode* pNodo = oOther.m_pFirst; pNodo != nullptr; pNodo = pNodo->m_pNext)
		{
			Push(pNodo->m_pszCadena);
		}
	}

	TList& TList::operator=(const TList& oOther)
	{
		if (this != &oOther) // Evita el caso oLista = oLista: si no, Reset borraría los datos antes de copiarlos
		{
			// Diferencia con el constructor de copia: aquí la lista ya existe y puede tener elementos,
			// así que primero hay que vaciarla. El resto es igual
			Reset();
			for (const TListNode* pNodo = oOther.m_pFirst; pNodo != nullptr; pNodo = pNodo->m_pNext)
			{
				Push(pNodo->m_pszCadena);
			}
		}
		return *this; // Se devuelve la propia lista para poder encadenar: oA = oB = oC;
	}

	TList GetReverseList(TList lstSrc) // Por valor: al llamarla se hace una copia entera de la lista (constructor de
		// copia)
	{
		TList oInvertida;
		// Se recorre de principio a fin y cada elemento se mete AL PRINCIPIO de la nueva lista, así queda al revés
		for (const TList::TListNode* pNodo = lstSrc.m_pFirst; pNodo != nullptr; pNodo = pNodo->m_pNext)
		{
			oInvertida.PushFront(pNodo->m_pszCadena);
		}
		return oInvertida;
	}

	TList::~TList()
	{
		Reset();
	}

	int TList::Size()
	{
		return m_uSize;
	}

	int TList::Push(const char* psz)
	{
		TListNode* pNewNode = new TListNode(psz);

		if (m_pFirst == nullptr)
		{
			m_pFirst = pNewNode;
		}
		else
		{
			m_pLast->m_pNext = pNewNode;
		}
		m_pLast = pNewNode;
		++m_uSize;
		return m_uSize;
	}

	// NUEVO: igual que Push, pero el nodo nuevo se coloca el primero. Se añadió para poder invertir la lista
	int TList::PushFront(const char* psz)
	{
		TListNode* pNewNode = new TListNode(psz);

		pNewNode->m_pNext = m_pFirst; // El nuevo apunta al que era primero (que pasa a ser el segundo)
		m_pFirst = pNewNode; // y ahora el nuevo es el primero.
		// Con PushFront(3); PushFront(2); PushFront(1); la lista queda 1, 2, 3

		if (m_pLast == nullptr)
		{
			m_pLast = pNewNode; // Solo cambia con el primer nodo que entra: el último no se mueve al añadir por delante
		}

		++m_uSize;
		return m_uSize;
	}

	const char* TList::First()
	{
		m_pIter = m_pFirst;
		if (m_pIter)
		{
			return m_pIter->m_pszCadena;
		}
		return nullptr;
	}

	const char* TList::Next()
	{
		if (m_pIter)
		{
			m_pIter = m_pIter->m_pNext;
		}
		if (m_pIter)
		{
			return m_pIter->m_pszCadena;
		}
		return nullptr;
	}

	// El puntero que devuelve Pop es válido hasta la siguiente llamada a Pop, a Reset o hasta destruir la lista.
	const char* TList::Pop()
	{
		if (m_pFirst == nullptr)
		{
			m_pLast = nullptr;
			return nullptr;
		}

		delete[] m_pszLastPopped;
		m_pszLastPopped = nullptr;

		TListNode* pRemoved = m_pFirst;
		m_pFirst = pRemoved->m_pNext;
		--m_uSize;
		if (m_pFirst == nullptr)
		{
			m_pLast = nullptr;
		}
		if (m_pIter == pRemoved)
		{
			m_pIter = nullptr;
		}

		m_pszLastPopped = pRemoved->m_pszCadena;
		pRemoved->m_pszCadena = nullptr;
		delete pRemoved;

		return m_pszLastPopped;
	}

	void TList::Reset()
	{
		TListNode* pTmp = m_pFirst;
		while (pTmp)
		{
			TListNode* pToDelete = pTmp;
			pTmp = pTmp->m_pNext;
			delete pToDelete;
		}
		m_pFirst = nullptr;
		m_pLast = nullptr;
		m_uSize = 0;
		m_pIter = nullptr;

		delete[] m_pszLastPopped;
		m_pszLastPopped = nullptr;
	}

	TList::TListNode::TListNode(const char* _pszText)
	{
		if (_pszText)
		{
			unsigned int uLen = static_cast<unsigned int>(strlen(_pszText));
			char* pcCopia = new char[uLen + 1];
			strcpy_s(pcCopia, uLen + 1, _pszText);
			m_pszCadena = pcCopia;
		}
	}

	TList::TListNode::~TListNode()
	{
		if (m_pszCadena)
		{
			delete[] m_pszCadena;
			m_pszCadena = nullptr;
		}
	}
}